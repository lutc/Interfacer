#include "itemmanager.h"
#include <QMutex>
#include <QFile>

#include "project.h"
#include "parser.h"

ItemManager* ItemManager::m_instance = 0;

ItemManager::ItemManager() :
    QObject(0)
{
}

int ItemManager::AddItem(CommonItemMECS * item)
{
    items.append(item);
    return items.count() - 1;
}

int ItemManager::AddItem(Page *page)
{
    pages.append(page);
    return pages.count() - 1;
}

ItemManager *ItemManager::Instance()
{
    static QMutex mutex;
    if (!m_instance)
    {
        mutex.lock();
        if (!m_instance)
            m_instance = new ItemManager;
        mutex.unlock();
    }
    return m_instance;
}

void ItemManager::GenerateInterface()
{
    Project::GenerateDevicesFile();
    QFile file("interface");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out.setCodec("Windows-1251");

    foreach (Page *page, pages)
    {
        out << page->Save();
    }

    foreach (CommonItemMECS *item, items) {
        if (!item->isRemoved())
            out << item->Save();
    }

    file.close();
}

void ItemManager::LoadFromFile()
{
    QStringList list = Parser::Parse("/home/lutc/MECS/projects/detsad/rootfs/interface", "[");
//    qDebug() << list;
    foreach (QString item, list) {
        int pos = 0;
        QRegExp rxType("^(\\w+)\\]");
        pos = rxType.indexIn(item, pos) + rxType.matchedLength();

        QString type = rxType.cap(1);
        if (type.compare("Page") == 0)
        {
            Page *page = new Page();
            page->Parse(item);
            AddItem(page);
        }
    }
}

QStringList ItemManager::GetPages()
{
    QStringList list;
    foreach(Page *page, pages)
    {
        list.append(page->GetName());
    }
    return list;
}
