#include "parser.h"
#include <QTextStream>

Parser::Parser()
{

}

QStringList Parser::Parse(QString fileName, QString delimiter)
{
    QFile *inputFile = new QFile(fileName);
    inputFile->open(QFile::ReadOnly);
    QTextStream reader(inputFile);

    QString all = reader.readAll();
    inputFile->close();
    return all.split(delimiter, QString::SkipEmptyParts);
}
