#include "TcpStream.h"

TcpStream::TcpStream()
{
}

void TcpStream::writeBegin(quint8 slave)
{
    m_data.clear();
    m_data.append(slave);
}

void TcpStream::writeByte(quint8 value)
{
    m_data.append(value);
}

void TcpStream::writeWord(quint16 value)
{
    m_data.append(quint8(value >> 8));
    m_data.append(quint8(value));
}

void TcpStream::writeEnd()
{
    m_data.prepend(header(1, 0, m_data.size()));
}

QByteArray TcpStream::data() const
{
    return m_data;
}

void TcpStream::setData(const QByteArray &data)
{
    m_data.clear();
}

QByteArray TcpStream::header(quint16 transaction, quint16 protocol, quint16 size)
{
    QByteArray result;
    result.append(quint8(transaction >> 8));
    result.append(quint8(transaction));
    result.append(quint8(protocol >> 8));
    result.append(quint8(protocol));
    result.append(quint8(size >> 8));
    result.append(quint8(size));

    return result;
}
