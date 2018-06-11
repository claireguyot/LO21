#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "fenetre1d.h"
#include "fenetre2d.h"
#include <QWidget>
#include <QStackedWidget>
#include <QComboBox>
#include <QSettings>

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    QComboBox *choixDimension;
    fenetre1D* dim1;
    fenetre2D* dim2;
    QStackedWidget *switchDim;
    void loadContexte();
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:
    void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
