#include "tvs_tester.h"

TVS_TESTER::TVS_TESTER(QObject* parent)
    : QSerialPort(parent)
    , POLYNOMIAL(0x1D)
{
    qDebug() << "FindStend" << FindStend();
}

TVS_TESTER::~TVS_TESTER()
{
    close();
}

bool TVS_TESTER::FindStend()
{
    QMutexLocker locker(&mutex);

    close();
    QList<QSerialPortInfo> portList = QSerialPortInfo::availablePorts();
    foreach (QSerialPortInfo port, portList) {
        if (port.manufacturer().count("FTDI")) {

            setPort(port);
            setBaudRate(9600);
            setParity(NoParity);
            setFlowControl(NoFlowControl);

            if (open(QSerialPort::ReadWrite)) {
                //Sleep(100);
                write(Parcel(-1, 0));
                waitForReadyRead(1000);
                waitForReadyRead(100);
                if (CheckCrc(Data)) {
                    qDebug() << "FindStend OK";
                    return true;
                }
                else {
                    qDebug() << "FindStend ERR";
                }
                close();
            }
        }
    }
    return false;
}

void TVS_TESTER::SetCap(int i)
{
    if (!isOpen())
        return;
    QMutexLocker locker(&mutex);
    write(Parcel(0, i));
    waitForReadyRead(4000);
    waitForReadyRead(100);
    if (CheckCrc(readAll())) {
        qDebug() << "SetCap OK";
    }
    else {
        qDebug() << "SetCap ERR";
    }
}

void TVS_TESTER::Test()
{
    if (!isOpen())
        return;
    QMutexLocker locker(&mutex);

    write(Parcel(1, 0));
    waitForReadyRead(3000);
    waitForReadyRead(100);
    if (CheckCrc(readAll())) {
        qDebug() << "Test OK";
    }
    else {
        qDebug() << "Test ERR";
    }
    double Voltage, Current;
    emit MeasureReady(QString("%1\t%2\t%3").arg(Voltage).arg(Current).arg(Voltage * Current).replace('.', ','));
}

QByteArray& TVS_TESTER::Parcel(char Cmd1, char Cmd2)
{
    Data.clear();

    Data.push_back(85);
    Data.push_back(-86);
    Data.push_back(1);
    Data.push_back(Cmd1);
    Data.push_back(Cmd2);
    Data.push_back(1);

    Data[2] = Data.size();
    Data[Data.size() - 1] = CalcCrc(Data);

    //qDebug() << "Parcel" << Data.toHex().toUpper();

    return Data;
}

bool TVS_TESTER::CheckCrc(const QByteArray& Data)
{
    //qDebug() << "CheckCrc" << Data.toHex().toUpper();
    if (Data.size() >= 5) {
        if ((-1 == (Data[0] ^ Data[1])) && (Data[Data[2] - 1] == CalcCrc(Data))) {
            return true;
        }
    }
    return false;
}

char TVS_TESTER::CalcCrc(const QByteArray& Data)
{
    char crc8 = 0;
    for (int i = 0; i < Data.size() - 1; ++i) {
        crc8 = crc8 ^ Data[i];
        for (int j = 0; j < 8; ++j) {
            if (crc8 & 0x80) {
                crc8 = (crc8 << 1) ^ POLYNOMIAL;
            }
            else {
                crc8 <<= 1;
            }
        }
    }
    return crc8;
}
