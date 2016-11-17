#ifndef TCPSTREAM_H
#define TCPSTREAM_H

#include <Stream.h>

class TcpStream : public InputStream, public OutputStream
{
public:
    TcpStream();

    void writeBegin(quint8 slave);
    void writeByte(quint8 value);
    void writeWord(quint16 value);
    void writeEnd();

    QByteArray data() const;
    void setData(const QByteArray &data);

private:
    static QByteArray header(quint16 transaction, quint16 protocol, quint16 size);

private:
    QByteArray m_data;
};

#endif // TCPSTREAM_H
