#ifndef PARSER_H
#define PARSER_H

#include <QFile>
#include <QStringList>

class Parser
{
public:
    Parser();
    static QStringList Parse(QString fileName, QString delimiter);
};

#endif // PARSER_H
