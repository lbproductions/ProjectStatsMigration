#include "itunesapplybar.h"

#include <QHBoxLayout>
#include <QFile>
#include <QPushButton>

namespace LBGui {

ItunesApplyBar::ItunesApplyBar(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *l = new QHBoxLayout(this);
    l->setSpacing(0);
    l->setContentsMargins(0,0,0,0);
    setBackgroundRole(QPalette::Base);

    setStyleSheet("QWidget { margin: 0; padding: 0; }");

    QWidget *contentWidget = new QWidget(this);
    contentWidget->setObjectName("contentWidget");
    m_contentLayout = new QHBoxLayout(contentWidget);
    QFile stylesheet1(QLatin1String(":/itunesApplyBar/stylesheet"));
    if(stylesheet1.exists()) {

        stylesheet1.open(QFile::ReadOnly);
        contentWidget->setStyleSheet(stylesheet1.readAll());
        stylesheet1.close();
    }
    m_contentLayout->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    contentWidget->setLayout(m_contentLayout);
    l->addWidget(contentWidget);

    QWidget *buttonWidget = new QWidget(this);
    buttonWidget->setObjectName("buttonBackground");
    QFile stylesheet(QLatin1String(":/itunesApplyBar/stylesheet_button"));
    if(stylesheet.exists()) {

        stylesheet.open(QFile::ReadOnly);
        buttonWidget->setStyleSheet(stylesheet.readAll());
        stylesheet.close();
    }
    QVBoxLayout *buttonLayout = new QVBoxLayout(buttonWidget);
    buttonLayout->setContentsMargins(14,14,14,14);
    QPushButton *applyButton = new QPushButton(tr("Export"));
    applyButton->setMinimumSize(60,22);
    connect(applyButton, SIGNAL(clicked()), this, SIGNAL(applyClicked()));

    buttonLayout->addWidget(applyButton);
    buttonWidget->setLayout(buttonLayout);
    buttonWidget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);


    l->addWidget(buttonWidget);
    setFixedHeight(96);
    setLayout(l);
}

void ItunesApplyBar::setWidget(QWidget *widget)
{
    m_contentLayout->insertWidget(0,widget);
}

} // namespace LBGui
