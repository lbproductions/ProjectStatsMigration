#include "sheet.h"

#include <QFile>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QVBoxLayout>

namespace LBGui {

Sheet::Sheet(QWidget *parent) :
    QFrame(parent),
    m_widget(0)
{
    QFile stylesheet(QLatin1String(":/sheet/stylesheet"));
    if(stylesheet.exists()) {

        stylesheet.open(QFile::ReadOnly);
        setStyleSheet(stylesheet.readAll());
        stylesheet.close();
    }

    QVBoxLayout* layout = new QVBoxLayout(this);

    m_header = new QWidget(this);
    QHBoxLayout *headerLayout = new QHBoxLayout(m_header);
    m_iconLabel = new QLabel(m_header);
    m_iconLabel->setVisible(false);
    m_titleLabel = new QLabel(m_header);
    m_titleLabel->setTextFormat(Qt::RichText);
    headerLayout->addWidget(m_iconLabel);
    headerLayout->addWidget(m_titleLabel);
    headerLayout->addStretch(1);
    QLabel *editLabel = new QLabel(tr("<font color=\"#2d5be8\">Edit</font>"), m_header);
    editLabel->setTextFormat(Qt::RichText);
    headerLayout->addWidget(editLabel);
    headerLayout->setContentsMargins(0,0,0,0);
    m_header->setLayout(headerLayout);

    layout->addWidget(m_header);

    QFrame *line = new QFrame(this);
    line->setGeometry(QRect(320, 150, 118, 1));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    layout->addWidget(line);
    m_widget = new QWidget(this);
//    m_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(m_widget);

//    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setLayout(layout);
}

void Sheet::setHeaderIcon(const QIcon &icon)
{
    m_iconLabel->setPixmap(QPixmap(icon.pixmap(icon.availableSizes().at(0))));
}

void Sheet::setHeaderTitle(const QString &title)
{
    m_titleLabel->setText("<b>"+title+"</b>");
}

void Sheet::setWidget(QWidget *widget)
{
    if(m_widget)
        m_widget->setVisible(false);

    m_widget = widget;
    layout()->addWidget(widget);
}

}
