#ifndef GROUPESAISIE_H
#define GROUPESAISIE_H

#include <QWidget>
#include <QLabel>
#include <QVector>
#include <QScrollArea>
#include <QScrollBar>
#include <QPushButton>
#include <QFont>
#include <QLayout>
#include <QString>
#include "saisie.h"

class GroupeSaisie : public QWidget
{
    Q_OBJECT
public:
    explicit GroupeSaisie(QString titre, QFont & fontTitre, QWidget *parent = 0);
    ~GroupeSaisie();
    QVector<Saisie *> saisies() const;
private:
    QVBoxLayout * m_layoutSaisies;
    QVector<Saisie *> m_vectorSaisies;
    QLabel * m_labelNbSaisies;
    QPushButton * m_buttonSupprSaisies;
    QString m_stringNbSaisies;
    QScrollArea * m_scrollSaisies;
signals:

public slots:
    void ajoutSaisie();
    void supprSaisie();
};

#endif // GROUPESAISIE_H
