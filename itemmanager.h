#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include "chip.h"

class ItemManager : public QObject
{
    Q_OBJECT
public:
    static ItemManager *Instance();

    int AddItem(Chip *);

    void LoadFromFile();

signals:

public slots:
    void SaveToFile();

private:
    ItemManager();
    ItemManager(const ItemManager&);
    ItemManager& operator =(const ItemManager&);
    QVector<Chip *> items;
    static ItemManager* m_instance;

};

#endif // ITEMMANAGER_H
