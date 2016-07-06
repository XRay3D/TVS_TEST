#include "rigol_ds1102e.h"

#include "visa/visa.h"

RIGOL_DS1102E::RIGOL_DS1102E()
{

    /*=============================================*/
    ViUInt32 Nmatches;
    ViFindList List;
    char Matches[200];

    qDebug() << viOpenDefaultRM(&DefaultRM);
    qDebug() << viFindRsrc(DefaultRM, "USB?*", &List, &Nmatches, Matches);
    qDebug() << viOpen(DefaultRM, Matches, VI_NULL, VI_NULL, &Vi);
    qDebug() << "DS" << Vi;

    QByteArray Res;
    Res.fill(0, 100);
    qDebug() << SetComand("*IDN?");
    qDebug() << GetData(Res.data());
    Res.resize(strlen(Res.data()));
    qDebug() << Res;

    //CommandButton1_Click();
}

RIGOL_DS1102E::~RIGOL_DS1102E()
{
    if (Vi > 0) {
        qDebug() << viClose(Vi);
        qDebug() << viClose(DefaultRM);
    }
}

void RIGOL_DS1102E::CommandButton1_Click()
{
    if (Vi == 0)
        return;
    //    qDebug() << SetChannel(1, "COUP DC");
    //    qDebug() << SetChannel(2, "COUP DC");

    //    qDebug() << SetChannel(1, "DISP ON");
    //    qDebug() << SetChannel(2, "DISP ON");

    //    qDebug() << SetChannel(1, "INV ON");
    //    qDebug() << SetChannel(2, "INV OFF");

    //    qDebug() << SetChannel(1, "OFFS 0");
    //    qDebug() << SetChannel(2, "OFFS 0");

    //    qDebug() << SetChannel(1, "PROB 10"); //ATTENUATOR
    //    qDebug() << SetChannel(2, "PROB 10");

    //    qDebug() << SetChannel(1, "SCAL 10"); //voltage
    //    qDebug() << SetChannel(2, "SCAL 20"); //voltage

    //    qDebug() << SetComand(":MATH:DISPlay OFF");

    //    qDebug() << SetComand(":TRIG:EDGE:SOUR CHAN1");
    //    qDebug() << SetComand(":TRIG:EDGE:LEV 10");
    //    qDebug() << SetComand(":TRIG:EDGE:SWE NORM");
    //    qDebug() << SetComand(":TRIG:EDGE:COUP DC");
    //    qDebug() << SetComand(":TRIG:EDGE:SLOP NEG");

    //    qDebug() << SetComand(":TIM:MODE MAIN");
    //    qDebug() << SetComand(":TIM:OFFS 0.001");
    //    qDebug() << SetComand(":TIM:SCAL 0.0002");
    //    qDebug() << SetComand(":TIM:FORM YT");

    QByteArray Res;
    Res.fill(0, 1000);
    qDebug() << SetComand(":WAVeform:DATA? CHAN1");
    qDebug() << GetData(Res.data());
    qDebug() << Res;

    Res.fill(0, 1000);
    qDebug() << SetComand(":WAVeform:DATA? CHAN2");
    qDebug() << GetData(Res.data());
    qDebug() << Res;

    //    qDebug() << SetComand(":WAVeform:DATA? MATH");
    //    qDebug() << GetData(Res);
    //        For I = 1 To Len(Res)
    //            if( Asc(Mid(Res, I + 10, 1)) = 0 ) Exit For
    //            Sheets("Diagrama").Cells(I, 3) = CSng(127 - Asc(Mid(Res, I + 10, 1)))
    //        Next
}

ViStatus RIGOL_DS1102E::SetChannel(int chNum, char* s)
{
    if (Vi == 0)
        return -1;
    return viVPrintf(Vi, QString(":CHAN%1:%2\n").arg(chNum).arg(s).toLocal8Bit().data(), 0);
}

ViStatus RIGOL_DS1102E::SetComand(char* s)
{
    if (Vi == 0)
        return -1;
    return viPrintf(Vi, QString(s).append('\n').toLocal8Bit().data());
}

ViStatus RIGOL_DS1102E::GetData(char* s)
{
    if (Vi == 0)
        return -1;
    return viScanf(Vi, "%t\n", s);
}

ViStatus RIGOL_DS1102E::GetTestResult(double& v, double& i)
{
    if (Vi == 0)
        return -1;

    QByteArray Data;
    Data.fill(0, 100);
    SetComand(":MEASure:VMAX? CHAN1");
    GetData(Data.data());
    i = Data.toFloat();
    Data.fill(0, 100);
    SetComand(":MEASure:VMAX? CHAN2");
    GetData(Data.data());
    v = Data.toFloat();
    qDebug() << i << v << i * v;
}
