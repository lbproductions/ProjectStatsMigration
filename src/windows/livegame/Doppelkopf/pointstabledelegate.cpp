#include "pointstabledelegate.h"

#include "pointstable.h"
#include "pointstableitem.h"

#include <QLineEdit>

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

}
