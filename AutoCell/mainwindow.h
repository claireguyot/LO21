#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "fenetre1d.h"
#include <QWidget>
#include <QStackedWidget>
#include <QComboBox>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // MAINWINDOW_H
