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

