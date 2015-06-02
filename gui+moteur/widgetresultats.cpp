#include "widgetresultats.h"

WidgetResultats::WidgetResultats(QFont & fontTitre, QWidget *parent) : QWidget(parent)
{
    // Label Titre
    QLabel * labelTitre = new QLabel(tr("Résultats"));
    labelTitre->setFont(fontTitre);

    // Label Résultats
    m_labelResultat = new QTextEdit("Veuillez remplir le formulaire de saisie et cliquer sur \"Appliquer\".");
    m_labelResultat->setReadOnly(true);
    m_labelResultat->setMinimumSize(530,310);
    m_labelResultat->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    m_labelResultat->setFrameShape(QFrame::NoFrame);

    // Bouton quitter
    QPushButton * buttonQuitter = new QPushButton(tr("Quitter"));
    QPushButton * buttonSaveHTML = new QPushButton(tr("Enregistrer en HTML"));
    QHBoxLayout * layoutBouttons = new QHBoxLayout;
    QWidget * widgetBouttons = new QWidget();
    layoutBouttons->addWidget(buttonSaveHTML);
    layoutBouttons->addWidget(buttonQuitter);
    widgetBouttons->setLayout(layoutBouttons);

    // Layout
    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(labelTitre,0, Qt::AlignTop);
    mainLayout->addWidget(m_labelResultat);
    mainLayout->addWidget(widgetBouttons, 0, Qt::AlignBottom | Qt::AlignRight);

    setLayout(mainLayout);

    // Connexion
    QObject::connect(buttonQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void WidgetResultats::updateResultats(QString & text){
    m_labelResultat->setText(text);
}

