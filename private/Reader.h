/*
 * newReader.h
 *
 *  Created on: 2010-7-11
 *      Author: Administrator
 */

#ifndef NEWREADER_H_
#define NEWREADER_H_

#include <deque>
#include <stack>
#include <QByteArray>

class Record;

class Reader {
public:
    typedef char Char;
    typedef const Char *Location;

    Reader();

    bool parse(const char *beginDoc, const char *endDoc, Record &root);

private:
    enum TokenType {
        tokenEndOfStream = 0,
        tokenObjectBegin,
        tokenObjectEnd,
        tokenArrayBegin,
        tokenArrayEnd,
        tokenString,
        tokenNumber,
        tokenTrue,
        tokenFalse,
        tokenNull,
        tokenArraySeparator,
        tokenMemberSeparator,
        tokenComment,
        tokenError
    };

    class Token {
    public:
        TokenType type_;
        Location start_;
        Location end_;
    };

    class ErrorInfo {
    public:
        Token token_;
        QByteArray message_;
        Location extra_;
    };

    typedef std::deque<ErrorInfo> Errors;

    bool expectToken(TokenType type, Token &token, const char *message);
    bool readToken(Token &token);
    void skipSpaces();
    bool match(Location pattern, int patternLength);
    bool readString();
    void readNumber();
    bool readValue();
    bool readObject(Token &token);
    bool readArray(Token &token);
    bool decodeNumber(Token &token);
    bool decodeString(Token &token);
    bool decodeString(Token &token, QByteArray &decoded);
    bool decodeDouble(Token &token);
    bool decodeUnicodeEscapeSequence(Token &token, Location &current,
            Location end, unsigned int &unicode);
    bool recoverFromError(TokenType skipUntilToken);
    bool addErrorAndRecover(const QByteArray &message, Token &token,
            TokenType skipUntilToken);
    void skipUntilSpace();
    Record& currentValue();
    Char getNextChar();
    void getLocationLineAndColumn(Location location, int &line, int &column) const;
    QByteArray getLocationLineAndColumn(Location location) const;
    void skipCommentTokens(Token &token);

    typedef std::stack<Record *> Nodes;
    Nodes nodes_;
    QByteArray document_;
    Location begin_;
    Location end_;
    Location current_;
    Location lastValueEnd_;
    Record *lastValue_;
};

#endif /* NEWREADER_H_ */
