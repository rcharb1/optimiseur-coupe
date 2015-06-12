#ifndef BARREGRAPHIQUE_H
#define BARREGRAPHIQUE_H

#include <QWidget>
#include <QPainter>
#include <list>
#include <QString>
#include <QVector>
#include <QMessageBox>
#include "../convertunit.h"
#include "../moteur/Paire.h"
#include "../moteur/Combinaison.h"

class BarreGraphique : public QWidget
{
    Q_OBJECT
public:
    explicit BarreGraphique(Combinaison * combinaison ,QWidget *parent = 0);

private:
    Combinaison * m_combinaison;
    std::list<Paire> m_liste;
    double m_barre;
signals:

public slots:

protected:
    void paintEvent(QPaintEvent * e);
};

#endif // BARREGRAPHIQUE_H