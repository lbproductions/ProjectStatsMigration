#include "row.h"

#include "column.h"
#include "database.h"
#include "table.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

namespace LBDatabase {

/******************************************************************************
** RowPrivate
*/
class RowPrivate {
private:
    RowPrivate() :
        id(0),
        table(0)
    {}

    void init();

    friend class Row;
    int id;
    int index;
    Table *table;
};

void RowPrivate::init()
{
}

/******************************************************************************
** Row
*/
/*!
  \class Row

  \brief The Row class represents a row in a Table.

  \ingroup lowlevel-database-classes

  There exists an instance of Row for each row in each table. You can use data()
  and setData() to query an manipulate the content of fields.

  You will seldomly instantiate this class on your own. Use the access and
  creation methods of Table instead (i.e. Table::appendRow() and Table::row()).

  \sa Table, Column
  */

/*!
  \fn void Row::dataChanged(int column, QVariant data)

  This signal is emitted whenever the content of the field in the Column at
  index \a column changes.

  The \a data parameter holds the new value.

  \sa data() and setData().
  */

/*!
  \var Row::d_ptr
  \internal
  */

/*!
  \internal

  Constructs a new row from the contents in the current record of \a query in
  the Table \a table.
  */
Row::Row(int index, int id, Table *table) :
    QObject(table),
    d_ptr(new RowPrivate)
{
    Q_D(Row);
    d->table = table;
    d->index = index;
    d->id = id;
    d->init();
}

/*!
  Destroys the row.
  */
Row::~Row()
{
}

/*!
  Returns the ID of the row.
  */
int Row::id() const
{
    Q_D(const Row);
    return d->id;
}

/*!
  Returns the content stored in the database in this row in the Column at index
  \a column.
  */
QVariant Row::data(int column) const
{
    Q_D(const Row);
    return d->table->value(d->index, column);
}

/*!
  Returns the data stored in the row in the column named \a column or an invalid
  QVariant if this column does not exist in the table of the row.
  */
QVariant Row::data(const QString &column) const
{
    Q_D(const Row);

    Column *c = d->table->column(column);
    if(!c)
        return QVariant();

    return data(c->index());
}

/*!
  Sets the content stored in the database in this row in the Column at index
  \a column to \a data.
  Does nothing if no such column exists in the table of the row.
  */
void Row::setData(int column, const QVariant &data)
{
    Q_D(Row);
    if(d->table->setData(d->index, column,data))
        d->table->database()->setDirty(true);
}

/*!
  Sets the content stored in the database in this row in the Column with the
  name \a column to \a data.
  Does nothing if no such column exists in the table of the row.
  */
void Row::setData(const QString &column, const QVariant &data)
{
    Q_D(const Row);

    Column *c = d->table->column(column);
    if(!c)
        return;

    setData(c->index(), data);
}

/*!
  Returns the table of the row.
  */
Table *Row::table() const
{
    Q_D(const Row);
    return d->table;
}

} // namespace LBDatabase
