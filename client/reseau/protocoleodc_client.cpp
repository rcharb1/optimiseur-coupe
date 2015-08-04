/*
 * \file ProtocoleODC_client.cpp
 * \brief class ProtocoleODC_client Protocole de communication entre les clients et le serveur de l'Optimiseur de Coupe
 * \author Pierre-Emmanuel PIRNAY 11296315
 * \date 2015
 */

#include "protocoleodc_client.h"

ProtocoleODC_client::ProtocoleODC_client(QString message) : m_etat(0)
{
    if(QString::compare(message, "ODC-START!STOP-CALCULS!ODC-END\n") == 0) {
        m_etat = 1;
    }
    else {
        QStringList messageList = message.split("!");
        if(messageList.size() == 6) {
            int testA = QString::compare(messageList[0], "ODC-START");
            int testB = QString::compare(messageList[5], "ODC-END\n");
            if(testA == 0 && testB == 0) {
                // Le message commence bien par ODC-START et ODC-END et contient bien 5 éléments
                // On peut le traiter
                QStringList combinaisonsList = messageList[1].split("|", QString::SkipEmptyParts);

                // Vérifie qu'il y ait au moins 1 tronçon
                if(QString::compare(combinaisonsList[0], messageList[1]) != 0 ||
                        QString::compare(messageList[1], "") != 0 ) {

                    // Il y a des combinaisons disponibles
                    int i,j;
                    QStringList combinaisonList, tronconsList;

                    for(i = 0; i < combinaisonsList.size(); i++) {
                        combinaisonList = combinaisonsList[i].split("/", QString::SkipEmptyParts);

                        // Vérifie que la combinaison est bien composée de 3 éléments
                        if(combinaisonList.size() == 3) {
                            tronconsList = combinaisonList[1].split(";", QString::SkipEmptyParts);

                            // Vérifie qu'il y a au moins un tronçon
                            if(tronconsList.size() > 0) {
                                QVector<double> tronconsVecteur;

                                for(j = 0; j < tronconsList.size() ; j++) {
                                    tronconsVecteur.append(tronconsList[j].toDouble());
                                }

                                Combinaison * combinaison = new Combinaison(combinaisonList[0].toDouble(), tronconsVecteur, combinaisonList[2].toDouble() );

                                m_listResultats.append(combinaison);
                            }
                            else
                                qDebug() << "Il n'y a pas de tronçons dans la combinaison : " << combinaisonsList[i];
                        }
                        else
                            qDebug() << "La combinaison n'est pas composée de 3 éléments : " << combinaisonsList[i];
                    }
                }

                // Enregistrement du rendement
                m_rendementTotal = messageList[2].toDouble();

                // Enregistrement des barres restantes
                if(QString::compare(messageList[3], "") != 0) {
                    QStringList barresRestList = messageList[3].split(";");
                    int i;
                    for(i = 0; i < barresRestList.size() ; i++)
                        m_barresRestantes.append(barresRestList[i].toDouble());
                }

                // Enregistrement des tronçons restants
                if(QString::compare(messageList[4], "") != 0) {
                    QStringList tronRestList = messageList[4].split(";");
                    int i;
                    for(i = 0; i < tronRestList.size() ; i++)
                        m_troncRestants.append(tronRestList[i].toDouble());
                }

                m_etat = 2;
            }
            else
                qDebug() << "Le message ne commence pas par ODC-START ou ODC-END\\n : [" << messageList.join("][") << "]";
        }
        else
            qDebug() << "Le message ne contient pas 6 éléments : [" << messageList.join("][") << "]";
    }
}


QString ProtocoleODC_client::createMessage(QVector<Saisie *> resultatsBarres, QVector<Saisie *> resultatsTron, double epaisseurLame)
{
    // ODC-START indique le début du message
    QString message("ODC-START!");
    int i;

    // Ajout des barres avant la découpe
    for(i=0; i< resultatsBarres.length() ; message += "|") {

        QString saisie(QString::number(ConvertUnit::toMm(resultatsBarres[i]->longueur(), resultatsBarres[i]->unite())));
        saisie += ";";
        saisie += QString::number(resultatsBarres[i]->quantite());
        i++;
        message += saisie;
    }
    message += "!";

    // Ajout des tronçons désirés
    for(i=0; i< resultatsTron.length() ; message += "|") {
        QString saisie(QString::number(ConvertUnit::toMm(resultatsTron[i]->longueur(), resultatsTron[i]->unite())));
        saisie += ";";
        saisie += QString::number(resultatsTron[i]->quantite());
        i++;
        message += saisie;
    }
    message += "!";

    // Ajout de l'épaisseur de la lame
    message += QString::number(epaisseurLame);

    // ODC-END indique la fin du message
    message +="!ODC-END\n";

    return message;
}

QVector<Combinaison *> ProtocoleODC_client::resultats() const
{
    return m_listResultats;
}

double ProtocoleODC_client::rendementTotal() const
{
    return m_rendementTotal;
}

QVector<double> ProtocoleODC_client::tronconsRestants() const
{
    return m_troncRestants;
}

QVector<double> ProtocoleODC_client::barresRestantes() const
{
    return m_barresRestantes;
}

int ProtocoleODC_client::etat() const
{
    return m_etat;
}
