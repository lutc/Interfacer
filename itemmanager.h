#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <QObject>
#include <QVector>
#include <QMap>
#include <QTabWidget>
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
    void SetTabWidget(QTabWidget * widget);
    void RefreshTabWidget();

signals:

public slots:
    void GenerateInterface();
    void LoadFromFile();

private:
    ItemManager();
    ItemManager(const ItemManager&);
    ItemManager& operator =(const ItemManager&);
    QVector<CommonItemMECS *> m_items;
    QMap<QString, Page *> m_pages;
    static ItemManager* m_instance;
    QTabWidget *m_tabWidget;

};

#endif // ITEMMANAGER_H
