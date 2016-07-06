#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QtEvents>
#include <QClipboard>

#include "tvs_tester.h"
#include "settings_and_data.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

signals:
    void SetCap(int i);
    void Test();

private:
    Ui::MainWindow* ui;

    QThread workerThread;

    TVS_TESTER* tester;

    SETTINGS_AND_DATA sai;

    QClipboard* clipboard;

    int measCount;
    // QObject interface
public:
    bool eventFilter(QObject* obj, QEvent* event);
};

#endif // MAINWINDOW_H
