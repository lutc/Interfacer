#include "itemmanager.h"
#include <QMutex>
#include <QFile>
#include <QFileInfo>

ItemManager* ItemManager::m_instance = 0;

ItemManager::ItemManager() :
    QObject(0)
{
}

int ItemManager::AddItem(CommonItemMECS * chip)
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
    out.setCodec("Windows-1251");
// TODO Add pages manager
    QString prepend = "[Page]\n" \

            "Name = Main\n" \
            "Background = Images/aqua_back.png\n\n";
    out << prepend;
    foreach (CommonItemMECS *chip, items) {
        out << chip->Save();
    }

    QFileInfo *info = new QFileInfo(file);
    qDebug() << "Saved to file" << info->absoluteFilePath();
    file.close();
}

void ItemManager::LoadFromFile()
{

}
