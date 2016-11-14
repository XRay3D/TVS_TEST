#include "chart.h"

#include <QChartView>
#include <QDebug>
#include <QLayout>
#include <QLineSeries>
#include <QSplineSeries>
#include <QTime>
#include <QValueAxis>

Chart::Chart(QWidget* parent)
    : QChartView(parent)
    , m_listCount(3)
    , m_valueMax(10)
    , m_valueCount(7)
    , m_dataTable(generateRandomData(m_listCount, m_valueMax, m_valueCount))

{
    setChart(createLineChart());
    //    QVBoxLayout* Layout = new QVBoxLayout(this);
    //    Layout->setMargin(0);
    //    Layout->setSpacing(0);
    //    QChartView* chartView = new QChartView(createLineChart());
    //    Layout->addWidget(chartView);
    m_charts << this;
    //    setLayout(Layout);
    updateUI();
}

void Chart::addData(QByteArray Current, QByteArray Voltage)
{
    chart()->removeAllSeries();
    //    chart()->removeAxis(chart()->axisX());
    //    chart()->removeAxis(chart()->axisY());

    double i(0);
    QLineSeries* series;

    series = new QSplineSeries(chart());
    foreach (char data, Current) {
        series->append(i++, *(uchar*)&data - 127);
        qDebug() << *(uchar*)&data;
    }
    series->setName("Current");
    chart()->addSeries(series);

    //    QValueAxis* axisX = new QValueAxis;
    //    axisX->setRange(1, series->count());
    //    axisX->setTickCount(series->count() / 100);
    //    //    axisX->setLabelFormat("%.2f");
    //    chart()->setAxisX(axisX, series);

    i = 0;
    series = new QSplineSeries(chart());
    foreach (char data, Voltage) {
        series->append(i++, 127 - *(uchar*)&data);
    }
    series->setName("Voltage");
    chart()->addSeries(series);
    //    chart()->setAxisX(axisX, series);

    QValueAxis* axisY = new QValueAxis;
    axisY->setRange(-128, 128);
    axisY->setTickCount(16);
    axisY->setObjectName("asda");
    //    axisY->setLabelFormat("%.2f");
    chart()->setAxisY(axisY, series);
}

void Chart::updateUI()
{
    QChart::ChartTheme theme = QChart::ChartThemeLight;

    if (m_charts.at(0)->chart()->theme() != theme) {
        foreach (QChartView* chartView, m_charts)
            chartView->chart()->setTheme(theme);

        QPalette pal = window()->palette();
        if (theme == QChart::ChartThemeLight) {
            pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        }
        else if (theme == QChart::ChartThemeDark) {
            pal.setColor(QPalette::Window, QRgb(0x121218));
            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        }
        else if (theme == QChart::ChartThemeBlueCerulean) {
            pal.setColor(QPalette::Window, QRgb(0x40434a));
            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        }
        else if (theme == QChart::ChartThemeBrownSand) {
            pal.setColor(QPalette::Window, QRgb(0x9e8965));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        }
        else if (theme == QChart::ChartThemeBlueNcs) {
            pal.setColor(QPalette::Window, QRgb(0x018bba));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        }
        else if (theme == QChart::ChartThemeHighContrast) {
            pal.setColor(QPalette::Window, QRgb(0xffab03));
            pal.setColor(QPalette::WindowText, QRgb(0x181818));
        }
        else if (theme == QChart::ChartThemeBlueIcy) {
            pal.setColor(QPalette::Window, QRgb(0xcee7f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        }
        else {
            pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        }
        window()->setPalette(pal);
    }

    foreach (QChartView* chart, m_charts)
        chart->setRenderHint(QPainter::Antialiasing, true);

    QChart::AnimationOptions options(QChart::AllAnimations);
    if (m_charts.at(0)->chart()->animationOptions() != options) {
        foreach (QChartView* chartView, m_charts)
            chartView->chart()->setAnimationOptions(options);
    }

    Qt::Alignment alignment(Qt::AlignRight);

    if (!alignment) {
        foreach (QChartView* chartView, m_charts)
            chartView->chart()->legend()->hide();
    }
    else {
        foreach (QChartView* chartView, m_charts) {
            chartView->chart()->legend()->setAlignment(alignment);
            chartView->chart()->legend()->show();
        }
    }
}

QChart* Chart::createLineChart() const
{
    QChart* chart = new QChart();
    chart->setTitle("Line chart");

    QString name("Series ");
    int nameIndex = 0;
    foreach (DataList list, m_dataTable) {
        QLineSeries* series = new QLineSeries(chart);
        foreach (Data data, list)
            series->append(data.first);
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }
    chart->createDefaultAxes();

    return chart;
}

QChart* Chart::createSplineChart() const
{
    // spine chart
    QChart* chart = new QChart();
    chart->setTitle("Spline chart");
    QString name("Series ");
    int nameIndex = 0;
    foreach (DataList list, m_dataTable) {
        QSplineSeries* series = new QSplineSeries(chart);
        foreach (Data data, list)
            series->append(data.first);
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }
    chart->createDefaultAxes();
    return chart;
}

DataTable Chart::generateRandomData(int listCount, int valueMax, int valueCount) const
{
    DataTable dataTable;

    // set seed for random stuff
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    // generate random data
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        qreal yValue(0);
        for (int j(0); j < valueCount; j++) {
            yValue = yValue + (qreal)(qrand() % valueMax) / (qreal)valueCount;
            QPointF value((j + (qreal)rand() / (qreal)RAND_MAX) * ((qreal)m_valueMax / (qreal)valueCount),
                yValue);
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        dataTable << dataList;
    }

    return dataTable;
}
