#ifndef LBDATABASE_TABLE_H
#define LBDATABASE_TABLE_H

#include <QSqlTableModel>

namespace LBDatabase {

class Column;
class Database;
class Row;

class TablePrivate;
class Table : public QSqlTableModel
{
    Q_OBJECT

public:
    ~Table();

    QString name() const;
    Database *database() const;


    Column *column(int column) const;
    Column *column(const QString &column) const;
    QList<Column *> columns() const;
    QStringList columnNames() const;

    Column *addColumn(const QString &name, const QString &sqlType, const QVariant &defaultValue = QVariant());
    void removeColumn(const QString &name);
    void changeColumnName(const QString &name, const QString &newName);

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool setData(int row, int column, const QVariant &data);

    Row *row(int id) const;
    Row *rowAt(int index) const;
    QList<Row *> rows() const;

    Row *appendRow();
    void deleteRow(int id);

protected:
    friend class DatabasePrivate;

    Table(const QString &name, Database *database);

    QScopedPointer<TablePrivate> d_ptr;
    Q_DECLARE_PRIVATE(Table)
    Q_DISABLE_COPY(Table)
};

} // namespace LBDatabase

Q_DECLARE_METATYPE(LBDatabase::Table *)

#endif // LBDATABASE_TABLE_H
