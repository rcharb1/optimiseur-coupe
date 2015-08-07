/*
 * \file ProtocoleODC_serveur.cpp
 * \brief class ProtocoleODC_serveur Protocole de communication entre les clients et le serveur de l'Optimiseur de Coupe
 * \author Rebecca Charbit 13409175
 * \date 2015
 */

#include "protocoleodc_serveur.h"

ProtocoleODC_serveur::ProtocoleODC_serveur(QString message)
{
        QStringList messageList = message.split("!");
        if(messageList.size() == 5) {
            int testA = QString::compare(messageList[0], "ODC-START");
            int testB = QString::compare(messageList[4], "ODC-END\n");
            if(testA == 0 && testB == 0) {
                // Le message commence bien par ODC-START et ODC-END et contient bien 4 éléments
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

            }
            else
                qDebug() << "Le message ne commence pas par ODC-START ou ODC-END\\n : [" << messageList.join("][") << "]";
        }
        else
            qDebug() << "Le message ne contient pas 6 éléments : [" << messageList.join("][") << "]";
    }
}


QString ProtocoleODC_serveur::createMessage ()
{
    // ODC-START indique le début du message
    QString message("ODC-START!");
    int i;
    list <Combinaison> combi = m_results->getResultatFinal();		// les combinaisons retenues
	list <Combinaison>::iterator itComb;
	list <Paire>::iterator itTron
	List * itList;
    // Ajout des combinaisons
        for (itComb = combi.begin(); itComb != combi.end(); itComb++) {

        message += QString::number(itComb->getBarre()));
        message += "/";
        
        for (itTron = combi->getPaires().begin() ; itTron != combi->getPaires().end () ; itTron++) {
        	message += QString::number (itTron->m_longueur);
        	message += ";";
        }
        message += "/";
        message += QString::number (combi->getRendement());
        message += "|";					// entre deux combinaisons
    }
    message += "!";						// entre combinaisons et rendement total

    // Ajout du rendement total
    message += QString::number(m_results->getRendement());
	message += "!";
	
	// Ajout du reste des barres
	itList = m_result->getBarres(); // itérateur
    while (itList)
    {
        message += QString::number (itList->getPremier());
        message += ";";
        itList = itList->getProchain ();
    }
    message += "!"
    
    // Ajout du reste des troncons
	itList = m_result->getTroncons(); // itérateur
    while (itList)
    {
        message += QString::number (itList->getPremier());
        message += ";";
        itList = itList->getProchain ();
    }

    // ODC-END indique la fin du message
    message +="!ODC-END\n";

    return message;
}
