#ifndef LBDATABASE_COLUMN_H
#define LBDATABASE_COLUMN_H

#include <QObject>

#include <QVariant>

class QSqlField;

namespace LBDatabase {

class Table;

class ColumnPrivate;
class Column : public QObject
{
    Q_OBJECT

public:
    enum Type {
        Null,
        Integer,
        Real,
        Text,
        Blob
    };

    ~Column();

    QString name() const;
    QString typeName() const;
    Table *table() const;
    Type type() const;
    int index() const;

    static Type variantTypeToType(QVariant::Type type);
    static QString typeToName(Type type);
    static QStringList typeNames();

Q_SIGNALS:
    void nameChanged(QString name);
    void indexChanged(int index);

private:
    friend class TablePrivate;

    explicit Column(const QSqlField &field, Table *table);

    void setName(const QString &name);
    void setIndex(int index);

    QScopedPointer<ColumnPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Column)
    Q_DISABLE_COPY(Column)
};

} // namespace LBDatabase

#endif // LBDATABASE_COLUMN_H
