#ifndef CHART_H
#define CHART_H

#include <QChartView>
#include <QObject>
#include <QWidget>

#include <QtCharts/QChartGlobal>

QT_BEGIN_NAMESPACE
class QComboBox;
class QCheckBox;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

QT_CHARTS_USE_NAMESPACE

class Chart : public QChartView {
    Q_OBJECT
public:
    explicit Chart(QWidget* parent = 0);
    void addData(QByteArray Current, QByteArray Voltage);

signals:

public slots:
private slots:

    void updateUI();

private:
    QChart* createLineChart() const;
    QChart* createSplineChart() const;
    DataTable generateRandomData(int listCount, int valueMax, int valueCount) const;
    int m_listCount;
    int m_valueMax;
    int m_valueCount;
    QList<QChartView*> m_charts;
    DataTable m_dataTable;
};

#endif // CHART_H
