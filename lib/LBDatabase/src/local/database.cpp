#include "database.h"

#include "table.h"

#include <QSqlDatabase>
#include <QMutexLocker>
#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>
#include <QMetaType>

#include <QDebug>

namespace LBDatabase {

/******************************************************************************
** Global
*/
bool checkSqlError(const QSqlQuery &query) {
    if(query.lastError().isValid()) {
        qWarning() << query.lastQuery();
        qWarning() << query.lastError();
        return false;
    }
    return true;
}

/******************************************************************************
** DatabasePrivate
*/
class DatabasePrivate {
    DatabasePrivate() : q_ptr(0), open(false), dirty(false) {}

    bool openSqlDatabase();
    void createTableInstances();
    Table *createTableInstance(const QString &name);

    Q_DECLARE_PUBLIC(Database)
    Database * q_ptr;

    static QHash<QString, Database*> instances;

    QString fileName;
    QMap<QString, Table*> tables;
    bool open;
    bool dirty;
};

QHash<QString, Database*> DatabasePrivate::instances = QHash<QString, Database*>();

void DatabasePrivate::createTableInstances()
{
    Q_Q(Database);
    foreach(QString name, q->tableNames()) {
        createTableInstance(name);
    }
}

Table *DatabasePrivate::createTableInstance(const QString &name)
{
    Q_Q(Database);
    Table *table = new Table(name, q);
    tables.insert(name, table);
    return table;
}

bool DatabasePrivate::openSqlDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", fileName);
    db.setDatabaseName(fileName);
    db.setUserName("projectstats");
    db.setPassword("projectstats");
    if(!db.open()) {
        qCritical() << "Database::loadFile: Could not open database file" << fileName;
        qCritical() << "Database::loadFile: " << db.lastError();
        return false;
    }
    return true;
}

/******************************************************************************
** Database
*/
/*!
  \class Database

  \brief The Database class represents a low-level SQLite database.

  \defgroup lowlevel-database-classes Low-Level Database Classes

  It is the starting point for opening and working with a SQLite file. You can
  only instantiate one Database per file, which is created by and afterwards
  globally accessable via instance(). Before using a new database you have to
  call open() and make sure it succeeds. All currently open databases can be
  queried by instances().

  You work with the database by accessing tables with tables(), table(),
  tableNames() and createTable() or directly through the sqlDatabase().
  Working directly on the database is inadvisable, since the internal
  datastructure will be out of sync with the database file and you would have
  to reinstantiate the whole database (which is currently not possible :-))
*/

/*!
  \fn void Database::opened()

  This signal is emitted when the database is opened. This can happen when
  calling open() or refreshConnection().

  \sa isOpen()
  */

/*!
  \fn void Database::closed()

  This signal is emitted when the database is closed. This can currently only
  happen when calling refreshConnection().

  \sa isOpen()
  */

/*!
  \fn void Database::dirtyChanged()

  This signal is emitted when something in the database is being edited. This
  means everything from changing names or content or adding column, tables, rows
  etc.
  */

/*!
  \var Database::d_ptr
  \internal
  */

/*
  Static
  */
/*!
  Returns a Database instance, which works on the SQLite database \a fileName.

  Since there may be only one instance per file, this method returns the same
  instance each time you call it with the same file name. This is useful because
  you can globally access the same instance of a database.

  Note that you need to call open() the first time you instantiate a Database.
*/
Database *Database::instance(const QString &fileName)
{
    static QMutex mutex(QMutex::Recursive);
    static QObject guard;
    QMutexLocker locker(&mutex);
    Q_UNUSED(locker)

    if(DatabasePrivate::instances.contains(fileName)) {
        return DatabasePrivate::instances.value(fileName);
    }

    Database* database = new Database(fileName, &guard);
    DatabasePrivate::instances.insert(fileName, database);
    return database;
}

/*!
  Returns a list of all Database instances.
*/
QList<Database *> Database::instances()
{
    return DatabasePrivate::instances.values();
}

/*
  Members
  */
/*!
  \internal

  Constructs a new database which works on \a fileName.
*/
Database::Database(const QString &fileName, QObject *parent) :
    QObject(parent),
    d_ptr(new DatabasePrivate)
{
    Q_D(Database);
    d->q_ptr = this;
    d->fileName = fileName;
}

/*!
  Destroys the database.
*/
Database::~Database()
{
}

/*!
  \property Database::open
  \brief true if the database has an open connection.

  \sa open()
*/
/*!
  Returns true if the database is open, i.e. if open() has successfully been
  called and established a valid QSqlDatabase connection.
  */
bool Database::isOpen() const
{
    Q_D(const Database);
    return d->open;
}

/*!
  \internal

  Set the open property.
  */
void Database::setOpen(bool open)
{
    Q_D(Database);
    if(d->open == open)
        return;

    d->open = open;
    if(open) {
        emit opened();
    }
    else {
        emit closed();
    }
}

/*!
  Opens the connection to the QSqlDatabase.

  Returns true upon succes and false otherwise. If the database is already open
  this method does nothing and returns true.
*/
bool Database::open()
{
    Q_D(Database);
    if(!d->open)
        d->open = d->openSqlDatabase();
    if(d->open && d->tables.isEmpty())
        d->createTableInstances();
    setOpen(true);
    return d->open;
}

/*!
  Refreshes the QSqlDatabase connection.

  This does not refresh the internal data structure and should therefore only be
  called internally.
  */
bool Database::refreshConnection()
{
    setOpen(false);
    QSqlDatabase::removeDatabase(fileName());
    return open();
}

/*!
  Closes the QSqlDatabase connection, sets open to false and emits closed().
  */
void Database::close()
{
    Q_D(Database);
    if(!d->open)
        return;
    QSqlDatabase::removeDatabase(d->fileName);
    setOpen(false);
}

/*!
  Returns true if anything in the database has been changed since the creation
  of the instance or the last time dirty has been set to false.
  */
bool Database::isDirty() const
{
    Q_D(const Database);
    return d->dirty;
}

/*!
  Sets the dirty state of this database to \a dirty.

  Internally each class sets this state to true, each time anything is changed.
  */
void Database::setDirty(bool dirty)
{
    Q_D(Database);
    if(d->dirty == dirty)
        return;

    d->dirty = dirty;
    emit dirtyChanged(dirty);
}

/*!
  Returns a list of all Table instances of this database.
  */
QList<Table *> Database::tables() const
{
    Q_D(const Database);
    return d->tables.values();
}

/*!
  Creates a new Table named \a name in the database.

  Does nothing when a table with this name already exists and returns the
  already existing instance.

  Returns the newly created Table or \a 0 upon errors.

  \sa tableNames()
  */
Table *Database::createTable(const QString &name)
{
    if(tableNames().contains(name, Qt::CaseInsensitive)) {
        qWarning() <<  "Database::createTable: This table already exists:" << name;
        return table(name);
    }

    QSqlQuery query(sqlDatabase());
    query.exec(QLatin1String("CREATE TABLE ")+name+QLatin1String(" (id INTEGER PRIMARY KEY)"));
    if(!checkSqlError(query)) return 0;

    Q_D(Database);
    Table *table = d->createTableInstance(name);
    setDirty(true);
    return table;
}

/*!
  Returns the Table instance for the table named \a name, or \a 0 if no such
  table exists.
*/
Table *Database::table(const QString &name) const
{
    Q_D(const Database);
    return d->tables.value(name, 0);
}

/*!
  Returns a QSqlDatabase connection to the file of this database.

  \warning This connection should only be used internally to modify the
  database, since the data structure will refresh itself. Reading operations
  should be safe.
*/
QSqlDatabase Database::sqlDatabase() const
{
    Q_D(const Database);
    return QSqlDatabase::database(d->fileName);
}

/*!
  Returns a list of all table names in the database.

  This is currently equivalent to QSqlDatabase::tables().
*/
QStringList Database::tableNames() const
{
    return sqlDatabase().tables();
}

/*!
  Returns the file which the database works on.
  */
QString Database::fileName() const
{
    Q_D(const Database);
    return d->fileName;
}

} // namespace LBDatabase
