/*
 * \file combinaison.h
 * \brief class Combinaison contient toutes les informations concernant une combinaison
 * \author Pierre-Emmanuel PIRNAY 11296315
 * \date 2015
 */

#ifndef COMBINAISON_H
#define COMBINAISON_H

#include <QVector>


/*
 * \class ProtocoleODC_client ProtocoleODC_client.h
 *
 * Classe permettant d'enregistrer toutes les informations nécesaires concernant une combinaison :
 * - la barre concernée en mm,
 * - les tronçons en mm
 * - le rendement
 */

class Combinaison
{
public:
    /*
     * \brief Constructeur
     * \param barre longueur de la barre concernée en mm
     * \param troncons Vecteur des tronçons à découper
     * \param rendement Le rendement de la coupe effectuée sur cette barre
     */
    Combinaison(double barre, QVector<double> troncons, double rendement);

    /*
     * \brief Méthode d'accès à la barre
     * \return la barre en mm
     */
    double barre() const;

    /*
     * \brief Méthode d'accès aux tronçons à découper
     * \return Un vecteur contenant les tronçons
     */
    QVector<double> troncons() const;

    /*
     * \brief Méthode d'accès au rendement
     * \return Le rendement
     */
    double rendement() const;
private:
    double m_barre;
    QVector<double> m_troncons;
    double m_rendement;
};

#endif // COMBINAISON_H
