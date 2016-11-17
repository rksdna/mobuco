#ifndef RTUSTREAM_H
#define RTUSTREAM_H

#include <Stream.h>

class RtuStream : public InputStream, public OutputStream
{
public:
    RtuStream();

    void writeBegin(quint8 slave);
    void writeByte(quint8 value);
    void writeWord(quint16 value);
    void writeEnd();

    QByteArray data() const;

private:
    static quint16 checksum(const QByteArray &data);

private:
    QByteArray m_data;
};

#endif // RTUSTREAM_H
