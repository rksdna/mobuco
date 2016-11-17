#ifndef ASCIISTREAM_H
#define ASCIISTREAM_H

#include <Stream.h>

class AsciiStream : public InputStream, public OutputStream
{
public:
    AsciiStream();

    void writeBegin(quint8 slave);
    void writeByte(quint8 value);
    void writeWord(quint16 value);
    void writeEnd();

    QByteArray data() const;

private:
    static quint8 checksum(const QByteArray &data);

private:
    QByteArray m_data;
};

#endif // ASCIISTREAM_H
