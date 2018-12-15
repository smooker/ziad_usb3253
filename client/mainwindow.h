#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QCheckBox>
#include <QVariant>
#include <QDebug>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void cbClicked(bool enable_in);
private:
    QList<QCheckBox*> *list;
};

#endif // MAINWINDOW_H
