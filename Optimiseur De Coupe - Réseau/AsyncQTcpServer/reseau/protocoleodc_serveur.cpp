/*
 * \file ProtocoleODC_serveur.cpp
 * \brief class ProtocoleODC_serveur Protocole de communication entre les clients et le serveur de l'Optimiseur de Coupe
 * \author Rebecca Charbit
 * \date 2015
 */

#include "protocoleodc_serveur.h"

ProtocoleODC_serveur::ProtocoleODC_serveur(QString message) {
    QStringList messageList = message.split("!");
    if(messageList.size() == 5) {
        int testA = QString::compare(messageList[0], "ODC-START");
        int testB = QString::compare(messageList[4], "ODC-END\n");
        if(testA == 0 && testB == 0) {
            // Le message commence bien par ODC-START et ODC-END et contient bien 5 éléments
            // On peut le traiter

            // les barres
            QStringList barresListe = messageList[1].split("|" , QString::SkipEmptyParts);
            int i,j;
            for(i=0; i<barresListe.length() ; i++) {
                QStringList infoBarre = barresListe[i].split(";");
                double laBarre = infoBarre[0].toDouble();
                int nbBarre = infoBarre[1].toInt();
                for(j=0 ; j<nbBarre ; j++){
                    m_barresVecteur.append(laBarre);
                }
            }

            // les tronçons désirés
            QStringList tronconsListe = messageList[2].split("|", QString::SkipEmptyParts);
            for(i=0; i<tronconsListe.length() ; i++) {
                QStringList infoTroncon = tronconsListe[i].split(";");
                double leTroncon = infoTroncon[0].toDouble();
                int nbTroncon = infoTroncon[1].toInt();
                for(j=0 ; j<nbTroncon ; j++){
                    m_tronconsVecteur.append(leTroncon);
                }
            }

            // Epaisseur de la lame
            m_epaisseurLame = messageList[3].toDouble();
            m_etat = 1;
        }

        else {
            qDebug() << "Le message ne commence pas par ODC-START ou ODC-END\\n : [" << messageList.join("][") << "]";
            m_etat = 0;
        }
    }
    else {
        qDebug() << "Le message ne contient pas 5 éléments : [" << messageList.join("][") << "]";
        m_etat = 0;
    }
}



QString ProtocoleODC_serveur::sendCalculsTropGrands()
{
    return "ODC-START!STOP-CALCULS!ODC-END\n";
}


QString ProtocoleODC_serveur::createMessage(std::list<Combinaison> *pointResultatFinal, double rendementTotal, List *barres, List *troncons)
{
    // début du message
    QString text("ODC-START!");

    // les combinaisons
    for(std::list<Combinaison>::iterator it=pointResultatFinal->begin();
            it != pointResultatFinal->end();
            ++it) {
        text += it->toStr() + "|";
    }
    text.remove(text.length()-1, 1);    // retire dernier |

    // rendement total
    text += "!";
    if(QString::compare(QString::number(rendementTotal), "nan") != 0)  // évine 'nan' de QString::number
        text += QString::number(rendementTotal);
    text += "!";

    // barres restantes
    text += barres->toStr(true);
    text += "!";

    // tronçons restants
    text += troncons->toStr(true);
    text += "!";

    // fin du message
    text += "ODC-END\n";

    return text;
}

QVector<double> ProtocoleODC_serveur::getBarresVecteur() const
{
    return m_barresVecteur;
}

QVector<double> ProtocoleODC_serveur::getTronconsVecteur() const
{
    return m_tronconsVecteur;
}

double ProtocoleODC_serveur::getEpaisseurLame() const
{
    return m_epaisseurLame;
}

int ProtocoleODC_serveur::getEtat() const
{
    return m_etat;
}
