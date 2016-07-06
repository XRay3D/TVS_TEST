/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef TABLEEDITOR_H
#define TABLEEDITOR_H

#include <QDialog>

#include <QtWidgets>
#include <QtSql>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QPushButton;
class QSqlTableModel;
QT_END_NAMESPACE

//! [0]
class TableEditor : public QWidget {
    Q_OBJECT

public:
    explicit TableEditor(/*const QString &tableName,*/ QWidget* parent = 0);
    typedef struct {
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
        int BowerVoltage; //	11
        float ScaleCh1VoltageCurrent; //	12
        float OffsetCh1VoltageCurrent; //	13
        float ScaleCh2VoltageVoltage; //	14
        float OffsetCh2Voltage; //	15
        float TriggerLevelVoltageMul_10; //	16
        float CapacitanceMul_22Uf; //	17
        bool Enable; //	18
    } TVS_DIODE;

private slots:
    void submit();

private:
    QPushButton* submitButton;
    QPushButton* revertButton;
    QPushButton* quitButton;

    QPushButton* addButton;

    QPushButton* deleteButton;

    QDialogButtonBox* buttonBox;
    QSqlTableModel* model;

    QString tableName;

    void Add();
    void Delete();

    bool myQery(const TVS_DIODE& params)
    {
        QSqlQuery query;
        //query.exec("insert into person values(101, 'Danny', 'Young')");
        return query.exec(QString("insert into tvs values(%1,\'%2\',\'%3',\'%4\',%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16,%17,%18,%19)").arg(params.Number).arg(params.DeviceType).arg(params.DeviceMarkingCodeUni).arg(params.DeviceMarkingCodeBi).arg(params.BreakdownVoltageVbrAtITMinVoltage).arg(params.BreakdownVoltageVbrAtITMaxVoltage).arg(params.TestCurrentItMiliAmpere).arg(params.StandOffVoltageVwmVoltage).arg(params.MaximumReverseLeakageAtVwmIdMicroAmpere).arg(params.MaximumPeakPulseSurgeCurrentIppmAmpere).arg(params.MaximumClampingVoltageAtIppmVcVoltage).arg(params.BowerVoltage).arg(params.ScaleCh1VoltageCurrent).arg(params.OffsetCh1VoltageCurrent).arg(params.ScaleCh2VoltageVoltage).arg(params.OffsetCh2Voltage).arg(params.TriggerLevelVoltageMul_10).arg(params.CapacitanceMul_22Uf).arg(params.Enable));
    }
};
//! [0]

#endif
