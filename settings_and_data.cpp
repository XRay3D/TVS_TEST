#include "settings_and_data.h"
#include "ui_settings_and_data.h"

SETTINGS_AND_DATA::SETTINGS_AND_DATA(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::SETTINGS_AND_DATA)
    , tableName("tvs")
    , sf(false)
{
    ui->setupUi(this);

    createConnection();

    model = new QSqlTableModel(this, db);
    model->setTable(tableName);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    //    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    //    model->setHeaderData(1, Qt::Horizontal, tr("First name"));
    //    model->setHeaderData(2, Qt::Horizontal, tr("Last name"));

    model->setHeaderData(0, Qt::Horizontal, tr("№"));
    model->setHeaderData(1, Qt::Horizontal, tr("	1	"));
    model->setHeaderData(2, Qt::Horizontal, tr("	2	"));
    model->setHeaderData(3, Qt::Horizontal, tr("	3	"));
    model->setHeaderData(4, Qt::Horizontal, tr("	4	"));
    model->setHeaderData(5, Qt::Horizontal, tr("	5	"));
    model->setHeaderData(6, Qt::Horizontal, tr("	6	"));
    model->setHeaderData(7, Qt::Horizontal, tr("	7	"));
    model->setHeaderData(8, Qt::Horizontal, tr("	8	"));
    model->setHeaderData(9, Qt::Horizontal, tr("	9	"));
    model->setHeaderData(10, Qt::Horizontal, tr("	10	"));
    model->setHeaderData(11, Qt::Horizontal, tr("	11	"));
    model->setHeaderData(12, Qt::Horizontal, tr("	12	"));
    model->setHeaderData(13, Qt::Horizontal, tr("	13	"));
    model->setHeaderData(14, Qt::Horizontal, tr("	14	"));
    model->setHeaderData(15, Qt::Horizontal, tr("	15	"));
    model->setHeaderData(16, Qt::Horizontal, tr("	16	"));
    model->setHeaderData(17, Qt::Horizontal, tr("	17	"));
    model->setHeaderData(18, Qt::Horizontal, tr("	18	"));

    ui->tableView->setVisible(ui->checkBox->isChecked());

    ui->tableView->setModel(model);

    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();

    for (int col = 4; col < 18; ++col) {
        ui->tableView->setColumnWidth(col, 50);
    }

    connect(ui->submitButton, &QPushButton::clicked, this, &SETTINGS_AND_DATA::submit);
    connect(ui->revertButton, &QPushButton::clicked, model, &QSqlTableModel::revertAll);
    connect(ui->quitButton, &QPushButton::clicked, this, &SETTINGS_AND_DATA::close);
}

SETTINGS_AND_DATA::~SETTINGS_AND_DATA()
{
    db.close();
    delete ui;
}

QStringList SETTINGS_AND_DATA::TVSList()
{
    QAbstractItemModel* am;
    QStringList list;

    QSqlQueryModel model;
    model.setQuery("SELECT * FROM " + tableName);

    for (int row = 0; row < this->model->rowCount(); ++row) {
        if (model.record(row).value("Enable").toInt() > 0) {
            list << model.record(row).value("DeviceType").toString();
        }
    }

    qDebug() << list;
    return list;
}

bool SETTINGS_AND_DATA::createConnection()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("tvs.db");

    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."),
            QMessageBox::Cancel);
        return false;
    }

    //    QSqlQuery query;
    //    query.exec("create table " + tableName + " (Number int primary key, DeviceType varchar(20), DeviceMarkingCodeUni varchar(20), DeviceMarkingCodeBi varchar(20), BreakdownVoltageVbrAtITMinVoltage float, BreakdownVoltageVbrAtITMaxVoltage float, TestCurrentItMiliAmpere float, StandOffVoltageVwmVoltage float, MaximumReverseLeakageAtVwmIdMicroAmpere float, MaximumPeakPulseSurgeCurrentIppmAmpere float, MaximumClampingVoltageAtIppmVcVoltage float, BowerVoltage int, ScaleCh1VoltageCurrent float, OffsetCh1VoltageCurrent float, ScaleCh2VoltageVoltage float, OffsetCh2Voltage float, TriggerLevelVoltageMul float, CapacitanceMul float, Enable bool)");
    //    TVS_DIODE tvs;
    //    tvs.Number = 20;
    //    tvs.DeviceType = "SMCJ24A";
    //    tvs.DeviceMarkingCodeUni = "GEZ";
    //    tvs.DeviceMarkingCodeBi = "BEZ";
    //    tvs.BreakdownVoltageVbrAtITMinVoltage = 26.7f;
    //    tvs.BreakdownVoltageVbrAtITMaxVoltage = 29.5f;
    //    tvs.TestCurrentItMiliAmpere = 1;
    //    tvs.StandOffVoltageVwmVoltage = 24;
    //    tvs.MaximumReverseLeakageAtVwmIdMicroAmpere = 1;
    //    tvs.MaximumPeakPulseSurgeCurrentIppmAmpere = 38.6f;
    //    tvs.MaximumClampingVoltageAtIppmVcVoltage = 38.9f;
    //    tvs.BowerVoltage = 200;
    //    tvs.ScaleCh1VoltageCurrent = 10;
    //    tvs.OffsetCh1VoltageCurrent = -30;
    //    tvs.ScaleCh2VoltageVoltage = 10;
    //    tvs.OffsetCh2Voltage = -30;
    //    tvs.TriggerLevelVoltageMul_10 = 10;
    //    tvs.CapacitanceMul_22Uf = 22;
    //    tvs.Enable = 1;
    //    return query.exec(QString("insert into " + tableName + " values(%1,'%2','%3','%4',%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16,%17,%18,%19)").arg(tvs.Number).arg(tvs.DeviceType).arg(tvs.DeviceMarkingCodeUni).arg(tvs.DeviceMarkingCodeBi).arg(tvs.BreakdownVoltageVbrAtITMinVoltage).arg(tvs.BreakdownVoltageVbrAtITMaxVoltage).arg(tvs.TestCurrentItMiliAmpere).arg(tvs.StandOffVoltageVwmVoltage).arg(tvs.MaximumReverseLeakageAtVwmIdMicroAmpere).arg(tvs.MaximumPeakPulseSurgeCurrentIppmAmpere).arg(tvs.MaximumClampingVoltageAtIppmVcVoltage).arg(tvs.BowerVoltage).arg(tvs.ScaleCh1VoltageCurrent).arg(tvs.OffsetCh1VoltageCurrent).arg(tvs.ScaleCh2VoltageVoltage).arg(tvs.OffsetCh2Voltage).arg(tvs.TriggerLevelVoltageMul_10).arg(tvs.CapacitanceMul_22Uf).arg(tvs.Enable));
    //    qDebug() << QString("insert into " + tableName + " values(%1,'%2','%3','%4',%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16,%17,%18,%19)").arg(tvs.Number).arg(tvs.DeviceType).arg(tvs.DeviceMarkingCodeUni).arg(tvs.DeviceMarkingCodeBi).arg(tvs.BreakdownVoltageVbrAtITMinVoltage).arg(tvs.BreakdownVoltageVbrAtITMaxVoltage).arg(tvs.TestCurrentItMiliAmpere).arg(tvs.StandOffVoltageVwmVoltage).arg(tvs.MaximumReverseLeakageAtVwmIdMicroAmpere).arg(tvs.MaximumPeakPulseSurgeCurrentIppmAmpere).arg(tvs.MaximumClampingVoltageAtIppmVcVoltage).arg(tvs.BowerVoltage).arg(tvs.ScaleCh1VoltageCurrent).arg(tvs.OffsetCh1VoltageCurrent).arg(tvs.ScaleCh2VoltageVoltage).arg(tvs.OffsetCh2Voltage).arg(tvs.TriggerLevelVoltageMul_10).arg(tvs.CapacitanceMul_22Uf).arg(tvs.Enable);
    return true;
}

void SETTINGS_AND_DATA::submit()
{

    if (QMessageBox::question(this, "Вопрос!", "Вы действительно хотите внести изменения?") == QMessageBox::Yes) {
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
}

void SETTINGS_AND_DATA::hideEvent(QHideEvent*)
{
    emit HideEvent();
}

void SETTINGS_AND_DATA::on_defaultButton_clicked()
{
    if (QMessageBox::question(this, "Вопрос!", "Вы действительно хотите установить всё по умолчанию!?") == QMessageBox::Yes) {
        QSqlQuery query;

        query.exec("DROP TABLE " + tableName);
        query.exec("CREATE TABLE " + tableName + " (Number int primary key, "
                                                 "DeviceType varchar(20), "
                                                 "DeviceMarkingCodeUni varchar(20), "
                                                 "DeviceMarkingCodeBi varchar(20), "
                                                 "BreakdownVoltageVbrAtITMinVoltage float, "
                                                 "BreakdownVoltageVbrAtITMaxVoltage float, "
                                                 "TestCurrentItMiliAmpere float, "
                                                 "StandOffVoltageVwmVoltage float, "
                                                 "MaximumReverseLeakageAtVwmIdMicroAmpere float, "
                                                 "MaximumPeakPulseSurgeCurrentIppmAmpere float, "
                                                 "MaximumClampingVoltageAtIppmVcVoltage float, "
                                                 "BowerVoltage float, ScaleCh1VoltageCurrent float, "
                                                 "OffsetCh1VoltageCurrent float, "
                                                 "ScaleCh2VoltageVoltage float, "
                                                 "OffsetCh2Voltage float, "
                                                 "TriggerLevelVoltageMul float, "
                                                 "CapacitanceMul float, "
                                                 "Enable bool)");
        QList<TVS_DIODE> list;
        list << TVS_DIODE(1, "SMCJ5.0A", "GDE", "GDE", 6.4f, 7.07f, 10.f, 5.f, 800.f, 163.f, 9.2f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(2, "SMCJ6.0A", "GDG", "GDG", 6.67f, 7.37f, 10.f, 6.f, 800.f, 145.6f, 10.3f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(3, "SMCJ6.5A", "GDK", "BDK", 7.22f, 7.98f, 10.f, 6.5f, 500.f, 133.9f, 11.2f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(4, "SMCJ7.0A", "GDM", "GDM", 7.78f, 8.6f, 10.f, 7.f, 200.f, 125.f, 12.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(5, "SMCJ7.5A", "GDP", "BDP", 8.33f, 9.21f, 1.f, 7.5f, 100.f, 116.3f, 12.9f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(6, "SMCJ8.0A", "GDR", "BDR", 8.89f, 9.83f, 1.f, 8.f, 50.f, 110.3f, 13.6f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(7, "SMCJ8.5A", "GDT", "BDT", 9.44f, 10.4f, 1.f, 8.5f, 20.f, 104.2f, 14.4f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(8, "SMCJ9.0A", "GDV", "BDV", 10.f, 11.1f, 1.f, 9.f, 10.f, 97.4f, 15.4f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(9, "SMCJ10A", "GDX", "BDX", 11.1f, 12.3f, 1.f, 10.f, 5.f, 88.2f, 17.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(10, "SMCJ11A", "GDZ", "GDZ", 12.2f, 13.5f, 1.f, 11.f, 5.f, 82.4f, 18.2f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(11, "SMCJ12A", "GEE", "BEE", 13.3f, 14.7f, 1.f, 12.f, 5.f, 75.4f, 19.9f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(12, "SMCJ13A", "GEG", "GEG", 14.4f, 15.9f, 1.f, 13.f, 1.f, 69.8f, 21.5f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(13, "SMCJ14A", "GEK", "BEK", 15.6f, 17.2f, 1.f, 14.f, 1.f, 64.7f, 23.2f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(14, "SMCJ15A", "GEM", "BEM", 16.7f, 18.5f, 1.f, 15.f, 1.f, 61.5f, 24.4f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(15, "SMCJ16A", "GEP", "GEM", 17.8f, 19.7f, 1.f, 16.f, 1.f, 57.7f, 26.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(16, "SMCJ17A", "GER", "GER", 18.9f, 20.9f, 1.f, 17.f, 1.f, 54.3f, 27.6f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(17, "SMCJ18A", "GET", "BET", 20.f, 22.1f, 1.f, 18.f, 1.f, 51.4f, 29.2f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(18, "SMCJ20A", "GEV", "BEV", 22.2f, 24.5f, 1.f, 20.f, 1.f, 46.3f, 32.4f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(19, "SMCJ22A", "GEX", "BEX", 24.4f, 26.9f, 1.f, 22.f, 1.f, 42.3f, 35.5f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(20, "SMCJ24A", "GEZ", "BEZ", 26.7f, 29.5f, 1.f, 24.f, 1.f, 38.6f, 38.9f, 200.f, 10.f, -30.f, 10.f, -30.f, 10.f, 22.f, 1)
             << TVS_DIODE(21, "SMCJ26A", "GFE", "BFE", 28.9f, 31.9f, 1.f, 26.f, 1.f, 35.6f, 42.1f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(22, "SMCJ28A", "GFG", "GFG", 31.1f, 34.4f, 1.f, 28.f, 1.f, 33.f, 45.4f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(23, "SMCJ30A", "GFK", "BFK", 33.3f, 36.8f, 1.f, 30.f, 1.f, 31.f, 48.4f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(24, "SMCJ33A", "GFM", "BFM", 36.7f, 40.6f, 1.f, 33.f, 1.f, 28.1f, 53.3f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(25, "SMCJ36A", "GFP", "BFP", 40.f, 44.2f, 1.f, 36.f, 1.f, 25.8f, 58.1f, 140.f, 10.f, -30.f, 10.f, -30.f, 10.f, 19.f, 1)
             << TVS_DIODE(26, "SMCJ40A", "GFR", "BFR", 44.4f, 49.1f, 1.f, 40.f, 1.f, 23.3f, 64.5f, 160.f, 10.f, -30.f, 10.f, -30.f, 10.f, 19.f, 1)
             << TVS_DIODE(27, "SMCJ43A", "GFT", "BFT", 47.8f, 52.8f, 1.f, 43.f, 1.f, 21.6f, 69.4f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(28, "SMCJ45A", "GFV", "GFV", 50.f, 55.3f, 1.f, 45.f, 1.f, 20.6f, 72.7f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(29, "SMCJ48A", "GFX", "GFX", 53.3f, 58.9f, 1.f, 48.f, 1.f, 19.4f, 77.4f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(30, "SMCJ51A", "GFZ", "GFZ", 56.7f, 62.7f, 1.f, 51.f, 1.f, 18.2f, 82.4f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(31, "SMCJ54A", "GGE", "GGE", 60.f, 66.3f, 1.f, 54.f, 1.f, 17.2f, 87.1f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(32, "SMCJ58A", "GGG", "GGG", 64.4f, 71.2f, 1.f, 58.f, 1.f, 16.f, 93.6f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(33, "SMCJ60A", "GGK", "GGK", 66.7f, 73.7f, 1.f, 60.f, 1.f, 15.5f, 96.8f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(34, "SMCJ64A", "GGM", "GGM", 71.1f, 78.6f, 1.f, 64.f, 1.f, 14.6f, 103.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(35, "SMCJ70A", "GGP", "GGP", 77.8f, 86.f, 1.f, 70.f, 1.f, 13.3f, 113.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(36, "SMCJ75A", "GGR", "GGR", 83.3f, 92.1f, 1.f, 75.f, 1.f, 12.4f, 121.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(37, "SMCJ78A", "GGT", "GGT", 86.7f, 95.8f, 1.f, 78.f, 1.f, 11.9f, 126.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(38, "SMCJ85A", "GGV", "GGV", 94.4f, 104.f, 1.f, 85.f, 1.f, 10.9f, 137.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(39, "SMCJ90A", "GGX", "GGX", 100.f, 111.f, 1.f, 90.f, 1.f, 10.3f, 146.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(40, "SMCJ100A", "GGZ", "GGZ", 111.f, 123.f, 1.f, 100.f, 1.f, 9.3f, 162.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(41, "SMCJ110A", "GHE", "GHE", 122.f, 135.f, 1.f, 110.f, 1.f, 8.5f, 177.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(42, "SMCJ120A", "GHG", "GHG", 133.f, 147.f, 1.f, 120.f, 1.f, 7.8f, 193.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(43, "SMCJ130A", "GHK", "GHK", 144.f, 159.f, 1.f, 130.f, 1.f, 7.2f, 209.f, 200.f, 2.f, -6.f, 50.f, -150.f, 8.f, 63.f, 1)
             << TVS_DIODE(44, "SMCJ150A", "GHM", "GHM", 167.f, 185.f, 1.f, 150.f, 1.f, 6.2f, 243.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(45, "SMCJ160A", "GHP", "GHP", 178.f, 197.f, 1.f, 160.f, 1.f, 5.8f, 259.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(46, "SMCJ170A", "GHR", "GHR", 189.f, 209.f, 1.f, 170.f, 1.f, 5.5f, 275.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(47, "SMBJ5.0A", "KE", "KE", 6.4f, 7.07f, 10.f, 5.f, 800.f, 65.2f, 9.2f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(48, "SMBJ6.0A", "KG", "KG", 6.67f, 7.37f, 10.f, 6.f, 800.f, 58.3f, 10.3f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(49, "SMBJ6.5A", "KK", "AK", 7.22f, 7.98f, 10.f, 6.5f, 500.f, 53.6f, 11.2f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(50, "SMBJ7.0A", "KM", "KM", 7.78f, 8.6f, 10.f, 7.f, 200.f, 50.f, 12.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(51, "SMBJ7.5A", "KP", "AP", 8.33f, 9.21f, 1.f, 7.5f, 100.f, 46.5f, 12.9f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(52, "SMBJ8.0A", "KR", "AR", 8.89f, 9.83f, 1.f, 8.f, 50.f, 44.1f, 13.6f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(53, "SMBJ8.5A", "KT", "AT", 9.44f, 10.4f, 1.f, 8.5f, 20.f, 41.7f, 14.4f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(54, "SMBJ9.0A", "KV", "AV", 10.f, 11.1f, 1.f, 9.f, 10.f, 39.f, 15.4f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(55, "SMBJ10A", "KX", "AX", 11.1f, 12.3f, 1.f, 10.f, 5.f, 35.3f, 17.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(56, "SMBJ11A", "KZ", "KZ", 12.2f, 13.5f, 1.f, 11.f, 5.f, 33.f, 18.2f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(57, "SMBJ12A", "LE", "BE", 13.3f, 14.7f, 1.f, 12.f, 5.f, 30.2f, 19.9f, 160.f, 10.f, -30.f, 5.f, -15.f, 20.f, 17.f, 1)
             << TVS_DIODE(58, "SMBJ13A", "LG", "LG", 14.4f, 15.9f, 1.f, 13.f, 1.f, 27.9f, 21.5f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(59, "SMBJ14A", "LK", "BK", 15.6f, 17.2f, 1.f, 14.f, 1.f, 25.9f, 23.2f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(60, "SMBJ15A", "LM", "BM", 16.7f, 18.5f, 1.f, 15.f, 1.f, 24.6f, 24.4f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(61, "SMBJ16A", "LP", "LM", 17.8f, 19.7f, 1.f, 16.f, 1.f, 23.1f, 26.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(62, "SMBJ17A", "LR", "LR", 18.9f, 20.9f, 1.f, 17.f, 1.f, 21.7f, 27.6f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(63, "SMBJ18A", "LT", "BT", 20.f, 22.1f, 1.f, 18.f, 1.f, 20.5f, 29.2f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(64, "SMBJ20A", "LV", "LV", 22.2f, 24.5f, 1.f, 20.f, 1.f, 18.5f, 32.4f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(65, "SMBJ22A", "LX", "BX", 24.4f, 26.9f, 1.f, 22.f, 1.f, 16.9f, 35.5f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(66, "SMBJ24A", "LZ", "BZ", 26.7f, 29.5f, 1.f, 24.f, 1.f, 15.4f, 38.9f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(67, "SMBJ26A", "ME", "CE", 28.9f, 31.9f, 1.f, 26.f, 1.f, 14.3f, 42.1f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(68, "SMBJ28A", "MG", "MG", 31.1f, 34.4f, 1.f, 28.f, 1.f, 13.2f, 45.4f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(69, "SMBJ30A", "MK", "CK", 33.3f, 36.8f, 1.f, 30.f, 1.f, 12.4f, 48.4f, 93.f, 5.f, -15.f, 10.f, -30.f, 5.f, 18.f, 1)
             << TVS_DIODE(70, "SMBJ33A", "MM", "CM", 36.7f, 40.6f, 1.f, 33.f, 1.f, 11.3f, 53.3f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(71, "SMBJ36A", "MP", "CP", 40.f, 44.2f, 1.f, 36.f, 1.f, 10.3f, 58.1f, 91.f, 5.f, -15.f, 10.f, -30.f, 5.f, 20.f, 1)
             << TVS_DIODE(72, "SMBJ40A", "MR", "CR", 44.4f, 49.1f, 1.f, 40.f, 1.f, 9.3f, 64.5f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(73, "SMBJ43A", "MT", "CT", 47.8f, 52.8f, 1.f, 43.f, 1.f, 8.6f, 69.4f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(74, "SMBJ45A", "MV", "MV", 50.f, 55.3f, 1.f, 45.f, 1.f, 8.3f, 72.7f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(75, "SMBJ48A", "MX", "MX", 53.3f, 58.9f, 1.f, 48.f, 1.f, 7.8f, 77.4f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(76, "SMBJ51A", "MZ", "MZ", 56.7f, 62.7f, 1.f, 51.f, 1.f, 7.3f, 82.4f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(77, "SMBJ54A", "NE", "NE", 60.f, 66.3f, 1.f, 54.f, 1.f, 6.9f, 87.1f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(78, "SMBJ58A", "NG", "NG", 64.4f, 71.2f, 1.f, 58.f, 1.f, 6.4f, 93.6f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(79, "SMBJ60A", "NK", "NK", 66.7f, 73.7f, 1.f, 60.f, 1.f, 6.2f, 96.8f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(80, "SMBJ64A", "NM", "NM", 71.1f, 78.6f, 1.f, 64.f, 1.f, 5.8f, 103.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(81, "SMBJ70A", "NP", "NP", 77.8f, 86.f, 1.f, 70.f, 1.f, 5.3f, 113.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(82, "SMBJ75A", "NR", "NR", 83.3f, 92.1f, 1.f, 75.f, 1.f, 5.f, 121.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(83, "SMBJ78A", "NT", "NT", 86.7f, 95.8f, 1.f, 78.f, 1.f, 4.8f, 126.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(84, "SMBJ85A", "NV", "NV", 94.4f, 104.f, 1.f, 85.f, 1.f, 4.4f, 137.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(85, "SMBJ90A", "NX", "NX", 100.f, 111.f, 1.f, 90.f, 1.f, 4.1f, 146.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(86, "SMBJ100A", "NZ", "NZ", 111.f, 123.f, 1.f, 100.f, 1.f, 3.7f, 162.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(87, "SMBJ110A", "PE", "PE", 122.f, 135.f, 1.f, 110.f, 1.f, 3.4f, 177.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(88, "SMBJ120A", "PG", "PG", 133.f, 147.f, 1.f, 120.f, 1.f, 3.1f, 193.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(89, "SMBJ130A", "PK", "PK", 144.f, 159.f, 1.f, 130.f, 1.f, 2.9f, 209.f, 180.f, 1.f, -3.f, 50.f, -150.f, 1.f, 46.f, 1)
             << TVS_DIODE(90, "SMBJ150A", "PM", "PM", 167.f, 185.f, 1.f, 150.f, 1.f, 2.5f, 243.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(91, "SMBJ160A", "PP", "PP", 178.f, 197.f, 1.f, 160.f, 1.f, 2.3f, 259.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(92, "SMBJ170A", "PR", "PR", 189.f, 209.f, 1.f, 170.f, 1.f, 2.2f, 275.f, 1.f, 1.f, -3.f, 1.f, -3.f, 1.f, 1.f, 0)
             << TVS_DIODE(93, "SMBJ188A", "PS", "PS", 209.f, 231.f, 1.f, 188.f, 1.f, 2.f, 328.f, 260.f, 1.f, -3.f, 50.f, -150.f, 1.f, 63.f, 1);

        foreach (TVS_DIODE tvs, list) {
            query.exec(QString("insert into " + tableName + " values(%1,'%2','%3','%4',%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,%16,%17,%18,%19)")
                           .arg(tvs.Number)
                           .arg(tvs.DeviceType)
                           .arg(tvs.DeviceMarkingCodeUni)
                           .arg(tvs.DeviceMarkingCodeBi)
                           .arg(tvs.BreakdownVoltageVbrAtITMinVoltage)
                           .arg(tvs.BreakdownVoltageVbrAtITMaxVoltage)
                           .arg(tvs.TestCurrentItMiliAmpere)
                           .arg(tvs.StandOffVoltageVwmVoltage)
                           .arg(tvs.MaximumReverseLeakageAtVwmIdMicroAmpere)
                           .arg(tvs.MaximumPeakPulseSurgeCurrentIppmAmpere)
                           .arg(tvs.MaximumClampingVoltageAtIppmVcVoltage)
                           .arg(tvs.BowerVoltage)
                           .arg(tvs.ScaleCh1VoltageCurrent)
                           .arg(tvs.OffsetCh1VoltageCurrent)
                           .arg(tvs.ScaleCh2VoltageVoltage)
                           .arg(tvs.OffsetCh2Voltage)
                           .arg(tvs.TriggerLevelVoltageMul_10)
                           .arg(tvs.CapacitanceMul_22Uf)
                           .arg(tvs.Enable));
        }
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
}

void SETTINGS_AND_DATA::on_checkBox_clicked(bool checked)
{
    ui->tableView->setVisible(checked);
}

void SETTINGS_AND_DATA::showEvent(QShowEvent*)
{
    sf = startTimer(100);
}

void SETTINGS_AND_DATA::paintEvent(QPaintEvent*)
{
}

void SETTINGS_AND_DATA::timerEvent(QTimerEvent* te)
{
    if (sf == te->timerId()) {
        killTimer(sf);
        sf = 0;
        int w;
        w = 0;
        for (int col = 0; col < 19; ++col) {
            w += ui->tableView->columnWidth(col);
        }
        if (ui->tableView->verticalScrollBar()->isVisible()) {
            w += ui->tableView->verticalScrollBar()->width();
        }
        w += ui->verticalLayout->contentsMargins().left();
        w += ui->verticalLayout->contentsMargins().right();
        w += ui->tableView->verticalHeader()->width() + 2;

        qDebug() << rect();
        qDebug() << pos();
        QRect r = geometry();
        r.setWidth(w);
        setGeometry(r);
    }
}
