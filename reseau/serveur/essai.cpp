#include "protocoleodc_serveur.h"
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


int main (int argc, char * argv[])
{
    QApplication app(argc, argv);

    // Chargement de la traduction
    QString locale = QLocale::system().name().section('_', 0, 0);
    return app.exec();
