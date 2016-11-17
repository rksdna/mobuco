#include "Test.h"
#include "TcpStream.h"
#include "RtuStream.h"
#include "AsciiStream.h"

Test::Test(QObject *parent) :
    QObject(parent)
{
}

void Test::outputRtuTest()
{
    RtuStream stream;
    stream.writeBegin(0x11);
    stream.writeByte(0x01);
    stream.writeWord(0x0013);
    stream.writeWord(0x0025);
    stream.writeEnd();
    QCOMPARE(stream.data(), QByteArray::fromHex("1101001300250E84"));

    stream.writeBegin(0x11);
    stream.writeByte(0x0F);
    stream.writeWord(0x0013);
    stream.writeWord(0x000A);
    stream.writeByte(0x02);
    stream.writeByte(0xCD);
    stream.writeByte(0x01);
    stream.writeEnd();
    QCOMPARE(stream.data(), QByteArray::fromHex("110F0013000A02CD01BF0B"));
}

void Test::outputAsciiTest()
{
    AsciiStream stream;
    stream.writeBegin(0x11);
    stream.writeByte(0x03);
    stream.writeWord(0x006B);
    stream.writeWord(0x0003);
    stream.writeEnd();

    QCOMPARE(QString::fromLocal8Bit(stream.data()), QString::fromLocal8Bit(QByteArray(":1103006B00037E\r\n")));
}

void Test::outputTcpTest()
{
    TcpStream stream;
    stream.writeBegin(0x11);
    stream.writeByte(0x03);
    stream.writeWord(0x006B);
    stream.writeWord(0x0003);
    stream.writeEnd();

    QCOMPARE(stream.data(), QByteArray::fromHex("0001000000061103006B0003"));
}

void Test::inputRtuTest()
{
    RtuStream stream;
    stream.setData(QByteArray::fromHex("1101001300250E84"));

    QCOMPARE(stream.data(), QByteArray::fromHex("110100130025"));

    stream.setData(QByteArray::fromHex("110F0013000A02CD01BF0B"));

    QCOMPARE(stream.data(), QByteArray::fromHex("110F0013000A02CD01"));

    stream.setData(QByteArray::fromHex("1101001300250E8"));

    QCOMPARE(stream.data(), QByteArray());
}

void Test::inputAsciiTest()
{
    AsciiStream stream;
    stream.setData(":1103006B00037E\r\n");

    QCOMPARE(stream.data(), QByteArray::fromHex("1103006B0003"));

    stream.setData(":1103006B0007E\r\n");

    QCOMPARE(stream.data(), QByteArray());
}

void Test::inputTcpTest()
{

}
