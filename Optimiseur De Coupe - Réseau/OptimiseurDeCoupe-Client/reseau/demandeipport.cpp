#include "demandeipport.h"

DemandeIpPort::DemandeIpPort(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(tr("Optimiseur de Coupe"));
    setWindowIcon(QIcon("../mainIcon.ico"));
    setWindowModality(Qt::ApplicationModal);

    // Label
    QLabel * message = new QLabel(tr("Veuillez rentrer l'ip et le port du serveur :"));

    // IP
    m_ip = new QLineEdit;
    m_ip->setPlaceholderText(tr("Adresse IP"));
    connect(m_ip, SIGNAL(textChanged(QString)), this, SLOT(ipModifie(QString)));
    connect(m_ip, SIGNAL(returnPressed()), this, SLOT(boutonConnexion()));

    // Port
    m_port = new QSpinBox;
    m_port->setMinimum(1024);
    m_port->setMaximum(65536);
    m_port->setValue(1050);

    // Buttons
    m_connexion = new QPushButton(tr("Se connecter"));
    m_connexion->setDisabled(true);
    m_connexion->setDefault(true);
    QPushButton * quitter = new QPushButton(tr("Quitter"));
    QHBoxLayout * boutonsLayout = new QHBoxLayout;
    boutonsLayout->addWidget(m_connexion);
    boutonsLayout->addWidget(quitter);
    QWidget * boutons = new QWidget;
    boutons->setLayout(boutonsLayout);
    connect(m_connexion, SIGNAL(clicked()), this, SLOT(boutonConnexion()));
    connect(quitter, SIGNAL(clicked()), qApp, SLOT(quit()));

    // layout
    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(message);
    mainLayout->addWidget(m_ip);
    mainLayout->addWidget(m_port);
    mainLayout->addWidget(boutons);

    setLayout(mainLayout);
}

QString DemandeIpPort::ip() const
{
    return m_ip->text();
}

int DemandeIpPort::port() const
{
    return m_port->value();
}

void DemandeIpPort::boutonConnexion()
{
    close();
    emit demandeConnexion();
}

void DemandeIpPort::ipModifie(QString ip)
{
    if(QString::compare(ip, "") != 0)
        m_connexion->setDisabled(false);
    else
        m_connexion->setDisabled(true);
}

