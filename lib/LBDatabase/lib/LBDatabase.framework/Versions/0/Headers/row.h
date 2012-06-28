#ifndef LBDATABASE_ROW_H
#define LBDATABASE_ROW_H

#include <QObject>

#include <QVariant>

class QSqlQuery;
class QSqlRecord;

namespace LBDatabase {

class Table;

class RowPrivate;
class Row : public QObject
{
    Q_OBJECT
public:
    ~Row();

    int id() const;
    QVariant data(int column) const;
    QVariant data(const QString &column) const;
    void setData(int column, const QVariant &data);
    void setData(const QString &column, const QVariant &data);

    Table *table() const;

private:
    friend class TablePrivate;

    explicit Row(int index, int id, Table *table);

    QScopedPointer<RowPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Row)
    Q_DISABLE_COPY(Row)
};

} // namespace LBDatabase

#endif // LBDATABASE_ROW_H
