/*
 * \file combinaison.cpp
 * \brief class Combinaison contient toutes les informations concernant une combinaison
 * \author Pierre-Emmanuel PIRNAY 11296315
 * \date 2015
 */

#include "combinaison.h"

Combinaison::Combinaison(double barre, QVector<double> troncons, double rendement) : m_barre(barre), m_troncons(troncons), m_rendement(rendement)
{

}

double Combinaison::barre() const
{
    return m_barre;
}

QVector<double> Combinaison::troncons() const
{
    return m_troncons;
}

double Combinaison::rendement() const
{
    return m_rendement;
}

QString Combinaison::toStr() const
{
    QString text = QObject::tr("<li>Sur une barre de ");
    text += ConvertUnit::toStrSimplifie(m_barre) + " :<br>";
    int i;
    for(i = 0; i < m_troncons.length(); text+=", ") {
        text += ConvertUnit::toStrSimplifie(m_troncons[i]);
        i++;
    }
    text += "<br>" + QObject::tr("Le rendement est de ");
    text += QString::number(m_rendement, 'g', 4) + "\%.<br></li>";
    return text;
}
