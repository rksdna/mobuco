#include <QString>
#include "AsciiStream.h"

AsciiStream::AsciiStream()
{
}

void AsciiStream::writeBegin(quint8 slave)
{
    m_data.clear();
    m_data.append(slave);
}

void AsciiStream::writeByte(quint8 value)
{
    m_data.append(value);
}

void AsciiStream::writeWord(quint16 value)
{
    m_data.append(quint8(value >> 8));
    m_data.append(quint8(value));
}

void AsciiStream::writeEnd()
{
    m_data.append(checksum(m_data));

    m_data = QByteArray(":") + m_data.toHex().toUpper() + QByteArray("\r\n");
}

QByteArray AsciiStream::data() const
{
    return m_data;
}

quint8 AsciiStream::checksum(const QByteArray &data)
{
    quint8 result;
    foreach (quint8 value, data)
        result -= value;

    return result;
}
