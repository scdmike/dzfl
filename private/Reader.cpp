#include "Reader.h"
#include "../public/Record.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

static inline bool in(Reader::Char c, Reader::Char c1, Reader::Char c2,
        Reader::Char c3, Reader::Char c4) {
    return c == c1 || c == c2 || c == c3 || c == c4;
}

static inline bool in(Reader::Char c, Reader::Char c1, Reader::Char c2,
        Reader::Char c3, Reader::Char c4, Reader::Char c5) {
    return c == c1 || c == c2 || c == c3 || c == c4 || c == c5;
}

static inline void appendUnicodeToUtf8(unsigned int c, QByteArray &utf8) {
    if (c < 0x00080) {
        utf8 += static_cast<char> (c & 0xFF);
    } else if (c < 0x00800) {
        utf8 += static_cast<char> (0xC0 + ((c >> 6) & 0x1F));
        utf8 += static_cast<char> (0x80 + (c & 0x3F));
    } else if (c < 0x10000) {
        utf8 += static_cast<char> (0xE0 + ((c >> 12) & 0x0F));
        utf8 += static_cast<char> (0x80 + ((c >> 6) & 0x3F));
        utf8 += static_cast<char> (0x80 + (c & 0x3F));
    } else {
        utf8 += static_cast<char> (0xF0 + ((c >> 18) & 0x07));
        utf8 += static_cast<char> (0x80 + ((c >> 12) & 0x3F));
        utf8 += static_cast<char> (0x80 + ((c >> 6) & 0x3F));
        utf8 += static_cast<char> (0x80 + (c & 0x3F));
    }
}

// Class Reader
// //////////////////////////////////////////////////////////////////

Reader::Reader() {
}

bool Reader::parse(const char *beginDoc, const char *endDoc, Record &root) {
    begin_ = beginDoc;
    end_ = endDoc;
    current_ = begin_;
    lastValueEnd_ = 0;
    lastValue_ = 0;
    while (!nodes_.empty())
        nodes_.pop();
    nodes_.push(&root);

    bool successful = readValue();
    Token token;
    skipCommentTokens(token);
    return successful;
}

bool Reader::readValue() {
    Token token;
    skipCommentTokens(token);
    bool successful = true;

    switch (token.type_) {
    case tokenObjectBegin:
        successful = readObject(token);
        break;
    case tokenArrayBegin:
        successful = readArray(token);
        break;
    case tokenNumber:
        successful = decodeNumber(token);
        break;
    case tokenString:
        successful = decodeString(token);
        break;
    case tokenTrue:
        currentValue() = true;
        break;
    case tokenFalse:
        currentValue() = false;
        break;
    case tokenNull:
        currentValue() = Record();
        break;
    default:
        return false;
    }

    return successful;
}

void Reader::skipCommentTokens(Token &token) {
    do {
        readToken(token);
    } while (token.type_ == tokenComment);
}

bool Reader::expectToken(TokenType type, Token &token, const char *) {
    readToken(token);
    if (token.type_ != type)
        return false;
    return true;
}

bool Reader::readToken(Token &token) {
    skipSpaces();
    token.start_ = current_;
    Char c = getNextChar();
    bool ok = true;
    switch (c) {
    case '{':
        token.type_ = tokenObjectBegin;
        break;
    case '}':
        token.type_ = tokenObjectEnd;
        break;
    case '[':
        token.type_ = tokenArrayBegin;
        break;
    case ']':
        token.type_ = tokenArrayEnd;
        break;
    case '"':
        token.type_ = tokenString;
        ok = readString();
        break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '-':
        token.type_ = tokenNumber;
        readNumber();
        break;
    case 't':
        token.type_ = tokenTrue;
        ok = match("rue", 3);
        break;
    case 'f':
        token.type_ = tokenFalse;
        ok = match("alse", 4);
        break;
    case 'n':
        token.type_ = tokenNull;
        ok = match("ull", 3);
        break;
    case ',':
        token.type_ = tokenArraySeparator;
        break;
    case ':':
        token.type_ = tokenMemberSeparator;
        break;
    case 0:
        token.type_ = tokenEndOfStream;
        break;
    default:
        ok = false;
        break;
    }
    if (!ok)
        token.type_ = tokenError;
    token.end_ = current_;
    return true;
}

void Reader::skipSpaces() {
    while (current_ != end_) {
        Char c = *current_;
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
            ++current_;
        else
            break;
    }
}

bool Reader::match(Location pattern, int patternLength) {
    if (end_ - current_ < patternLength)
        return false;
    int index = patternLength;
    while (index--)
        if (current_[index] != pattern[index])
            return false;
    current_ += patternLength;
    return true;
}

void Reader::readNumber() {
    while (current_ != end_) {
        if (!(*current_ >= '0' && *current_ <= '9') && !in(*current_, '.', 'e',
                'E', '+', '-'))
            break;
        ++current_;
    }
}

bool Reader::readString() {
    Char c = 0;
    while (current_ != end_) {
        c = getNextChar();
        if (c == '\\')
            getNextChar();
        else if (c == '"')
            break;
    }
    return c == '"';
}

bool Reader::readObject(Token &) {
    Token tokenName;
    QByteArray name;
    currentValue() = Record(DataType::Object);
    while (readToken(tokenName)) {
        bool initialTokenOk = true;
        while (tokenName.type_ == tokenComment && initialTokenOk)
            initialTokenOk = readToken(tokenName);
        if (!initialTokenOk)
            break;
        if (tokenName.type_ == tokenObjectEnd && name.isEmpty()) // empty object
            return true;
        if (tokenName.type_ != tokenString)
            break;

        name = "";
        if (!decodeString(tokenName, name))
            return recoverFromError(tokenObjectEnd);

        Token colon;
        if (!readToken(colon) || colon.type_ != tokenMemberSeparator) {
            return addErrorAndRecover("Missing ':' after object member name",
                    colon, tokenObjectEnd);
        }
        Record &value = currentValue()[(const char*)name];
        nodes_.push(&value);
        bool ok = readValue();
        nodes_.pop();
        if (!ok) // error already set
            return recoverFromError(tokenObjectEnd);

        Token comma;
        if (!readToken(comma) || (comma.type_ != tokenObjectEnd && comma.type_
                != tokenArraySeparator)) {
            return addErrorAndRecover(
                    "Missing ',' or '}' in object declaration", comma,
                    tokenObjectEnd);
        }
        if (comma.type_ == tokenObjectEnd)
            return true;
    }
    return addErrorAndRecover("Missing '}' or object member name", tokenName,
            tokenObjectEnd);
}

bool Reader::readArray(Token &) {
    currentValue() = Record(DataType::Array);
    skipSpaces();
    if (*current_ == ']') // empty array
    {
        Token endArray;
        readToken(endArray);
        return true;
    }
    int index = 0;
    while (true) {
        Record &value = currentValue()[index++];
        nodes_.push(&value);
        bool ok = readValue();
        nodes_.pop();
        if (!ok) // error already set
            return recoverFromError(tokenArrayEnd);

        Token token;
        if (!readToken(token) || (token.type_ != tokenArraySeparator
                && token.type_ != tokenArrayEnd)) {
            return addErrorAndRecover(
                    "Missing ',' or ']' in array declaration", token,
                    tokenArrayEnd);
        }
        if (token.type_ == tokenArrayEnd)
            break;
    }
    return true;
}

typedef int Int;
typedef unsigned int UInt;
const Int minInt = Int(~(UInt(-1) / 2));
const Int maxInt = Int(UInt(-1) / 2);
const UInt maxUInt = UInt(-1);

bool Reader::decodeNumber(Token &token) {
    bool isDouble = false;
    for (Location inspect = token.start_; inspect != token.end_; ++inspect) {
        isDouble = isDouble || in(*inspect, '.', 'e', 'E', '+') || (*inspect
                == '-' && inspect != token.start_);
    }
    if (isDouble)
        return decodeDouble(token);
    Location current = token.start_;
    bool isNegative = *current == '-';
    if (isNegative)
        ++current;
    UInt threshold = (isNegative ? UInt(-minInt) : maxUInt) / 10;
    UInt value = 0;
    while (current < token.end_) {
        Char c = *current++;
        if (c < '0' || c > '9')
            return false;
        if (value >= threshold)
            return decodeDouble(token);
        value = value * 10 + UInt(c - '0');
    }
    if (isNegative)
        currentValue() = -Int(value);
    else if (value <= UInt(maxInt))
        currentValue() = Int(value);
    else
        currentValue() = value;
    return true;
}

bool Reader::decodeDouble(Token &token) {
    double value = 0;
    const int bufferSize = 32;
    int count;
    int length = int(token.end_ - token.start_);
    if (length <= bufferSize) {
        Char buffer[bufferSize];
        memcpy(buffer, token.start_, length);
        buffer[length] = 0;
        count = sscanf(buffer, "%lf", &value);
    } else {
        QByteArray buffer(token.start_, token.end_ - token.start_);
        count = sscanf(buffer, "%lf", &value);
    }

    if (count != 1)
        return false;
    currentValue() = value;
    return true;
}

bool Reader::decodeString(Token &token) {
    QByteArray decoded;
    if (!decodeString(token, decoded))
        return false;
    currentValue() = decoded.data();
    return true;
}

bool Reader::decodeString(Token &token, QByteArray &decoded) {
    decoded.reserve(token.end_ - token.start_ - 2);
    Location current = token.start_ + 1; // skip '"'
    Location end = token.end_ - 1; // do not include '"'
    while (current != end) {
        Char c = *current++;
        if (c == '"')
            break;
        else if (c == '\\') {
            if (current == end)
                return false;
            Char escape = *current++;
            switch (escape) {
            case '"':
                decoded += '"';
                break;
            case '/':
                decoded += '/';
                break;
            case '\\':
                decoded += '\\';
                break;
            case 'b':
                decoded += '\b';
                break;
            case 'f':
                decoded += '\f';
                break;
            case 'n':
                decoded += '\n';
                break;
            case 'r':
                decoded += '\r';
                break;
            case 't':
                decoded += '\t';
                break;
            case 'u': {
                unsigned int unicode;
                if (!decodeUnicodeEscapeSequence(token, current, end, unicode))
                    return false;
                appendUnicodeToUtf8(unicode, decoded);
            }
                break;
            default:
                return false;
            }
        } else {
            decoded += c;
        }
    }
    return true;
}

bool Reader::decodeUnicodeEscapeSequence(Token &, Location &current,
        Location end, unsigned int &unicode) {
    if (end - current < 4)
        return false;
    unicode = 0;
    for (int index = 0; index < 4; ++index) {
        Char c = *current++;
        unicode *= 16;
        if (c >= '0' && c <= '9')
            unicode += c - '0';
        else if (c >= 'a' && c <= 'f')
            unicode += c - 'a' + 10;
        else if (c >= 'A' && c <= 'F')
            unicode += c - 'A' + 10;
        else
            return false;
    }
    return true;
}

bool Reader::recoverFromError(TokenType skipUntilToken) {
    Token skip;
    while (true) {
        readToken(skip);
        if (skip.type_ == skipUntilToken || skip.type_ == tokenEndOfStream)
            break;
    }
    return false;
}

bool Reader::addErrorAndRecover(const QByteArray&, Token &, TokenType skipUntilToken) {
    return recoverFromError(skipUntilToken);
}

Record& Reader::currentValue() {
    return *(nodes_.top());
}

Reader::Char Reader::getNextChar() {
    if (current_ == end_)
        return 0;
    return *current_++;
}

void Reader::getLocationLineAndColumn(Location location, int &line, int &column) const {
    Location current = begin_;
    Location lastLineStart = current;
    line = 0;
    while (current < location && current != end_) {
        Char c = *current++;
        if (c == '\r') {
            if (*current == '\n')
                ++current;
            lastLineStart = current;
            ++line;
        } else if (c == '\n') {
            lastLineStart = current;
            ++line;
        }
    }
    // column & line start at 1
    column = int(location - lastLineStart) + 1;
    ++line;
}

QByteArray Reader::getLocationLineAndColumn(Location location) const {
    int line, column;
    getLocationLineAndColumn(location, line, column);
    char buffer[18 + 16 + 16 + 1];
    sprintf(buffer, "Line %d, Column %d", line, column);
    return buffer;
}
