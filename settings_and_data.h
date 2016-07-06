#ifndef SETTINGS_AND_DATA_H
#define SETTINGS_AND_DATA_H

#include <QDialog>

#include <QtSql>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QScrollBar>
#include <QMessageBox>
#include <QTimerEvent>

typedef struct TVS_DIODE {
    TVS_DIODE(
        int Number = 0,
        QString DeviceType = "",
        QString DeviceMarkingCodeUni = "",
        QString DeviceMarkingCodeBi = "",
        float BreakdownVoltageVbrAtITMinVoltage = 0.0f,
        float BreakdownVoltageVbrAtITMaxVoltage = 0.0f,
        float TestCurrentItMiliAmpere = 0.0f,
        float StandOffVoltageVwmVoltage = 0.0f,
        float MaximumReverseLeakageAtVwmIdMicroAmpere = 0.0f,
        float MaximumPeakPulseSurgeCurrentIppmAmpere = 0.0f,
        float MaximumClampingVoltageAtIppmVcVoltage = 0.0f,
        float BowerVoltage = 0,
        float ScaleCh1VoltageCurrent = 0.0f,
        float OffsetCh1VoltageCurrent = 0.0f,
        float ScaleCh2VoltageVoltage = 0.0f,
        float OffsetCh2Voltage = 0.0f,
        float TriggerLevelVoltageMul_10 = 0.0f,
        float CapacitanceMul_22Uf = 0.0f,
        bool Enable = 0)
        : Number(Number)
        , DeviceType(DeviceType)
        , DeviceMarkingCodeUni(DeviceMarkingCodeUni)
        , DeviceMarkingCodeBi(DeviceMarkingCodeBi)
        , BreakdownVoltageVbrAtITMinVoltage(BreakdownVoltageVbrAtITMinVoltage)
        , BreakdownVoltageVbrAtITMaxVoltage(BreakdownVoltageVbrAtITMaxVoltage)
        , TestCurrentItMiliAmpere(TestCurrentItMiliAmpere)
        , StandOffVoltageVwmVoltage(StandOffVoltageVwmVoltage)
        , MaximumReverseLeakageAtVwmIdMicroAmpere(MaximumReverseLeakageAtVwmIdMicroAmpere)
        , MaximumPeakPulseSurgeCurrentIppmAmpere(MaximumPeakPulseSurgeCurrentIppmAmpere)
        , MaximumClampingVoltageAtIppmVcVoltage(MaximumClampingVoltageAtIppmVcVoltage)
        , BowerVoltage(BowerVoltage)
        , ScaleCh1VoltageCurrent(ScaleCh1VoltageCurrent)
        , OffsetCh1VoltageCurrent(OffsetCh1VoltageCurrent)
        , ScaleCh2VoltageVoltage(ScaleCh2VoltageVoltage)
        , OffsetCh2Voltage(OffsetCh2Voltage)
        , TriggerLevelVoltageMul_10(TriggerLevelVoltageMul_10)
        , CapacitanceMul_22Uf(CapacitanceMul_22Uf)
        , Enable(Enable)
    {
    }
    int Number; //	0
    QString DeviceType; //	1
    QString DeviceMarkingCodeUni; //	2
    QString DeviceMarkingCodeBi; //	3
    float BreakdownVoltageVbrAtITMinVoltage; //	4
    float BreakdownVoltageVbrAtITMaxVoltage; //	5
    float TestCurrentItMiliAmpere; //	6
    float StandOffVoltageVwmVoltage; //	7
    float MaximumReverseLeakageAtVwmIdMicroAmpere; //	8
    float MaximumPeakPulseSurgeCurrentIppmAmpere; //	9
    float MaximumClampingVoltageAtIppmVcVoltage; //	10
    ////////////	//
    float BowerVoltage; //	11
    float ScaleCh1VoltageCurrent; //	12
    float OffsetCh1VoltageCurrent; //	13
    float ScaleCh2VoltageVoltage; //	14
    float OffsetCh2Voltage; //	15
    float TriggerLevelVoltageMul_10; //	16
    float CapacitanceMul_22Uf; //	17
    bool Enable; //	18
} TVS_DIODE;

namespace Ui {
class SETTINGS_AND_DATA;
}

class SETTINGS_AND_DATA : public QDialog {
    Q_OBJECT

public:
    explicit SETTINGS_AND_DATA(QWidget* parent = 0);
    ~SETTINGS_AND_DATA();

    QStringList TVSList();

private:
    Ui::SETTINGS_AND_DATA* ui;
    bool createConnection();
    QSqlDatabase db;
    QSqlTableModel* model;

    QString tableName;

    int sf;
    //    bool myQery(const TVS_DIODE& params)
    //    {
    //        QSqlQuery query;
    //        query.exec("create table tvs (Number int primary key, DeviceType varchar(20), DeviceMarkingCodeUni varchar(20), DeviceMarkingCodeBi varchar(20), BreakdownVoltageVbrAtITMinVoltage float, BreakdownVoltageVbrAtITMaxVoltage float, TestCurrentItMiliAmpere float, StandOffVoltageVwmVoltage float, MaximumReverseLeakageAtVwmIdMicroAmpere float, MaximumPeakPulseSurgeCurrentIppmAmpere float, MaximumClampingVoltageAtIppmVcVoltage float, BowerVoltage float, ScaleCh1VoltageCurrent float, OffsetCh1VoltageCurrent float, ScaleCh2VoltageVoltage float, OffsetCh2Voltage float, TriggerLevelVoltageMul_10 float, CapacitanceMul_22Uf float, Enable bool )");
    //        TVS_DIODE tvs;
    //        tvs.Number = 20;
    //        tvs.DeviceType = "SMCJ24A";
    //        tvs.DeviceMarkingCodeUni = "GEZ";
    //        tvs.DeviceMarkingCodeBi = "BEZ";
    //        tvs.BreakdownVoltageVbrAtITMinVoltage = 26.7f;
    //        tvs.BreakdownVoltageVbrAtITMaxVoltage = 29.5f;
    //        tvs.TestCurrentItMiliAmpere = 1;
    //        tvs.StandOffVoltageVwmVoltage = 24;
    //        tvs.MaximumReverseLeakageAtVwmIdMicroAmpere = 1;
    //        tvs.MaximumPeakPulseSurgeCurrentIppmAmpere = 38.6f;
    //        tvs.MaximumClampingVoltageAtIppmVcVoltage = 38.9f;
    //        tvs.BowerVoltage = 200;
    //        tvs.ScaleCh1VoltageCurrent = 10;
    //        tvs.OffsetCh1VoltageCurrent = -30;
    //        tvs.ScaleCh2VoltageVoltage = 10;
    //        tvs.OffsetCh2Voltage = -30;
    //        tvs.TriggerLevelVoltageMul_10 = 10;
    //        tvs.CapacitanceMul_22Uf = 22;
    //        tvs.Enable = 1;
    //        myQery(tvs);
    //        //query.exec("insert into person values(101, 'Danny', 'Young')");
    //        return query.exec(QString("insert into tvs values(%1,\'%2\',\'%3',\'%4\',%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16,%17,%18,%19)").arg(params.Number).arg(params.DeviceType).arg(params.DeviceMarkingCodeUni).arg(params.DeviceMarkingCodeBi).arg(params.BreakdownVoltageVbrAtITMinVoltage).arg(params.BreakdownVoltageVbrAtITMaxVoltage).arg(params.TestCurrentItMiliAmpere).arg(params.StandOffVoltageVwmVoltage).arg(params.MaximumReverseLeakageAtVwmIdMicroAmpere).arg(params.MaximumPeakPulseSurgeCurrentIppmAmpere).arg(params.MaximumClampingVoltageAtIppmVcVoltage).arg(params.BowerVoltage).arg(params.ScaleCh1VoltageCurrent).arg(params.OffsetCh1VoltageCurrent).arg(params.ScaleCh2VoltageVoltage).arg(params.OffsetCh2Voltage).arg(params.TriggerLevelVoltageMul_10).arg(params.CapacitanceMul_22Uf).arg(params.Enable));
    //    }

private slots:
    void submit();
    void on_defaultButton_clicked();
    void on_checkBox_clicked(bool checked);

signals:
    void HideEvent();

    // QWidget interface
protected:
    void hideEvent(QHideEvent*);
    void showEvent(QShowEvent*);
    void paintEvent(QPaintEvent*);

    // QObject interface
protected:
    void timerEvent(QTimerEvent *te);
};

#endif // SETTINGS_AND_DATA_H
