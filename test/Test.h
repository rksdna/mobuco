#ifndef TEST_H
#define TEST_H

#include <QTest>
#include <QObject>

class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = 0);

private slots:
    void outputRtuTest();
    void outputAsciiTest();
    void outputTcpTest();
    void inputRtuTest();
    void inputAsciiTest();
    void inputTcpTest();

};

#endif // TEST_H
