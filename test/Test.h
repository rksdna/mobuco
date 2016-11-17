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

};

#endif // TEST_H
