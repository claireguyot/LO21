#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include <QObject>
#include <QWidget>
//#include <QRadioButton>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
//#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>
#include <QString>

class sauvegarde : public QWidget
{
    QHBoxLayout* layout;
    QPushButton* bJson;
    QPushButton* bXml;
    QPushButton* bAnnuler;
    //QLineEdit* nomDoc;

public:
    explicit sauvegarde(QWidget* parent = nullptr);

};

#endif // SAUVEGARDE_H
