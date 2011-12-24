#include "itemmanager.h"
#include <QMutex>

ItemManager* ItemManager::m_instance = 0;

ItemManager::ItemManager() :
    QObject(0)
{
}

int ItemManager::AddItem(Chip * chip)
{
    items.append(chip);
    return items.count() - 1;
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

void ItemManager::SaveToFile()
{

}

void ItemManager::LoadToFile()
{

}
