#include "itemmanager.h"
#include <QMutex>
#include <QFile>
#include <QGraphicsView>

#include "project.h"
#include "parser.h"

ItemManager* ItemManager::m_instance = 0;

ItemManager::ItemManager() :
    QObject(0)
{
    m_tabWidget = 0;
}

int ItemManager::AddItem(CommonItemMECS * item)
{
    m_items.append(item);
    return m_items.count() - 1;
}

int ItemManager::AddItem(Page *page)
{
    m_pages[page->GetName()] = page;
    return m_pages.count() - 1;
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
    QFile file(Project::PathToProject + "interface");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out.setCodec("Windows-1251");

    foreach (Page *page, m_pages.values())
    {
        out << page->Save();
    }

    foreach (CommonItemMECS *item, m_items) {
        if (!item->isRemoved())
            out << item->Save();
    }

    file.close();
}

void ItemManager::LoadFromFile()
{

}

void ItemManager::RefreshTabWidget()
{
    if (m_tabWidget == 0)
        return;

    //TODO clean m_tabWidget;
    while (m_tabWidget->count() > 0)
    {
        m_tabWidget->removeTab(0);
    }

    foreach(Page *page, m_pages)
    {
        QGraphicsView *graphicsView = Page::GenerateGraphicsView();
        graphicsView->setScene(page);        

        m_tabWidget->setUpdatesEnabled(false);
        m_tabWidget->addTab(graphicsView, page->GetName());

        m_tabWidget->setUpdatesEnabled(true);
        page->UpdateBackground();

    }
    foreach (CommonItemMECS *item, m_items)
    {
        if (item->getPage().isEmpty() && !m_pages.contains(item->getPage()))
        {
            QGraphicsView *graphicsView = qobject_cast<QGraphicsView *>(m_tabWidget->currentWidget());
            graphicsView->scene()->addItem(item);
        }
        else
            m_pages[item->getPage()]->addItem(item);
        item->UpdatePosition();
    }


}

QStringList ItemManager::GetPages()
{
    QStringList list;
    foreach(Page *page, m_pages)
    {
        list.append(page->GetName());
    }
    return list;
}

void ItemManager::SetTabWidget(QTabWidget *widget)
{
    m_tabWidget = widget;
}
