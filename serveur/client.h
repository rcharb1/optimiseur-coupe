/* client.h
 * Optimiseur de Coupe
 * 2015 - Rebecca Charbit
 */

#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThreadPool>
#include <QString>
#include "task.h"

// Gère la socket et le thread pour chaque client connecté
class Client : public QObject
{
    Q_OBJECT
	public:
    	explicit Client(QObject *parent = 0);
    	void setSocket(qintptr Descriptor);

	signals:

	public slots:
		void connected();
		void disconnected();

		// Récupère le message du client et lance le thread
		void readyRead();

		// Envoie les résultats
		void TaskResult(QString message);

	private:
		QTcpSocket *socket;
};

#endif // CLIENT_H
