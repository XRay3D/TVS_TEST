#include "rigol_ds1102e.h"

#include "visa/visa.h"

RIGOL_DS1102E::RIGOL_DS1102E()
{

    ViUInt32 Nmatches;
    ViFindList List;
    char Matches[200];

    viOpenDefaultRM(&DefaultRM);
    viFindRsrc(DefaultRM, (ViString) "USB?*", &List, &Nmatches, Matches);
    viOpen(DefaultRM, Matches, VI_NULL, VI_NULL, &Vi);

    SetComand("*IDN?");
    QByteArray Res;
    GetData(Res);
    if (Vi > 0) {
        connected = "ОСЦИЛЛОГРАФ ПОДКЛЮЧЕН - " + Res.split(',')[1] + " (" + QString().setNum(Vi) + ")";
    }
    else {
        connected = "ОСЦИЛЛОГРАФ НЕПОДКЛЮЧЕН!";
    }

    CommandButton1_Click();
}

RIGOL_DS1102E::~RIGOL_DS1102E()
{
    if (Vi > 0) {
        qDebug() << "viClose" << viClose(Vi);
        qDebug() << "viClose" << viClose(DefaultRM);
    }
}

void RIGOL_DS1102E::CommandButton1_Click()
{
    if (Vi == 0)
        return;

    //        qDebug() << SET_CHAN(1, "COUP DC");
    //        qDebug() << SET_CHAN(1, "DISP ON");
    //        qDebug() << SET_CHAN(1, "INV ON");
    //        qDebug() << SET_CHAN(1, "PROB 10"); //ATTENUATOR
    //        qDebug() << SET_CHAN(1, "SCAL " & Trim(str(GetCellVal(I, 13)))); //current
    //        qDebug() << SET_CHAN(1, "OFFS " & Trim(str(GetCellVal(I, 14))));

    //        qDebug() << SET_CHAN(2, "COUP DC");
    //        qDebug() << SET_CHAN(2, "INV OFF");
    //        qDebug() << SET_CHAN(2, "DISP ON");
    //        qDebug() << SET_CHAN(2, "PROB 10"); //ATTENUATOR
    //        qDebug() << SET_CHAN(2, "SCAL " & Trim(str(GetCellVal(I, 15)))); //voltage
    //        qDebug() << SET_CHAN(2, "OFFS " & Trim(str(GetCellVal(I, 16))));

    //        qDebug() << SET_COMAND(":MATH:DISPlay OFF");

    //        qDebug() << SET_COMAND(":TRIG:EDGE:SOUR CHAN1");
    //        qDebug() << SET_COMAND(":TRIG:EDGE:LEV " & Trim(str(GetCellVal(I, 17))));
    //        qDebug() << SET_COMAND(":TRIG:EDGE:SWE NORM");
    //        qDebug() << SET_COMAND(":TRIG:EDGE:COUP DC");
    //        qDebug() << SET_COMAND(":TRIG:EDGE:SLOP NEG");

    //        qDebug() << SET_COMAND(":TIM:MODE MAIN");
    //        qDebug() << SET_COMAND(":TIM:OFFS 0.001");
    //        qDebug() << SET_COMAND(":TIM:SCAL 0.0002");
    //        qDebug() << SET_COMAND(":TIM:FORM YT");

    //    SetChannel(1, "COUP DC");
    //    SetChannel(2, "COUP DC");

    //    SetChannel(1, "DISP ON");
    //    SetChannel(2, "DISP ON");

    //    SetChannel(1, "INV ON");
    //    SetChannel(2, "INV OFF");

    //    SetChannel(1, "OFFS 0");
    //    SetChannel(2, "OFFS 0");

    //    SetChannel(1, "PROB 10"); //ATTENUATOR
    //    SetChannel(2, "PROB 10");

    //    SetChannel(1, "SCAL 10"); //voltage
    //    SetChannel(2, "SCAL 20"); //voltage

    //    SetComand(":MATH:DISPlay OFF");

    //    SetComand(":TRIG:EDGE:SOUR CHAN1");
    //    SetComand(":TRIG:EDGE:LEV 10");
    //    SetComand(":TRIG:EDGE:SWE NORM");
    //    SetComand(":TRIG:EDGE:COUP DC");
    //    SetComand(":TRIG:EDGE:SLOP NEG");

    //    SetComand(":TIM:MODE MAIN");
    //    SetComand(":TIM:OFFS 0.001");
    //    SetComand(":TIM:SCAL 0.0002");
    //    SetComand(":TIM:FORM YT");

    QByteArray CHAN1;
    qDebug() << "SetComand" << SetComand(":WAVeform:DATA? CHAN1");
    qDebug() << "GetData" << GetData(CHAN1);
    CHAN1.remove(0, 10);

    QByteArray CHAN2;
    qDebug() << "SetComand" << SetComand(":WAVeform:DATA? CHAN2");
    qDebug() << "GetData" << GetData(CHAN2);
    CHAN2.remove(0, 10);

    emit addData(CHAN1, CHAN2);

    //    qDebug() << SetComand(":WAVeform:DATA? MATH");
    //    qDebug() << GetData(Res);
    //        For I = 1 To Len(Res)
    //            if( Asc(Mid(Res, I + 10, 1)) = 0 ) Exit For
    //            Sheets("Diagrama").Cells(I, 3) = CSng(127 - Asc(Mid(Res, I + 10, 1)))
    //        Next
}

ViStatus RIGOL_DS1102E::SetChannel(int chNum, const QString& s)
{
    if (Vi == 0)
        return -1;
    ViStatus Status = viVPrintf(Vi, QString(":CHAN%1:%2\n").arg(chNum).arg(s).toLocal8Bit().data(), 0);
    qDebug() << "SetChannel" << Status << s;
    return Status;
}

ViStatus RIGOL_DS1102E::SetComand(const QString& s)
{
    if (Vi == 0)
        return -1;
    return viPrintf(Vi, QString(s).append('\n').toLocal8Bit().data());
}

ViStatus RIGOL_DS1102E::GetData(QByteArray& data)
{
    if (Vi == 0)
        return -1;
    data.fill(0, 1000);
    ViStatus Status = viScanf(Vi, (ViString) "%t\n", data.data());
    data.resize(strlen(data.data()));
    return Status;
}

ViStatus RIGOL_DS1102E::GetTestResult(double& v, double& i)
{
    if (Vi == 0)
        return -1;

    QByteArray Data;
    SetComand(":MEASure:VMAX? CHAN1");
    GetData(Data);
    i = Data.toFloat();
    SetComand(":MEASure:VMAX? CHAN2");
    GetData(Data);
    v = Data.toFloat();
    qDebug() << i << v << i * v;
}
