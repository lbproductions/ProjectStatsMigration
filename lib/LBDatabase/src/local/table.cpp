#include "table.h"

#include "column.h"
#include "database.h"
#include "row.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStringList>

namespace LBDatabase {

/******************************************************************************
** TablePrivate
*/
class TablePrivate {
private:
    TablePrivate() :
        q_ptr(0),
        database(0)
    {}

    void init();

    Column *addColumn(const QString &name, const QString &sqlType, const QVariant &defaultValue);
    void removeColumn(const QString &name);
    void changeColumnName(const QString &name, const QString &newName);

    Row *appendRow();
    void deleteRow(int id);

    Table *q_ptr;
    Database *database;
    QString name;

    QHash<QString, Column *> columnsByName;
    QList<Column *> columns;
    QHash<int, Row *> rowsById;
    QList<Row *> rows;

    Q_DECLARE_PUBLIC(Table)
};

void TablePrivate::init()
{
    Q_Q(Table);

    q->setTable(name);
    q->setEditStrategy(QSqlTableModel::OnFieldChange);
    q->select();

    QSqlRecord columnNames = q->record();
    int columnCount = columnNames.count();
    columns.reserve(columnCount);
    for(int i = 0; i < columnCount; ++i) {
        Column *column = new Column(columnNames.field(i), q);
        column->setIndex(i);
        columns.append(column);
        columnsByName.insert(column->name(), column);
    }

    while(q->canFetchMore())
        q->fetchMore();

    QSqlQuery query = q->query();
    int rowCount = q->rowCount();
    int idIndex = q->record().indexOf(QLatin1String("id"));
    int id = 0;
    rows.reserve(rowCount);
    rowsById.reserve(rowCount);
    for(int i = 0; i < rowCount; ++i) {
        query.seek(i);
        id = query.value(idIndex).toInt();
        Row *row = new Row(i, id, q);
        rows.append(row);
        rowsById.insert(id, row);
    }
}

Column *TablePrivate::addColumn(const QString &name, const QString &sqlType, const QVariant &defaultValue)
{
    Q_Q(Table);
    if(q->columnNames().contains(name, Qt::CaseInsensitive)) {
        qWarning() << "TablePrivate::addColumn: Duplicate column name" << name;
        return columnsByName.value(name);
    }

    QSqlQuery query(database->sqlDatabase());

    QString queryString = QLatin1String("ALTER TABLE ")+this->name+QLatin1String(" ADD ")+name+
            QLatin1String(" ")+sqlType;
    if(!defaultValue.toString().isEmpty()) {
        queryString += QLatin1String(" DEFAULT ")+defaultValue.toString();
    }
    query.exec(queryString);
    checkSqlError(query);
    query.finish();

    q->clear();
    q->setTable(this->name);
    if(!q->select()) {
        qDebug() << q->lastError();
        return 0;
    }

    QSqlField columnField = q->record().field(name);

    Column *column = new Column(columnField, q);
    column->setIndex(columns.size());
    columns.append(column);
    columnsByName.insert(name, column);
    return column;
}

void TablePrivate::changeColumnName(const QString &name, const QString &newName)
{
    qWarning() << "TablePrivate::changeColumnName: IMPLEMENT ME";
//    Q_Q(Table);
//    if(!q->columnNames().contains(name)) {
//        qWarning() << "TablePrivate::addColumn: No such column" << name;
//        return;
//    }
//    if(q->columnNames().contains(newName)) {
//        qWarning() << "TablePrivate::addColumn: Duplicate column name" << newName;
//        return;
//    }

//    QSqlQuery query(database->sqlDatabase());
//    query.exec(QLatin1String("SELECT sql FROM sqlite_master WHERE name = '")+this->name+QLatin1String("'"));
//    checkSqlError(query);
//    query.first();
//    QString sql = query.value(0).toString();
//    QString replacement = QLatin1String(" ")+newName+QLatin1String(" ");
//    QString search = QLatin1String(" ")+name+QLatin1String(" ");
//    sql = sql.replace(sql.lastIndexOf(search),search.length(),replacement);
//    query.exec(QLatin1String("PRAGMA writable_schema = 1;"));
//    checkSqlError(query);
//    query.exec(QLatin1String("UPDATE SQLITE_MASTER SET sql = '")+sql+
//               QLatin1String("' WHERE NAME = '")+this->name+QLatin1String("';"));
//    checkSqlError(query);
//    query.exec(QLatin1String("PRAGMA writable_schema = 0;"));
//    checkSqlError(query);
//    query.finish();
//    Column *column = columnsByName.value(name);
//    int index = columns.indexOf(column);
//    column->setName(newName);
//    q->select();
//    emit q->headerDataChanged(Qt::Horizontal,index,index);
}

void TablePrivate::removeColumn(const QString &name)
{
    qWarning() << "TablePrivate::removeColumn: IMPLEMENT ME";
//    Q_Q(Table);
//    if(!q->columnNames().contains(name)) {
//        qWarning() << "TablePrivate::addColumn: No such column" << name;
//        return;
//    }
//    if(name == QLatin1String("id")) {
//        qWarning() << "TablePrivate::addColumn: You may not remove the column" << name;
//        return;
//    }

//    QSqlQuery query(database->sqlDatabase());
//    query.exec(QLatin1String("SELECT sql FROM sqlite_master WHERE name = '")+this->name+QLatin1String("'"));
//    checkSqlError(query);
//    query.first();
//    QString sql = query.value(0).toString();
//    QString search = QLatin1String(" ")+name+QLatin1String(" ");
//    int from = sql.lastIndexOf(search) - 1;
//    int to = sql.indexOf(',',from + 1);
//    if(to == -1) {
//        to = sql.indexOf(')',from);
//    }
//    sql = sql.remove(from,to - from);
//    query.exec(QLatin1String("PRAGMA writable_schema = 1;"));
//    checkSqlError(query);
//    query.exec(QLatin1String("UPDATE SQLITE_MASTER SET sql = '")+sql+
//               QLatin1String("' WHERE NAME = '")+this->name+QLatin1String("';"));
//    checkSqlError(query);
//    query.exec(QLatin1String("PRAGMA writable_schema = 0;"));
//    checkSqlError(query);
//    query.finish();

//    q->clear();
//    q->setTable(this->name);
//    if(!q->select()) {
//        qDebug() << q->lastError();
//        return;
//    }

//    Column *column = columnsByName.value(name);
//    int index = columns.indexOf(column);
//    for(int i = index; i < columns.size(); ++i) {
//        columns.at(i)->setIndex(i);
//    }
//    columns.removeAt(index);
//    columnsByName.remove(name);
//    column->deleteLater();
}

Row *TablePrivate::appendRow()
{
    Q_Q(Table);
    int index = rows.count();

    if(!q->insertRecord(-1,q->record()))
        return 0;

    QSqlQuery query = q->query();
    query.seek(index);
    int id = query.lastInsertId().toInt();
    Row *row = new Row(index, id, q);
    rows.append(row);
    rowsById.insert(id, row);
    return row;
}

void TablePrivate::deleteRow(int id)
{
    Q_Q(Table);
    int index = rows.indexOf(rowsById.value(id));
    q->removeRow(index);
    Row *row = rows.takeAt(index);
    rowsById.remove(id);
    row->deleteLater();
}

/******************************************************************************
** Table
*/
/*!
  \class Table

  \brief The Table class represents a table in a SQLite database.

  \ingroup lowlevel-database-classes

  It provides access and manipulation methods for most simple tasks that you
  can perform on tables. name() stores the name, database() the Database of the
  Table.

  You will seldomly instantiate this class on your own. Use the access and
  creation methods of Database instead (i.e. Database::table(),
  Database::tables() and Database::createTable()).

  You can append a Row to the table with appendRow(), you can query the rows by
  id with row() and access all rows().

  Columns may be queried by index (column()) or you access all columns() and
  all columnNames(). Manipulation of the table's signature is achieved through
  addColumn(), removeColumn() and changeColumnName().

  In addition to that the Table class implements QAbstractTableModel and can
  thus easily be added to tree and table views. The model allows editing of
  single fields.

  \sa Database, Column, Row
  */

/*!
  \var Table::d_ptr
  \internal
  */

/*!
  Constructs a Table named \a name in the Database \a database.
  */
Table::Table(const QString &name, Database *database) :
    QSqlTableModel(database, database->sqlDatabase()),
    d_ptr(new TablePrivate)
{
    Q_D(Table);
    d->q_ptr = this;
    d->name = name;
    d->database = database;
    d->init();
}

/*!
  Destroys the table.
  */
Table::~Table()
{
}

/*!
  \property Table::name
  \brief holds the name of the table.

  Note that you can not change the name of a table.
  */
QString Table::name() const
{
    Q_D(const Table);
    return d->name;
}

/*!
  Returns the database containing the table.
  */
Database *Table::database() const
{
    Q_D(const Table);
    return d->database;
}

/*!
  Adds a column named \a name with the SQLite type \a sqlType and the default
  value \a defaultValue to the table.

  Returns the newly created Column. If the column already existed it returns the
  corresponding Column instance and \a 0 if an error occurs.

  \note \a sqlType should be but does not need to be a valid SQLite type.

  \warning This is potentially dangerous as SQLite only supports a tiny subset
  of the "ALTER TABLE" SQL command. This method uses a dirty workaround by
  manipulating ther sqlite_master table directly.

  \sa Column::typeNames()
  */
Column *Table::addColumn(const QString &name, const QString &sqlType, const QVariant &defaultValue)
{
    Q_D(Table);
    Column *col = d->addColumn(name, sqlType, defaultValue);
    database()->setDirty(true);
    return col;
}

/*!
  Removes the column named \a name from the table. Does nothing if no such
  column exists.

  \warning This is potentially dangerous as SQLite only supports a tiny subset
  of the "ALTER TABLE" SQL command. This method uses a dirty workaround by
  manipulating ther sqlite_master table directly.
  */
void Table::removeColumn(const QString &name)
{
    Q_D(Table);
    d->removeColumn(name);
    database()->setDirty(true);
}

/*!
  Deletes the row with ID \a id.

  Does nothing if no such row exists.
  */
void Table::deleteRow(int id)
{
    Q_D(Table);
    d->deleteRow(id);
    database()->setDirty(true);
}

/*!
  Changes the name of the column named \a name to \a newName. Does nothing if
  \a name equals \a newName or if no column \a name exists.

  \warning This is potentially dangerous as SQLite only supports a tiny subset
  of the "ALTER TABLE" SQL command. This method uses a dirty workaround by
  manipulating ther sqlite_master table directly.
  */
void Table::changeColumnName(const QString &name, const QString &newName)
{
    Q_D(Table);
    if(name == newName)
        return;
    d->changeColumnName(name, newName);
    database()->setDirty(true);
}

QVariant Table::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::TextAlignmentRole) {
        return Qt::AlignLeft;
    }

    return QSqlTableModel::headerData(section, orientation, role);
}

Qt::ItemFlags Table::flags(const QModelIndex &index) const
{
    if(index.column() == 0) {
        return QSqlTableModel::flags(index) & ~Qt::ItemIsEditable;
    }

    return QSqlTableModel::flags(index);
}

bool Table::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool ret = QSqlTableModel::setData(index,value, role);

    if(ret)
        database()->setDirty(true);
    else if(lastError().isValid())
        qWarning() << lastError();

    return ret;
}

bool Table::setData(int row, int column, const QVariant &data)
{
    QSqlRecord r = record(row);
    r.setValue(column, data);

    bool ret = setRecord(row, r);

    if(!ret && lastError().isValid())
        qWarning() << lastError();

    return ret;
}

/*!
  Returns the column with the index \a column. The indexes are sorted by the
  first call to QSqlDatabase::record() and therefore not deterministically
  sorted from execution to execution.
  */
Column *Table::column(int column) const
{
    Q_D(const Table);
    return d->columns.at(column);
}

/*!
  Returns the column with the name \a column.
  */
Column *Table::column(const QString &column) const
{
    Q_D(const Table);
    return d->columnsByName.value(column, 0);
}

/*!
  Returns a list of all columns in the table.
  */
QList<Column *> Table::columns() const
{
    Q_D(const Table);
    return d->columns;
}

/*!
  Returns a list of all column names in the table.
  */
QStringList Table::columnNames() const
{
    Q_D(const Table);
    return d->columnsByName.keys();
}

/*!
  Appends a new Row to the table.

  The row will be populated with the default values of the SQLite table.

  Returns the newly created row.
  */
Row *Table::appendRow()
{
    Q_D(Table);
    Row *row = d->appendRow();
    database()->setDirty(true);
    return row;
}

/*!
  Returns the row with the ID \a id or \a 0 if no such row exists.
  */
Row *Table::row(int id) const
{
    Q_D(const Table);
    return d->rowsById.value(id, 0);
}

/*!
  Returns the row at \a index or \a 0 if no such row exists.
  */
Row *Table::rowAt(int index) const
{
    Q_D(const Table);
    if(index >= d->rows.count())
        return 0;

    return d->rows.at(index);
}

/*!
  Returns a list of all rows in the table.
  */
QList<Row *> Table::rows() const
{
    Q_D(const Table);
    return d->rows;
}

} // namespace LBDatabase
