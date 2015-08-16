/*
 * \file fenetreprincipale.cpp
 * \brief Source de la classe FenetrePrincipale
 * \author Pierre-Emmanuel PIRNAY 11296315
 * \date 2015
 */

#include "fenetreprincipale.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) : QWidget(parent)
{
    m_client = new Client;
    QObject::connect(m_client, SIGNAL(bienConnecte()), this, SLOT(bienConnecte()));
    setDisabled(true);

    // Titre de la fenêtre
    setWindowTitle(tr("Optimiseur de coupe"));
    setWindowIcon(QIcon("mainIcon.ico"));

    // Police titre
    QFont fontTitre;
    fontTitre.setPointSize(12);
    fontTitre.setBold(true);
    fontTitre.setStyleHint(QFont::SansSerif);

    // Formulaire
    m_tabs = new QTabWidget(this);
    m_formulaireSaisie = new FormulaireSaisie(fontTitre);
    m_tabs->addTab(m_formulaireSaisie, tr("Formulaire de saisie"));

    // Résultats
    m_widgetResultats = new WidgetResultats(fontTitre);
    m_tabs->addTab(m_widgetResultats, tr("Résultats"));

    // Graphique
    m_widgetGraphique = new WidgetGraphique(fontTitre);
    m_tabs->addTab(m_widgetGraphique, tr("Graphique des résultats"));

    // Infos
    OngletInfo * infos = new OngletInfo;
    m_tabs->addTab(infos, tr("A propos"));
    //Layout
    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_tabs);
    setLayout(mainLayout);

    // Connexions
    QObject::connect(m_formulaireSaisie->buttonAppliquer(), SIGNAL(clicked()),
                     this, SLOT(traiterFormulaire()) );
}

QString FenetrePrincipale::listToStr(QVector<double> liste)
{
    int i;
    QString text("");
    for(i=0; i< liste.length(); text+=", ") {
        text += ConvertUnit::toStrSimplifie(liste[i]);
        i++;
    }
    text += "<br>";
    return text;
}

void FenetrePrincipale::traiterFormulaire(){

    //Déclarations diverses
    QVector <Saisie *> resultatsBarres = m_formulaireSaisie->groupeSaisieBarres()->saisies();
    QVector <Saisie *> resultatsTron = m_formulaireSaisie->groupeSaisieTron()->saisies();
    int i,j, erreur=0;

    // Détection de l'erreur : total longueur des barres av découpe < total longueur tronçons demandés
    double totalBarre = 0, totalTron = 0;
    for(i = 0; i != resultatsBarres.size();i++){
        for(j=0; j!= resultatsBarres[i]->quantite();j++)
            totalBarre += resultatsBarres[i]->longueur();
    }
    for(i = 0; i != resultatsTron.size();i++){
        for(j=0; j!= resultatsTron[i]->quantite();j++)
            totalTron += resultatsTron[i]->longueur();
    }
    if(totalBarre < totalTron){
        QMessageBox::warning(this, tr("Erreur"),
                             tr("La longueur totale des barres avant la découpe "
                             "est plus petite que la longueur totale des tronçons demandés."));
        erreur++;
    }

    // Détection de l'erreur : épaisseur de la lame > + petite longueur
    double temp = resultatsBarres.at(0)->longueur();
    for(i=1;i!=resultatsBarres.size();i++){
        if(resultatsBarres.at(i)->longueur() < temp)
            temp = resultatsBarres.at(i)->longueur();
    }
    if(m_formulaireSaisie->epaisseurLame() > temp){
        QMessageBox::warning(this,tr("Erreur"),
                             tr("L'épaisseur de la lame est plus grande que la plus "
                             "petite longueur des barres avant la découpe."));
        erreur++;
    }

    // Pas d'erreur détectée : lancement du moteur
    if(erreur==0){
        m_formulaireSaisie->setDisabled(true);

        // Envoi du message au serveur
        QString text("");
        QString message = ProtocoleODC_client::createMessage(resultatsBarres,
                                                             resultatsTron,
                                                             m_formulaireSaisie->epaisseurLame() );
        int result_client = m_client->sendMessage(message);

        if(result_client == -1) {
            QMessageBox::warning(this, tr("Erreur"), tr("Une erreur est apparue lors de l'envoie du message au serveur.\n"
                                                               "Veuillez vérifier la connexion et redémarrer le programme."),
                                 QMessageBox::Ok);
            m_formulaireSaisie->setDisabled(false);
            return;
        }
        else if(result_client == -2) {
            QMessageBox::warning(this, tr("Erreur"), tr("Une erreur est apparue lors de la réception du résultat.\n"
                                                               "Veuillez vérifier la connexion et redémarrer le programme.s"),
                                 QMessageBox::Ok);
            m_formulaireSaisie->setDisabled(false);
            return;
        }
        else {
            while(QString::compare(m_client->message(), "") == 0) ;
            ProtocoleODC_client * protODC = new ProtocoleODC_client(m_client->message());
            m_formulaireSaisie->setDisabled(false);
            if(protODC->etat() == 1){
                QMessageBox::warning(this, tr("Calculs arrétés"), tr("Les calculs demandés sont trop grands."
                                                                     "Aucun résultat ne sera affiché."));
                return;
            }
            else if(protODC->etat() != 2) {
                QMessageBox erreurMsgB;
                erreurMsgB.setText(tr("Une erreur s'est produite lors du traitement de la réponse du serveur."
                                      "Aucun résultat ne sera affiché."));
                erreurMsgB.setWindowTitle(tr("Erreur - Traitement de la réponse du serveur"));
                erreurMsgB.setStandardButtons(QMessageBox::Ok);
                erreurMsgB.setDetailedText(
                            tr("Message envoyé : ") + message +
                            "\n"+ tr("Message reçu : ") +
                            m_client->message() + "\n" + protODC->erreur());
                erreurMsgB.setIcon(QMessageBox::Critical);
                erreurMsgB.exec();
                return;
            }
            else {

                if(not protODC->tronconsRestants().empty()){
                    erreur=10;
                    text = tr("Vous n'avez pas assez de matière première pour "
                                      "couper tous les tronçons désirés.<br>Liste des troncons restants:<br>");
                    text += listToStr(protODC->tronconsRestants());
                    QMessageBox::warning(this, tr("Erreur"), text);
                }

                text="";

                if(not protODC->tronconsRestants().empty()){
                    text = tr("Il vous reste une/des barre(s) entière(s) non utilisée(s) :<br>Liste de la/des barre(s) restante(s) :<br>");
                    text += listToStr(protODC->tronconsRestants()) + "<hr>";
                }

                if(erreur==10){
                    text += tr("Vous n'avez pas eu assez de matière première pour "
                                      "couper tous les tronçons que vous désiriez.<br>Liste de troncons restants:<br>");
                    text += listToStr(protODC->tronconsRestants()) + "<hr>";
                }

                // Liste des coupes
                text += tr("<br>Voici la liste des coupes que vous devez effectuer :<ul>");
                int i;
                for(i = 0; i < protODC->resultats().length(); i++) {
                    text += protODC->resultats()[i]->toStr();
                }

                text += "</ul>" + tr("Vous avez un rendement moyen de ");
                text += QString::number(protODC->rendementTotal(),'g', 4) + "%.";

                m_widgetResultats->updateResultats(text);
                m_widgetGraphique->updateGraphique(protODC->resultats());
                m_tabs->setCurrentIndex(1);
                delete protODC;
            }
        }
    }
}

void FenetrePrincipale::bienConnecte()
{
    setDisabled(false);
}

void FenetrePrincipale::deconnexion()
{
    m_formulaireSaisie->buttonAppliquer()->setDisabled(true);
    QMessageBox::warning(this, tr("Déconnexion du serveur"),
                         tr("Le serveur n'est plus connecté. Vous ne pouvez plus effectuer d'autres requêtes."),
                         QMessageBox::Ok );
}
