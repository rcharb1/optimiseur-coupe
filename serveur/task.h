/* task.h
 * Optimiseur de Coupe
 * 2015 - Rebecca Charbit
 */

#ifndef TASK_H
#define TASK_H

#include <QRunnable>
#include <QObject>
#include <QRunnable>
#include <QString>
#include "reseau/protocoleodc_serveur.h"
#include "moteur/MoteurCalculs.h"
#include "moteur/List.h"
#include <QDebug>

// Lance le moteur et utilise la classe ProtocoleODC_serveur

class Task : public QObject, public QRunnable
{
		Q_OBJECT
	public:
		Task(QString messageClient);
	private:
		QString m_messageClient;
	signals:
		// Renvoie le résultat au thread principale
		void Result(QString message);

	protected:
		// la fonction lancée après la création du thread
		void run();
};

#endif // TASK_H
