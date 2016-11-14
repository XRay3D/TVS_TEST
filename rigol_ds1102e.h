#ifndef RIGOL_DS1102E_H
#define RIGOL_DS1102E_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <qt_windows.h>

//#include "visa/visa.h"
#include "visa/visatype.h"
#include "visa/vpptype.h"

class RIGOL_DS1102E : public QObject {
    Q_OBJECT
public:
    explicit RIGOL_DS1102E();
    ~RIGOL_DS1102E();

    QString connected;

    void CommandButton1_Click();

    ViStatus SetChannel(int chNum, const QString& s);
    ViStatus SetComand(const QString& s);
    ViStatus GetData(QByteArray& data);

    ViStatus GetTestResult(double& v, double& i);
signals:
    void addData(QByteArray Current, QByteArray Voltage);

private:
    ViSession Vi;
    ViSession DefaultRM;
};

#endif( // RIGOL_DS1102E_H
