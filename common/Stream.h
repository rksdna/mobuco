#ifndef STREAM_H
#define STREAM_H

#include <QByteArray>

class InputStream
{
public:
    virtual ~InputStream();
};

class OutputStream
{
public:
    virtual ~OutputStream();

    virtual void writeBegin(quint8 slave) = 0;
    virtual void writeByte(quint8 value) = 0;
    virtual void writeWord(quint16 value) = 0;
    virtual void writeEnd() = 0;

    virtual QByteArray data() const = 0;

};

#endif // STREAM_H
