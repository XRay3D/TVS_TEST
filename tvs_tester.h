#ifndef TVS_TESTER_H
#define TVS_TESTER_H

#include <QObject>
#include <QDebug>
#include <QtSerialPort>
//#include "rigol_ds1xxx.h"

class TVS_TESTER : /*public RIGOL_DS1102E,*/ public QSerialPort {
    Q_OBJECT
public:
    explicit TVS_TESTER(QObject* parent = 0);
    ~TVS_TESTER();

public:
    bool FindStend();
    void SetCap(int i);
    void Test();

private:
//    RIGOL_DS1XXX osc2;


    const char POLYNOMIAL;
    QByteArray Data;

    QByteArray& Parcel(char Cmd1, char Cmd2);
    bool CheckCrc(const QByteArray& Data);
    char CalcCrc(const QByteArray& Data);
    QMutex mutex;

signals:
    void MeasureReady(const QString& str);

public slots:
};

#endif // TVS_TESTER_H
