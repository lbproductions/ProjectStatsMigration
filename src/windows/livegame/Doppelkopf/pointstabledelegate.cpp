#include "pointstabledelegate.h"

#include "pointstable.h"
#include "pointstableitem.h"

#include <QLineEdit>
#include <QPainter>
#include <QDebug>

namespace DokoLiveGameWindowNS {

PointsTableDelegate::PointsTableDelegate(PointsTable *parent) :
    QItemDelegate(parent),
    m_table(parent)
{
}

void PointsTableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);

    if(lineEdit)
        lineEdit->setText(QString::number(m_table->itemAtIndex(index)->points()));
}

void PointsTableDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    Q_UNUSED(model)
    QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);

    if(lineEdit)
        m_table->itemAtIndex(index)->setPoints(lineEdit->text().toInt());
}

void PointsTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QTableWidgetItem *item = m_table->itemAtIndex(index);

    QLinearGradient gradient(option.rect.topLeft(), option.rect.bottomLeft());
    QColor color = item->backgroundColor();
    gradient.setColorAt(0.0, color);
    gradient.setColorAt(1.0, color.darker(200));
    QBrush brush(gradient);

    painter->save();
    painter->setRenderHints(QPainter::Antialiasing, true);
    if(color == QColor() || color == QColor(0,0,0))
        painter->setBrush(QColor(0,0,0,0));
    else
        painter->setBrush(brush);

    painter->setPen(QColor(0,0,0,0));

    QPainterPath path;
    path.addRoundedRect(option.rect,4.0,4.0);
    painter->drawPath(path);

    QTextOption to(Qt::AlignCenter);
    static QColor shadow(51,51,51,255);
    static QColor foreground(250,250,250,255);

    QFont font = item->font();

    painter->setFont(font);
    painter->setPen(shadow);
    QRect shadowpos = option.rect;
    shadowpos.adjust(0,1,0,1);
    painter->drawText(shadowpos, item->text(), to);

    painter->setPen(foreground);
    painter->drawText(option.rect, item->text(), to);

    painter->restore();
}

}
