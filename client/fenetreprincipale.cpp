/*
 * \file fenetreprincipale.cpp
 * \brief Source de la classe FenetrePrincipale
 * \author Pierre-Emmanuel PIRNAY 11296315
 * \date 2015
 */

#include "fenetreprincipale.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) : QWidget(parent)
{
    bool ok, continueBoucle=true;

    // la boucle permet de proposer plusieurs fois de rentrer l'adresse IP et le port en cas d'erreur
    while (continueBoucle){
        // demande l'IP
        m_ip = QInputDialog::getText(this, tr("Saisie de l'adresse IP"),
                                              tr("Adresse IP"), QLineEdit::Normal,
                                              "", &ok );
        if (ok){
            if(!m_ip.isEmpty()) {
                // récupère le port
                m_port = QInputDialog::getInt(this, tr("Saisie du port"),
                                          tr("Port"), 0, 1024, 65536, 1, &ok );
                if (!ok){
                    qApp->quit();   // quitte l'application si 'Cancel' a été cliqué
                }
            }
            else
                continue;   // redemande l'IP si celle-ci est toujours vide
        }
        else
            qApp->quit();   // quitte l'application si 'Cancel' a été cliqué

        // connexion au serveur
        m_socket = new QTcpSocket(this);

        //connexion
        m_socket->connectToHost(m_ip, m_port);

        // attend la connextion
        if(! m_socket->waitForConnected()) {
            // Affichage du message d'errur
            QMessageBox erreurMessageBox;
            switch (m_socket->error()) {
                case QAbstractSocket::HostNotFoundError:
                    erreurMessageBox.setText(tr("Erreur : le serveur n'a pas pu être trouvé."));
                    erreurMessageBox.setInformativeText(tr("Vérifiez l'adresse IP et le port."));
                break;
            case QAbstractSocket::ConnectionRefusedError:
                erreurMessageBox.setText(tr("Erreur : le serveur a refusé la connexion."));
                erreurMessageBox.setInformativeText(tr("Vérifiez si le serveur a bien été lancé. Vérifiez aussi l'adresse IP et le port."));
                break;
            case QAbstractSocket::RemoteHostClosedError:
                erreurMessageBox.setText(tr("Erreur : le serveur a coupé la connexion."));
                erreurMessageBox.setInformativeText(tr("Veuillez réessayer plus tard."));
                break;
            default:
                erreurMessageBox.setText(tr("Erreur : ") + m_socket->errorString());
                break;
            }

            erreurMessageBox.setIcon(QMessageBox::Critical);
            erreurMessageBox.setWindowTitle(tr("Erreur - Connexion au serveur"));
            erreurMessageBox.setStandardButtons(QMessageBox::Close | QMessageBox::Retry);
            if (erreurMessageBox.exec() == QMessageBox::Close) {
                qApp->quit();
            }
         }
         else
             continueBoucle = false;    // passe à la suite
    }

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
        QString text("");

        // Envoi du message au serveur
        QString message = ProtocoleODC_client::createMessage(resultatsBarres, resultatsTron,m_formulaireSaisie->epaisseurLame());
        if(m_socket->write(qPrintable(message)) == -1) {
            QMessageBox::warning(this, tr("Erreur - Envoi du formulaire"),
                                 tr("Une erreur est apparu lors de l'envoi du formulaire au serveur. "));
            return;
        }

        // Réception des résultats
        forever{
            if(m_socket->canReadLine())
                break;
        }
        ProtocoleODC_client * protODC = new ProtocoleODC_client(m_socket->readLine());
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
            erreurMsgB.setDetailedText(message);
            erreurMsgB.setIcon(QMessageBox::Critical);
            erreurMsgB.exec();
            return;
        }

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
