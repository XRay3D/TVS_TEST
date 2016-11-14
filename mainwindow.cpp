#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tester(new TVS_TESTER)
    , osc(new RIGOL_DS1102E)
    , sai(this)
    , clipboard(QApplication::clipboard())
    , measCount(0)
{
    ui->setupUi(this);
    ui->lblOsc->setText(osc->connected);

    //    double Voltage, Current;
    //    osc->GetTestResult(Voltage, Current);
    //    qDebug() << Voltage << Current;

    //    ui->horizontalSlider->installEventFilter(this);
    //    this->installEventFilter(this);

    //    tester->moveToThread(&workerThread);
    //    connect(&workerThread, &QThread::finished, tester, &QObject::deleteLater);
    //    connect(ui->pushButton_Ping, &QPushButton::clicked, tester, &TVS_TESTER::FindStend);
    //    connect(ui->pushButton_test, &QPushButton::clicked, tester, &TVS_TESTER::Test);
    //    connect(tester, &TVS_TESTER::MeasureReady, ui->lineEdit, &QLineEdit::setText);
    //    connect(this, &MainWindow::SetCap, tester, &TVS_TESTER::SetCap);
    //    connect(this, &MainWindow::Test, tester, &TVS_TESTER::Test);
    //    workerThread.start();

    //    connect(&sai, &SETTINGS_AND_DATA::HideEvent, this, &QMainWindow::close);

    //    ui->comboBox->addItems(sai.TVSList());
    connect(osc, &RIGOL_DS1102E::addData, ui->graphicsView, &Chart::addData);
    osc->CommandButton1_Click();
}

MainWindow::~MainWindow()
{
    //    workerThread.quit();
    //    workerThread.wait();
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    sai.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->textEdit->append(QString("%1\t%2").arg(++measCount).arg(ui->lineEdit->text()));
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == ui->horizontalSlider) {
        if (event->type() == QEvent::MouseButtonRelease) {
            emit SetCap(ui->horizontalSlider->value());
            ui->capLabel->setText(QString("%1 uF").arg(ui->horizontalSlider->value() * 22));
            return false;
        }
    }
    if (obj == this) {
        if (event->type() == QEvent::KeyRelease) {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            qDebug() << "Ate key press" << keyEvent->text();
            switch (*keyEvent->text().toLocal8Bit().data()) {
            case 'T':
            case 't':
            case 'Е':
            case 'е':
                emit Test();
                return false;
                break;
            case 'A':
            case 'a':
            case 'Ф':
            case 'ф':
                on_pushButton_2_clicked();
                return false;
                break;
            case 'C':
            case 'c':
            case 'С':
            case 'с':
                on_pushButton_3_clicked();
                return false;
                break;
            default:
                break;
            }
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::on_pushButton_3_clicked()
{
    clipboard->setText(ui->textEdit->toPlainText());
    ui->textEdit->clear();
    measCount = 0;
}
