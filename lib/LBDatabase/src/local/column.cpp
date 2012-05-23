#include "column.h"

#include "table.h"

#include <QDebug>
#include <QSqlField>
#include <QStringList>

namespace LBDatabase {

/******************************************************************************
** Column Private
*/

class ColumnPrivate {
    explicit ColumnPrivate() :
        table(0),
        type(Column::Null),
        index(-1)
    {}

    friend class Column;
    Table *table;
    QString name;
    Column::Type type;
    int index;
};

/******************************************************************************
** Column
*/
/*!
  \class Column

  \brief The Column class represents a column in an instance of the low-level
  database class Table.

  \ingroup database-lowlevel-classes

  It provides easy access to information about a table's columns through name()
  and type().

  You will seldomly instantiate (or even use) this class on your own. Use the
  access, creation and manipulation methods of Table instead (i.e.
  Table::addColumn(), Table::removeColumn(), and Table::changeColumnName()).

  To access and manipulate values in a column you will have to use Row instead.

  \sa Table, Row
*/

/*!
  \enum Column::Type
  \brief Lists all possible SQLite types.

  \sa type(), typeName(), variantTypeToType(), typeToName() and typeNames()
  */

/*!
  \fn void Column::nameChanged(QString name)

  This signals is emitted when the column's name changes. The \a name parameter
  holds the new name of the column.

  \sa name
*/

/*!
  \fn void Column::indexChanged()

  This signals is emitted when the column's internal index changes.

  \sa name
*/

/*!
  \var Column::d_ptr
  \internal
  */

/*!
  \internal

  Constructs a column which represents the column \a field in the Table \a
  table.
*/
Column::Column(const QSqlField &field, Table *table) :
    QObject(table),
    d_ptr(new ColumnPrivate)
{
    Q_D(Column);
    d->table = table;
    d->name = field.name();
    d->type = Column::variantTypeToType(field.type());
}

/*!
  Destroys the column.
*/
Column::~Column()
{
}

/*!
  \property Column::name
  \brief the name of the column

  This is always synchronized with the actual database and may only be changed
  by the Table.
*/
/*!
  Returns the name of the column.
  */
QString Column::name() const
{
    Q_D(const Column);
    return d->name;
}

/*!
  Sets the name of the column to \a name.
  */
void Column::setName(const QString &name)
{
    Q_D(Column);
    if(name == d->name)
        return;

    d->name = name;
    emit nameChanged(name);
}

/*!
  \property Column::type
  \brief The SQLite type of this column.

  This property is being guessed based upon creation based on the QSqlField of
  this column and can not be changed by the user.

  \sa typeName(), variantTypeToType(), typeToName() and typeNames()
*/
Column::Type Column::type() const
{
    Q_D(const Column);
    return d->type;
}

/*!
  Returns the index of this column in its table.
  */
int Column::index() const
{
    Q_D(const Column);
    return d->index;
}

/*!
  Sets the index of the column to \a index.
  */
void Column::setIndex(int index)
{
    Q_D(Column);
    if(index == d->index)
        return;

    d->index = index;
    emit indexChanged(index);
}

/*!
  Returns the name of the type of the column as returned by typeToName().
*/
QString Column::typeName() const
{
    Q_D(const Column);
    return Column::typeToName(d->type);
}

/*!
  Returns the table that this column belongs to.
*/
Table *Column::table() const
{
    Q_D(const Column);
    return d->table;
}

/*!
  Maps the \a type parameter to a suitable SQLite type.

  Returns Column::Blob, if no suitable type could be found.

  \sa http://www.sqlite.org/datatype3.html
*/
Column::Type Column::variantTypeToType(QVariant::Type type)
{
    switch(type) {
    case QVariant::DateTime:
    case QVariant::Date:
    case QVariant::String:
    case QVariant::Pixmap:
        return Text;
    case QVariant::Double:
        return Real;
    case QVariant::Int:
        return Integer;
    case QVariant::Invalid:
    case QVariant::BitArray:
    case QVariant::Bitmap:
    case QVariant::Bool:
    case QVariant::Brush:
    case QVariant::ByteArray:
    case QVariant::Char:
    case QVariant::Color:
    case QVariant::Cursor:
    case QVariant::EasingCurve:
    case QVariant::Font:
    case QVariant::Hash:
    case QVariant::Icon:
    case QVariant::Image:
    case QVariant::KeySequence:
    case QVariant::Line:
    case QVariant::LineF:
    case QVariant::List:
    case QVariant::Locale:
    case QVariant::LongLong:
    case QVariant::Map:
    case QVariant::Matrix:
    case QVariant::Transform:
    case QVariant::Matrix4x4:
    case QVariant::Palette:
    case QVariant::Pen:
    case QVariant::Point:
    case QVariant::PointF:
    case QVariant::Polygon:
    case QVariant::Quaternion:
    case QVariant::Rect:
    case QVariant::RectF:
    case QVariant::RegExp:
    case QVariant::Region:
    case QVariant::Size:
    case QVariant::SizeF:
    case QVariant::SizePolicy:
    case QVariant::StringList:
    case QVariant::TextFormat:
    case QVariant::TextLength:
    case QVariant::Time:
    case QVariant::UInt:
    case QVariant::ULongLong:
    case QVariant::Url:
    case QVariant::Vector2D:
    case QVariant::Vector3D:
    case QVariant::Vector4D:
    case QVariant::UserType:
    default:
        break;
    }

    qWarning() << "Column::variantTypeToType: Unkown type:" << type << "Returning \"Blob\".";
    return Blob;
}

/*!
  Returns a string, which corresponds to \a type.

  This string is always being taken from typeNames().
*/
QString Column::typeToName(Type type)
{
    return Column::typeNames().at(static_cast<int>(type));
}

/*!
  Returns a list of all possible types known to SQLite.

  \sa http://www.sqlite.org/datatype3.html
*/
QStringList Column::typeNames()
{
    QStringList names;
    names << "NULL"
          << "INTEGER"
          << "REAL"
          << "TEXT"
          << "BLOB";
    return names;
}

} // namespace LBDatabase
