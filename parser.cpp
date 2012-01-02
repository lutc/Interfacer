#include "parser.h"

Parser::Parser(QString fileName)
{
    QFile *inputFile = new QFile(fileName);
    inputFile->open(QFile::ReadOnly);

    inputFile->close();
}
