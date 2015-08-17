// mytask.cpp

#include "mytask.h"
#include <QDebug>


MyTask::MyTask(QString messageClient) : m_messageClient(messageClient) {

}


void MyTask::run() {
    qDebug() << "Task : run...";
    // time consumer
    ProtocoleODC_serveur * protODC = new ProtocoleODC_serveur(m_messageClient);
    // vérification en cas d'erreur...
    if(protODC->getEtat() == 0)
        return;

    // lancement du moteur
    List * tronconsList = new List();
    List * barresList =  new List();
    createSortedList(tronconsList, protODC->getTronconsVecteur());
    createSortedList(barresList, protODC->getBarresVecteur());
    MoteurCalculs * moteur = new MoteurCalculs(tronconsList, barresList, protODC->getEpaisseurLame());

    QString resultat = ProtocoleODC_serveur::createMessage(moteur->getPointResultatFinal(),
                                        moteur->calculeRendementFinal(),
                                        moteur->getBarres(),
                                        moteur->getTroncons() );
    qDebug() << "Task : résultat généré : " << resultat;
    delete tronconsList;
    delete barresList;
    delete moteur;
    emit Result(resultat);
}
