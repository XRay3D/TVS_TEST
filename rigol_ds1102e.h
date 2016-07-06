#ifndef RIGOL_DS1102E_H
#define RIGOL_DS1102E_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <qt_windows.h>

//#include "visa/visa.h"
#include "visa/visatype.h"
#include "visa/vpptype.h"

class RIGOL_DS1102E {
public:
    explicit RIGOL_DS1102E();
    ~RIGOL_DS1102E();

    //    void Ini_DS(int I)
    //    {
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
    //    }

    void CommandButton1_Click();

    ViStatus SetChannel(int chNum, char* s);

    ViStatus SetComand(char* s);

    ViStatus GetData(char* s);

    ViStatus GetTestResult(double& v, double& i);

private:
    char Res[10000];
    ViSession Vi;
    ViSession DefaultRM;
};

#endif( // RIGOL_DS1102E_H
