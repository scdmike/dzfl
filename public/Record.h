#ifndef _RECORD_H_
#define _RECORD_H_

#include <QStringList>
#pragma execution_character_set("utf-8")

namespace Literal { enum literal { True, False, Null }; }

namespace DataType {
    enum datatype {
        Undefined,
        String,
        UnquotedString,
        Literal,
        Number,
        FixedNumber,
        Array,
        Object,
        Nullval
    };
}

class Record {
public:
    Record& operator[](int index);
    Record& operator[](const char *name);
    Record& operator[](const QByteArray& name);
    Record& operator+=(const Record& nval);
    bool operator==(Record& v);
    bool operator!=(Record& v);
    Record& operator=(int);
    Record& operator=(long);
    Record& operator=(size_t);
    Record& operator=(qint64);
    Record& operator=(double);
    Record& operator=(const char *);
    Record& operator=(bool);
    Record& operator=(const QString& str);
    Record& operator=(const Record& other);
    Record& operator=(Literal::literal);

    operator int();
    operator long();
    operator size_t();
    operator qint64();
    operator double();
    operator float();
    operator const char*();
    operator bool();
    operator Literal::literal();

    bool Exists(const char* name);
    bool ReSize(size_t);
    bool Swap(Record &other);
    QList<QByteArray> keys();
    size_t Size();
    bool Erase(const char* name);
    bool Erase(int index);
    bool Clear();

    QByteArray ToString() const;
    bool FromString(const char* str, int len);
    bool FromString(const QString& str);

    Record();
    Record(int nval);
    Record(long nval);
    Record(size_t nval);
    Record(qint64 nval);
    Record(double nval);
    Record(const char *nval);
    Record(const QString& nval);
    Record(Literal::literal);
    Record(bool nval);
    Record(DataType::datatype);
    Record(const Record& nval);
    ~Record(void);
    DataType::datatype GetType();
private:
    bool SetLiteral(Literal::literal newval);
    bool SetLiteral(bool nval);
    bool SetLiteral();
    bool SetNumber(qint64 nval);
    bool SetNumber(double nval);
    bool SetString();
    bool SetString(const char *newval);
    bool SetArray();
    bool SetObject();
    bool SetDataType(DataType::datatype);
    bool Clone(const Record& oldval);
    bool DeleteValue();

private:
    DataType::datatype  dt;
    union DataPtr*      val;
};

#endif /* _RECORD_H_ */
