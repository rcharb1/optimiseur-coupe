#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QApplication>
#include <QWidget>
#include <QLayout>
#include <QFont>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QFrame>
#include <QFileDialog>
#include <QTextEdit>
#include "groupesaisie.h"

class FenetrePrincipale : public QWidget
{
    Q_OBJECT
public:
    explicit FenetrePrincipale(QWidget *parent = 0);
    ~FenetrePrincipale();

private:

signals:

public slots:

};

#endif // FENETREPRINCIPALE_H
