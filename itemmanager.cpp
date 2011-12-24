#include "itemmanager.h"
#include <QMutex>
#include <QFile>

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
    QFile file("interface");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
// TODO Add pages manager
    QString prepend = "[Page]\n" \

            "Name = Main\n" \
            "Background = Images/aqua_back.png\n\n";
    out << prepend;
    foreach (Chip *chip, items) {
        out << chip->Save();
    }

    file.close();
}

void ItemManager::LoadToFile()
{

}
