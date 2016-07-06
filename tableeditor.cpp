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
** * Redistributions of source code must retain the above copyright
** notice, this list of conditions and the following disclaimer.
** * Redistributions in binary form must reproduce the above copyright
** notice, this list of conditions and the following disclaimer in
** the documentation and/or other materials provided with the
** distribution.
** * Neither the name of The Qt Company Ltd nor the names of its
** contributors may be used to endorse or promote products derived
** from this software without specific prior written permission.
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

#include "tableeditor.h"

//! [0]
TableEditor::TableEditor(QWidget* parent)
    : QWidget(parent)
    , tableName("TVS")
{
    return;

    // QString path = qApp->applicationDirPath().append('/').replace('/', '\\');
    // QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    // // db.setDatabaseName("DRIVER={Microsoft Excel Driver(*.xls, )};DBQ=" + QString("Лист Microsoft Excel.xlsx"));
    // // db.setDatabaseName("provider=MSDASQL;DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ=" + path + QString("Лист Microsoft Excel.xlsx") + ";DriverID=790");
    // db.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ=" + path + QString("TVS.xlsx") + ";DriverID=790");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("customdb.db");

    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."),
            QMessageBox::Cancel);
        return;
    }

    Add();
    db.close();
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."),
            QMessageBox::Cancel);
        return;
    }
    model = new QSqlTableModel(this, db);
    model->setTable("tvs");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    //    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    //    model->setHeaderData(1, Qt::Horizontal, tr("First name"));
    //    model->setHeaderData(2, Qt::Horizontal, tr("Last name"));

    model->setHeaderData(0, Qt::Horizontal, tr(" 0 "));
    model->setHeaderData(1, Qt::Horizontal, tr(" 1 "));
    model->setHeaderData(2, Qt::Horizontal, tr(" 2 "));
    model->setHeaderData(3, Qt::Horizontal, tr(" 3 "));
    model->setHeaderData(4, Qt::Horizontal, tr(" 4 "));
    model->setHeaderData(5, Qt::Horizontal, tr(" 5 "));
    model->setHeaderData(6, Qt::Horizontal, tr(" 6 "));
    model->setHeaderData(7, Qt::Horizontal, tr(" 7 "));
    model->setHeaderData(8, Qt::Horizontal, tr(" 8 "));
    model->setHeaderData(9, Qt::Horizontal, tr(" 9 "));
    model->setHeaderData(10, Qt::Horizontal, tr(" 10 "));
    model->setHeaderData(11, Qt::Horizontal, tr(" 11 "));
    model->setHeaderData(12, Qt::Horizontal, tr(" 12 "));
    model->setHeaderData(13, Qt::Horizontal, tr(" 13 "));
    model->setHeaderData(14, Qt::Horizontal, tr(" 14 "));
    model->setHeaderData(15, Qt::Horizontal, tr(" 15 "));
    model->setHeaderData(16, Qt::Horizontal, tr(" 16 "));
    model->setHeaderData(17, Qt::Horizontal, tr(" 17 "));
    model->setHeaderData(18, Qt::Horizontal, tr(" 18 "));
    model->setHeaderData(19, Qt::Horizontal, tr(" 19 "));

    //! [0] //! [1]
    QTableView* view = new QTableView;
    view->setModel(model);
    view->resizeColumnsToContents();
    //! [1]

    //! [2]
    submitButton = new QPushButton(tr("Submit"));
    submitButton->setDefault(true);

    revertButton = new QPushButton(tr("&Revert"));

    quitButton = new QPushButton(tr("Quit"));

    addButton = new QPushButton(tr("addButton"));
    deleteButton = new QPushButton(tr("deleteButton"));

    buttonBox = new QDialogButtonBox(Qt::Vertical);
    buttonBox->addButton(submitButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(revertButton, QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    buttonBox->addButton(addButton, QDialogButtonBox::RejectRole);
    buttonBox->addButton(deleteButton, QDialogButtonBox::RejectRole);
    //! [2]

    //! [3]
    connect(submitButton, SIGNAL(clicked()), this, SLOT(submit()));
    connect(revertButton, SIGNAL(clicked()), model, SLOT(revertAll()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    connect(addButton, &QPushButton::clicked, this, &TableEditor::Add);
    connect(deleteButton, &QPushButton::clicked, this, &TableEditor::Delete);
    //! [3]

    //! [4]
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(view);
    mainLayout->addWidget(buttonBox);

    mainLayout->setMargin(0);

    setLayout(mainLayout);

    setWindowTitle(tr("Cached Table"));
}
//! [4]

//! [5]
void TableEditor::submit()
{
    model->database().transaction();
    if (model->submitAll()) {
        model->database().commit();
    }
    else {
        model->database().rollback();
        QMessageBox::warning(this, tr("Cached Table"),
            tr("The database reported an error: %1")
                .arg(model->lastError().text()));
    }
}

void TableEditor::Add()
{
    qDebug() << "create table";
    QSqlQuery query;

    query.exec("create table tvs (Number int primary key, DeviceType varchar(20), DeviceMarkingCodeUni varchar(20), DeviceMarkingCodeBi varchar(20), BreakdownVoltageVbrAtITMinVoltage float, BreakdownVoltageVbrAtITMaxVoltage float, TestCurrentItMiliAmpere float, StandOffVoltageVwmVoltage float, MaximumReverseLeakageAtVwmIdMicroAmpere float, MaximumPeakPulseSurgeCurrentIppmAmpere float, MaximumClampingVoltageAtIppmVcVoltage float, ////////////, BowerVoltage int, ScaleCh1VoltageCurrent float, OffsetCh1VoltageCurrent float, ScaleCh2VoltageVoltage float, OffsetCh2Voltage float, TriggerLevelVoltageMul_10 float, CapacitanceMul_22Uf float, Enable bool )");

    TVS_DIODE tvs;
    tvs.Number = 20;
    tvs.DeviceType = "SMCJ24A";
    tvs.DeviceMarkingCodeUni = "GEZ";
    tvs.DeviceMarkingCodeBi = "BEZ";
    tvs.BreakdownVoltageVbrAtITMinVoltage = 26.7f;
    tvs.BreakdownVoltageVbrAtITMaxVoltage = 29.5f;
    tvs.TestCurrentItMiliAmpere = 1;
    tvs.StandOffVoltageVwmVoltage = 24;
    tvs.MaximumReverseLeakageAtVwmIdMicroAmpere = 1;
    tvs.MaximumPeakPulseSurgeCurrentIppmAmpere = 38.6f;
    tvs.MaximumClampingVoltageAtIppmVcVoltage = 38.9f;
    tvs.BowerVoltage = 200;
    tvs.ScaleCh1VoltageCurrent = 10;
    tvs.OffsetCh1VoltageCurrent = -30;
    tvs.ScaleCh2VoltageVoltage = 10;
    tvs.OffsetCh2Voltage = -30;
    tvs.TriggerLevelVoltageMul_10 = 10;
    tvs.CapacitanceMul_22Uf = 22;
    tvs.Enable = 1;
    myQery(tvs);
    // query.exec("insert into " + tableName + " values(101, 'Danny', 'Young')");
    // query.exec("insert into " + tableName + " values(102, 'Christine', 'Holand')");
    // query.exec("insert into " + tableName + " values(103, 'Lars', 'Gordon')");
    // query.exec("insert into " + tableName + " values(104, 'Roberto', 'Robitaille')");
    // query.exec("insert into " + tableName + " values(105, 'Maria', 'Papadopoulos')");

    query.exec("create table items (id int primary key,"
               "imagefile int,"
               "itemtype varchar(20),"
               "description varchar(100))");
    query.exec("insert into items "
               "values(0, 0, 'Qt',"
               "'Qt is a full development framework with tools designed to "
               "streamline the creation of stunning applications and "
               "amazing user interfaces for desktop, embedded and mobile "
               "platforms.')");
    query.exec("insert into items "
               "values(1, 1, 'Qt Quick',"
               "'Qt Quick is a collection of techniques designed to help "
               "developers create intuitive, modern-looking, and fluid "
               "user interfaces using a CSS & JavaScript like language.')");
    query.exec("insert into items "
               "values(2, 2, 'Qt Creator',"
               "'Qt Creator is a powerful cross-platform integrated "
               "development environment (IDE), including UI design tools "
               "and on-device debugging.')");
    query.exec("insert into items "
               "values(3, 3, 'Qt Project',"
               "'The Qt Project governs the open source development of Qt, "
               "allowing anyone wanting to contribute to join the effort "
               "through a meritocratic structure of approvers and "
               "maintainers.')");

    query.exec("create table images (itemid int, file varchar(20))");
    query.exec("insert into images values(0, 'images/qt-logo.png')");
    query.exec("insert into images values(1, 'images/qt-quick.png')");
    query.exec("insert into images values(2, 'images/qt-creator.png')");
    query.exec("insert into images values(3, 'images/qt-project.png')");
}

void TableEditor::Delete()
{
}


//! [5]
