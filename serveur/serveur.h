/* serveur.h
 * Optimiseur de Coupe
 * 2015 - Rebecca Charbit
 */

#ifndef SERVEUR_H
#define SERVEUR_H

#include <QApplication>
#include <QMessageBox>
#include <QInputDialog>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include "client.h"
#include <QDebug>

// Serveur : gère les sockets
class Serveur : public QTcpServer
{
		Q_OBJECT
	public:
		explicit Serveur(QObject *parent = 0);
		// fonction principale, lance le serveur
		void lancement();
	protected:
		// gère les connexions entrantes
		void incomingConnection(qintptr socketDescriptor);

	signals:
		void quitter();
	public slots:

};

#endif // SERVEUR_H
