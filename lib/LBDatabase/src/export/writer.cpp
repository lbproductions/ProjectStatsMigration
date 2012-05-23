#include "writer.h"

#include "cppexporter.h"

#include <QRegExp>
#include <QFile>
#include <QTextStream>

namespace LBDatabase {

namespace {
const QString ExtraContentBegin("\t// Write anything you want to remain unchanged between these comments: \n\t//START");
const QString ExtraContentEnd("\n\t// END");
}

Writer::Writer(const CppExporter *const exporter) :
    m_exporter(exporter)
{
}

void Writer::startNamespace(QString &file) const
{
    QString namespaceName = m_exporter->namespaceName();
    if(!namespaceName.isEmpty())
        writeNamespaceBegin(namespaceName, file);
}

void Writer::endNamespace(QString &file) const
{
    QString namespaceName = m_exporter->namespaceName();
    if(!namespaceName.isEmpty())
        writeNamespaceEnd(namespaceName, file);
}

void Writer::writeNamespaceBegin(const QString &namespaceName, QString &file) const
{
    file.append(QLatin1String("namespace ")+namespaceName+QLatin1String(" {\n"));
}

void Writer::writeNamespaceEnd(const QString &namespaceName, QString &file) const
{
    file.append(QLatin1String("} // namespace ")+namespaceName+QLatin1String("\n\n"));
}

QString Writer::makeClassname(const QString &name) const
{
    QString classname = name.trimmed().remove(' ').remove('.');
    QRegExp reg("(^\\d*)");
    int pos = reg.indexIn(classname);
    if(pos > -1) {
        QString headingNumbers = reg.cap(0);
        classname = classname.remove(0, headingNumbers.length()).append(headingNumbers);
    }
    return classname.left(1).toUpper()+classname.mid(1);
}

QString Writer::makeMethodName(const QString &name) const
{
    QString classname = makeClassname(name);
    return classname.left(1).toLower()+classname.mid(1);
}

void Writer::startHeader(const QString &classname, QString &header) const
{
    QString guard = m_exporter->namespaceName().toUpper();
    if(!guard.isEmpty())
        guard += QLatin1String("_");
    guard += classname.toUpper() + QLatin1String("_H\n");

    header.append(QLatin1String("#ifndef "));
    header.append(guard);
    header.append(QLatin1String("#define "));
    header.append(guard);
    header.append(QLatin1String("\n#include <LBDatabase/LBDatabase.h>\n\n"));
}

void Writer::endHeader(const QString &classname, QString &header) const
{
    QString guard = m_exporter->namespaceName().toUpper();
    if(!guard.isEmpty())
        guard += QLatin1String("_");
    guard += classname.toUpper() + QLatin1String("_H\n");

    header.append(QLatin1String("#endif // ") + guard);
}

void Writer::writeInclude(const QString &className, QString &file) const
{
    file.append(QLatin1String("#include \"") + makeHeaderFilename(className) + QLatin1String("\"\n"));
}

QString Writer::makeHeaderFilename(const QString &classname) const
{
    return classname.toLower() + QLatin1String(".h");
}

QString Writer::makeSourceFilename(const QString &classname) const
{
    return classname.toLower() + QLatin1String(".cpp");
}

void Writer::writeToFile(const QString &fileName, const QString &content) const
{
    QFile file(m_exporter->directory() + fileName);
    if(!file.open(QFile::WriteOnly))
        return;

    QTextStream out(&file);
    out << content;
    file.close();
}

QString Writer::readFromFile(const QString &fileName) const
{
    QFile file(m_exporter->directory() + fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return QString();

    QString content;
    QTextStream in(&file);
    while (!in.atEnd()) {
        content += in.readLine()+"\n";
    }
    return content;
}

QString Writer::extractExtraContent(const QString &content) const
{
    int start = content.indexOf(ExtraContentBegin) + ExtraContentBegin.size();
    int length = content.indexOf(ExtraContentEnd) - start;

    if(start < 0 || length < 0)
        return QString();

    return content.mid(start, length);
}

void Writer::writeExtraContent(const QString &content, QString &file) const
{
    file.append(QLatin1String("\n"));
    file.append(ExtraContentBegin);
    file.append(content);
    file.append(ExtraContentEnd);
    file.append(QLatin1String("\n"));
}

} // namespace LBDatabase
