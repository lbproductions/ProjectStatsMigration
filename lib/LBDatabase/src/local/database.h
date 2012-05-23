#ifndef LBDATABASE_DATABASE_H
#define LBDATABASE_DATABASE_H

#include <QObject>

#include <QMetaType>
#include <QSharedPointer>

class QSqlDatabase;
class QSqlQuery;

namespace LBDatabase {

class Table;

bool checkSqlError(const QSqlQuery &query);

class DatabasePrivate;
class Database : public QObject
{
    Q_OBJECT
public:
    static QList<Database*> instances();
    static Database *instance(const QString &fileName);

    ~Database();

    bool open();
    bool refreshConnection();
    void close();

    bool isDirty() const;

    bool isOpen() const;
    QString fileName() const;
    QSqlDatabase sqlDatabase() const;

    QList<Table *> tables() const;
    QStringList tableNames() const;
    Table *table(const QString &name) const;
    Table *createTable(const QString &name);

public Q_SLOTS:
    void setDirty(bool dirty);

Q_SIGNALS:
    void opened();
    void closed();
    void dirtyChanged(bool dirty);

private:
    explicit Database(const QString &fileName, QObject *parent);

    void setOpen(bool open);

    QScopedPointer<DatabasePrivate> d_ptr;
    Q_DECLARE_PRIVATE(Database)
    Q_DISABLE_COPY(Database)
};

} // namespace LBDatabase

Q_DECLARE_METATYPE(LBDatabase::Database *)

#endif // LBDATABASE_DATABASE_H
