#include <QMap>
#include <QVector>
#include <limits>
#include <stdio.h>
#include "../public/Record.h"
using namespace std;

#define CheckCanSetValue { if (dt == DataType::Nullval) { return false; } DeleteValue();}
#define RecordInit  dt(DataType::Undefined), val(new DataPtr)

union DataPtr {
    void* _v;
    QByteArray* _string;
    Literal::literal _literal;
    double _number;
    qint64 _fixed_number;
    QMap<QByteArray, Record>*_object;
    QVector<Record>* _array;
};

Record& NullVal() {
    static Record val(DataType::Nullval);
    return val;
}

Record::Record() :
    RecordInit {

}
Record::Record(bool nval) :
    RecordInit {
    SetLiteral(nval);
}
Record::Record(Literal::literal nval) :
    RecordInit {
    SetLiteral(nval);
}
Record::Record(int nval) :
    RecordInit {
    SetNumber((qint64) nval);
}
Record::Record(long nval) :
    RecordInit {
    SetNumber((qint64) nval);
}
Record::Record(qint64 nval) :
    RecordInit {
    SetNumber(nval);
}
Record::Record(double nval) :
    RecordInit {
    SetNumber(nval);
}
Record::Record(const char *nval) :
    RecordInit {
    SetString(nval);
}

Record::Record(const QString& nval) :
    RecordInit {
    SetString(nval.toUtf8());
}

Record::Record(DataType::datatype ndt) :
    RecordInit {
    SetDataType(ndt);
}
Record::Record(const Record& nval) :
    RecordInit {
    Clone(nval);
}
Record::~Record(void) {
    DeleteValue();
    delete val;
}
bool Record::SetArray() {
    CheckCanSetValue;
    dt = DataType::Array;
    val->_array = new QVector<Record> ;
    return true;
}
bool Record::SetObject() {
    CheckCanSetValue;
    dt = DataType::Object;
    val->_object = new QMap<QByteArray, Record> ;
    return true;
}
bool Record::SetLiteral() {
    CheckCanSetValue;
    dt = DataType::Literal;
    val->_literal = Literal::Null;
    return true;
}
bool Record::SetDataType(DataType::datatype nv) {
    CheckCanSetValue;
    switch (nv) {
    case DataType::Array:
        return SetArray();
    case DataType::FixedNumber:
        return SetNumber((qint64) 0);
    case DataType::Literal:
        return SetLiteral(Literal::Null);
    case DataType::Number:
        return SetNumber(0.0);
    case DataType::Object:
        return SetObject();
    case DataType::UnquotedString:
    case DataType::String:
        return SetString();
    case DataType::Undefined:
        dt = DataType::Undefined;
        return true;
    case DataType::Nullval:
        dt = DataType::Nullval;
        return true;
    }
    return false;
}
bool Record::Clone(const Record& oldval) {
    switch (oldval.dt) {
    case DataType::UnquotedString:
    case DataType::String:
        SetString(oldval.val->_string->data());
        break;
    case DataType::Number:
        SetNumber(oldval.val->_number);
        break;
    case DataType::FixedNumber:
        SetNumber(oldval.val->_fixed_number);
        break;
    case DataType::Literal:
        SetLiteral(oldval.val->_literal);
        break;
    case DataType::Array:
        SetArray();
        *val->_array = *oldval.val->_array;
        break;
    case DataType::Object:
        SetObject();
        *val->_object = *oldval.val->_object;
        break;
    case DataType::Undefined:
    case DataType::Nullval:
    default:
        return false;
    }
    return true;

}

bool Record::SetNumber(double newval) {
    if (dt != DataType::Number) {
        CheckCanSetValue;
    }
    dt = DataType::Number;
    val->_number = newval;
    return true;
}

bool Record::SetNumber(qint64 newval) {
    if (dt != DataType::FixedNumber) {
        CheckCanSetValue;
    }
    dt = DataType::FixedNumber;
    val->_fixed_number = newval;
    return true;
}
bool Record::SetString() {
    CheckCanSetValue;
    dt = DataType::String;
    val->_string = new QByteArray;
    return true;
}
bool Record::SetString(const char *newval) {
    if (SetString()) {
        (*val->_string) = newval;
        return true;
    }
    return false;
}
bool Record::SetLiteral(bool newval) {
    return SetLiteral(newval ? Literal::True : Literal::False);
}
bool Record::SetLiteral(Literal::literal newval) {
    CheckCanSetValue;
    dt = DataType::Literal;
    val->_literal = newval;
    return true;
}
bool Record::Clear() {
    if (dt == DataType::Array) {
        val->_array->clear();
        return true;
    }
    if (dt == DataType::Object) {
        val->_object->clear();
        return true;
    }
    return false;
}
bool Record::DeleteValue() {
    if(val == NULL) val = new DataPtr;

    if (val->_v == NULL) {
        dt = DataType::Undefined;
        return true;
    }

    switch (dt) {
    case DataType::UnquotedString:
    case DataType::String:
        delete val->_string;
        break;
    case DataType::Number:
        val->_number = 0;
        break;
    case DataType::FixedNumber:
        val->_fixed_number = 0;
        break;
    case DataType::Literal:
        val->_literal = Literal::Null;
        break;
    case DataType::Array:
        delete val->_array;
        break;
    case DataType::Object:
        delete val->_object;
        break;
    case DataType::Undefined:
        return true;
    case DataType::Nullval:
    default:
        return false;
    }
    dt = DataType::Undefined;
    val->_v = NULL;
    return true;
}
bool Record::Exists(const char* name) {
    return dt == DataType::Object &&
           val->_object->find(name) != val->_object->end();
}
QList<QByteArray> Record::keys() {
    QList<QByteArray> ret;
    if (dt == DataType::Object) {
        return val->_object->keys();
    }
    return ret;
}
size_t Record::Size() {
    if (dt == DataType::Array) {
        return val->_array->size();
    } else if (dt == DataType::Object) {
        return val->_object->size();
    }
    return 0;
}
bool Record::ReSize(size_t size) {
    if (dt == DataType::Undefined) {
        SetArray();
    }
    if (dt != DataType::Array) {
        return false;
    }
    val->_array->resize(size);
    return true;
}
bool Record::Swap(Record &other) {
    if (dt == DataType::Nullval) {
        return false;
    }
    qSwap(dt, other.dt);
    qSwap(val, other.val);
    return true;
}
bool Record::Erase(const char *name) {
    if (dt != DataType::Object) {
        return false;
    }
    return val->_object->remove(name) > 0;
}
bool Record::Erase(int index) {
    if (dt == DataType::Array && val->_array->size() > index) {
        val->_array->erase(val->_array->begin() + index);
        return true;
    }
    return false;
}
Record& Record::operator[](int index) {
    if (dt == DataType::Undefined) {
        SetArray();
    }
    if (dt != DataType::Array) {
        return NullVal();
    }
    if (index >= val->_array->size()) {
        val->_array->resize(index + 1);
    }
    return (*val->_array)[index];
}

Record& Record::operator[](const char* name) {
    if (dt == DataType::Undefined) {
        SetObject();
    }
    if (dt != DataType::Object) {
        return NullVal();
    }
    return (*val->_object)[name];
}

Record& Record::operator[](const QByteArray& name) {
    if (dt == DataType::Undefined) {
        SetObject();
    }
    if (dt != DataType::Object) {
        return NullVal();
    }
    return (*val->_object)[name];
}

Record& Record::operator=(int nval) {
    return (*this) = (qint64) nval;
}
Record& Record::operator=(long nval) {
    return (*this) = (qint64) nval;
}
Record& Record::operator=(size_t nval) {
    return (*this) = (qint64) nval;
}
Record& Record::operator=(qint64 newval) {
    if (SetNumber(newval)) {
        return *this;
    }
    return NullVal();
}
Record& Record::operator=(double nval) {
    if (SetNumber(nval)) {
        return *this;
    }
    return NullVal();
}

Record& Record::operator=(const char * str) {
    if (SetString()) {
        (*val->_string) = str;
        return *this;
    }
    return NullVal();
}

Record& Record::operator=(const QString& str) {
    if (SetString()) {
        (*val->_string) = str.toUtf8();
        return *this;
    }
    return NullVal();
}

Record& Record::operator=(bool nval) {
    if (SetLiteral(nval)) {
        return *this;
    }
    return NullVal();
}
Record& Record::operator=(Literal::literal nval) {
    if (SetLiteral(nval)) {
        return *this;
    }
    return NullVal();
}
Record& Record::operator=(const Record& other){
    SetDataType(DataType::Undefined);
    Clone(other);
    return *this;
}

Record::operator int() {
    if (dt == DataType::Number) {
        return (int)val->_number;
    }
    if (dt == DataType::FixedNumber) {
        return (int)val->_fixed_number;
    }
    return 0;
}
Record::operator long() {
    if (dt == DataType::Number) {
        return (long)val->_number;
    }
    if (dt == DataType::FixedNumber) {
        return (long)val->_fixed_number;
    }
    return 0;
}
Record::operator size_t() {
    if (dt == DataType::Number) {
        return (size_t)val->_number;
    }
    if (dt == DataType::FixedNumber) {
        return (size_t)val->_fixed_number;
    }
    return 0;
}
Record::operator qint64() {
    if (dt == DataType::Number) {
        return (qint64)val->_number;
    }
    if (dt == DataType::FixedNumber) {
        return (qint64)val->_fixed_number;
    }
    return 0;
}
Record::operator double() {
    if (dt == DataType::Number) {
        return val->_number;
    }
    if (dt == DataType::FixedNumber) {
        return (double)val->_fixed_number;
    }
    return 0.0;
}
Record::operator float() {
    if (dt == DataType::Number) {
        return (float)val->_number;
    }
    if (dt == DataType::FixedNumber) {
        return (float)val->_fixed_number;
    }
    return 0.0;
}
Record::operator const char*() {
    if (dt == DataType::String) {
        return val->_string->data();
    }
    return "";
}

Record::operator bool() {
    switch (dt) {
    case DataType::Array:
        if (val->_array->size() > 0) {
            return true;
        }
        return false;
    case DataType::FixedNumber:
        if (val->_fixed_number == 0) {
            return false;
        }
        return true;
    case DataType::Literal:
        if (val->_literal == Literal::True) {
            return true;
        }
        return false;
    case DataType::Number:
        if (val->_number == 0) {
            return false;
        }
        return true;
    case DataType::Object:
        if (val->_object->size() > 0) {
            return true;
        }
        return false;
    case DataType::UnquotedString:
    case DataType::String:
        if (val->_string->length() == 0) {
            return false;
        }
        return true;
    default:
        break;
    }
    return false;
}
Record::operator Literal::literal() {
    if (dt == DataType::Literal) {
        return val->_literal;
    }
    return Literal::Null;
}

bool Record::operator!=(Record& v) {
    return !((*this) == v);
}
bool Record::operator==(Record& v) {
    if (v.dt == DataType::Undefined) {
        v = Literal::Null;
    }
    if (dt == DataType::Undefined) {
        *this = Literal::Null;
    }

    if (v.dt != dt) {
        return false;
    }
    switch (v.dt) {
    case DataType::Array:
    {
        QVector<Record>& p1 = *val->_array;
        QVector<Record>& p2 = *v.val->_array;
        if(p1.size() != p2.size()) return false;
        for(int i = 0; i < p1.size(); i++) {
            if(p1[i] != p2[i]) return false;
        }
        return true;
    }
    case DataType::FixedNumber:
        return this->val->_fixed_number == v.val->_fixed_number;
    case DataType::Literal:
        return this->val->_literal == v.val->_literal;
    case DataType::Number:
        return qAbs(this->val->_number - v.val->_number) <= numeric_limits<double>::epsilon();
    case DataType::Object:
        if (val->_object->size() != v.val->_object->size()) {
            return false;
        }
        {
            QMap<QByteArray, Record>::Iterator oi, oj;
            for (oi = val->_object->begin(), oj = v.val->_object->begin(); oi
                    != val->_object->end(); ++oi, ++oj) {
                if (oi.key() != oj.key() || oi.value() != oj.value()) {
                    return false;
                }
            }
        }
        return true;
    case DataType::UnquotedString:
    case DataType::String:
        return (*v.val->_string) == (*this->val->_string);
    case DataType::Undefined:
        return true;
    case DataType::Nullval:
        return true;
    }
    return false;
}
DataType::datatype Record::GetType() {
    return dt;
}
void replace_all(QByteArray &srcstr, const char *search, const char *replace) {
    size_t searchlen = strlen(search);
    size_t replacelen = strlen(replace);
    int fnd = 0;
    int schstart = 0;
    while ((fnd = srcstr.indexOf(search, schstart)) >= 0) {
        srcstr.replace(fnd, searchlen, replace);
        schstart = fnd + replacelen;
    }
}
void quotestring(QByteArray &thestr) {
    replace_all(thestr, "\\", "\\\\");
    replace_all(thestr, "\"", "\\\"");
    replace_all(thestr, "\n", "\\n");
    replace_all(thestr, "\r", "\\r");
    QByteArray tmpstr = thestr;
    thestr = "\"";
    thestr += tmpstr;
    thestr += "\"";
}
#ifdef MSVC
#define snprintf _snprintf
#endif

QByteArray Record::ToString() const {
    QByteArray ret;
    char strnum[40];
    switch (dt) {
    case DataType::UnquotedString:
    case DataType::String:
        ret = *val->_string;
        quotestring(ret);
        break;
    case DataType::FixedNumber:
        ret = QByteArray::number((qlonglong)val->_fixed_number);
        break;
    case DataType::Number:
#ifdef _WIN32
        _snprintf(strnum, 38, "%d.%05d", (int)val->_number, (int)((val->_number - (int)val->_number) * 100000));
#else
        snprintf(strnum, 38, "%d.%05d", (int)val->_number, (int)((val->_number - (int)val->_number) * 100000));
#endif

        ret = strnum;
        break;
    case DataType::Literal:
        switch (val->_literal) {
        case Literal::False:
            ret = "false";
            break;
        case Literal::True:
            ret = "true";
            break;
        case Literal::Null:
            ret = "null";
            break;
        default:
            return ret;
        }
        break;
    case DataType::Array: {
        QString astr = ret;
        astr += "[";
        QVector<Record>::iterator it;
        bool started = false;
        for (it = val->_array->begin(); it != val->_array->end(); ++it) {
            if (started) {
                astr += ", ";
            } else {
                started = true;
            }
            astr += it->ToString();
        }
        astr += "]";
        ret = astr.toUtf8();
        break;
    }
    case DataType::Object: {
        QByteArray thestr = ret;
        thestr += "{";
        bool started = false;
        for (QMap<QByteArray, Record>::ConstIterator it = val->_object->begin(); it != val->_object->end(); ++it) {
            if (started) {
                thestr += ", ";
            } else {
                started = true;
            }
            QByteArray namestr = it.key();
            quotestring(namestr);
            thestr += namestr;
            thestr += ":";
            thestr += it.value().ToString();
        }

        thestr += "}";
        ret = thestr;
        break;
    }
    case DataType::Nullval:
    case DataType::Undefined:
        ret = "null";
        break;
    }
    return ret;
}
#include "Reader.h"
bool Record::FromString(const char* str, int len){
    SetDataType(DataType::Undefined);
    Reader reader;
    return reader.parse(str, str + len, *this);
}

bool Record::FromString(const QString& str){
    QByteArray byteArray = str.toUtf8();
    SetDataType(DataType::Undefined);
    Reader reader;
    return reader.parse(byteArray.data(), byteArray.data() + byteArray.length(), *this);
}
