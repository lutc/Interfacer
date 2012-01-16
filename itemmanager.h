#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include "commonitemmecs.h"
#include "page.h"

class ItemManager : public QObject
{
    Q_OBJECT
public:
    static ItemManager *Instance();

    int AddItem(CommonItemMECS *);
    int AddItem(Page *);

    QStringList GetPages();

signals:

public slots:
    void GenerateInterface();
    void LoadFromFile();

private:
    ItemManager();
    ItemManager(const ItemManager&);
    ItemManager& operator =(const ItemManager&);
    QVector<CommonItemMECS *> items;
    QVector<Page *> pages;
    static ItemManager* m_instance;

};

#endif // ITEMMANAGER_H
