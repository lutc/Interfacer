#include <QTextStream>
#include "project.h"
#include "parser.h"
#include <QDebug>
#include "pjlinkdevice.h"
#include "itemmanager.h"

#include "comdevice.h"
#include "textmesc.h"
#include "buttonmecs.h"
#include "togglebuttonmecs.h"

QString Project::PathToProject;
const QString Project::m_LircdConfPath = "etc/lirc/lircd.conf";

const QString Project::ImagesDirectory = QString("Images");
const QString Project::ControllerDirectory = QString("/controller");
QMap<QString, Lirc *> Project::m_lircConfiges;
QMap<QString, Device*> Project::m_devices;

Project* Project::m_instance = 0;

Project::Project()
{
}


QStringList Project::GetImages()
{
    QDir *dir = new QDir(Project::PathToProject + Project::ImagesDirectory);

    // TODO throw exception
    //if (!dir->exists())
    //    throw ;
//    dir->setFilter(QDir::NoDot | QDir::NoDotDot);
    QStringList list = dir->entryList();
    list.removeFirst();
    list.removeFirst();
    return list;
}

QStringList Project::GetLircComands(QString name)
{
    if (m_lircConfiges.isEmpty())
        Project::updateLircConfiges();

    if (Project::m_lircConfiges.contains(name))
    {
        return Project::m_lircConfiges.value(name)->GetCommands();
    }
    return QStringList();
}

QStringList Project::GetLircDevices()
{
    if (m_lircConfiges.isEmpty())
        Project::updateLircConfiges();
    return QStringList(m_lircConfiges.keys());
}

Lirc *Project::GetLirc(QString name)
{
    if (m_lircConfiges.isEmpty())
        Project::updateLircConfiges();

    if (Project::m_lircConfiges.contains(name))
    {
        return Project::m_lircConfiges.value(name);
    }
    return NULL;
}

void Project::updateLircConfiges()
{
    QStringList list = Parser::Parse(Project::LircdConfPath(), Lirc::CommandSeparator);

    foreach (QString rawString, list)
    {
//        QString rawString = list.last();
        Lirc *lirc = new Lirc();
        lirc->Parse(rawString);
        m_lircConfiges[lirc->Name()] = lirc;
    }
}

void Project::generateDeviceFile(Device *device)
{    
    QFile file(Project::PathToDevices()  + device->GetFileName());
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
//    out.setCodec("Windows-1251");
    out << device->Save();
    file.close();
}

void Project::AddDevice(Device *device)
{
    m_devices.insert(device->GetName(), device);
    emit DevicesUpdated(Project::GetDevices());
}


QStringList Project::GetDevices()
{
    if (m_devices.isEmpty())
        return QStringList();

    return QStringList(m_devices.keys());
}

Device *Project::GetDevice(QString deviceName)
{
    return m_devices[deviceName];
}

QStringList Project::GetDeviceCommands(QString deviceName)
{
    if (m_devices.contains(deviceName))
        return m_devices[deviceName]->GetCommands();
    return QStringList();
}

void Project::GenerateDevicesFile()
{
	QFile file(Project::PathToProject + "protocols all");
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream out(&file);
//    out.setCodec("Windows-1251");

    foreach (Device *device, m_devices) {
        generateDeviceFile(device);
		out << "controller/" + device->GetFileName() << endl;
    }
	file.close();
}


Project *Project::Instance()
{
    static QMutex mutex;
    if (!m_instance)
    {
        mutex.lock();
        if (!m_instance)
            m_instance = new Project;
        mutex.unlock();
    }
    return m_instance;
}

bool Project::ParseInterface()
{
    QString rawData = readFile(Project::PathToProject + "/interface");

    int i = 0;


    QRegExp rawType("\\[(\\w+)\\]");

    while ((i = rawType.indexIn(rawData, i)) >= 0)
    {
        i += rawType.matchedLength();
        QString type = rawType.cap(1);

        if (type.compare("Page") == 0)
        {
            QRegExp rawName("Name = (\\w+)");
            rawName.indexIn(rawData, i);
            QString name= rawName.cap(1);


            QRegExp rawBackground("Background = (\\w+.)/(\\w+)\\.(\\w+)");
            rawBackground.indexIn(rawData, i);
            QString background= rawBackground.cap(1) + "/" + rawBackground.cap(2) + "." + rawBackground.cap(3);

            ItemManager::Instance()->AddItem(new Page(name, background));

        }
        else if (type.compare("Text") == 0)
        {
            /*
[Text]
Align = left
Pages = Extron
Left = 250
Top = 25
Font = Images/arial.ttf
FontSize = 20
Color = white
Width = 200
Height = 50
DefaultText = Extron
              */
            QRegExp rawAlign("Align = (\\w+)");
            rawAlign.indexIn(rawData, i);
            QString Align= rawAlign.cap(1);

            QRegExp rawPages("Pages = (\\w+)");
            rawPages.indexIn(rawData, i);
            QString Pages= rawPages.cap(1);

            QRegExp rawLeft("Left = (\\d+)");
            rawLeft.indexIn(rawData, i);
            QString Left= rawLeft.cap(1);

            QRegExp rawTop("Top = (\\d+)");
            rawTop.indexIn(rawData, i);
            QString Top= rawTop.cap(1);

            QRegExp rawFontSize("FontSize = (\\d+)");
            rawFontSize.indexIn(rawData, i);
            QString FontSize= rawFontSize.cap(1);

            QRegExp rawWidth("Width = (\\d+)");
            rawWidth.indexIn(rawData, i);
            QString Width= rawWidth.cap(1);

            QRegExp rawHeight("Height = (\\d+)");
            rawHeight.indexIn(rawData, i);
            QString Height= rawHeight.cap(1);

            QRegExp rawFont("Font = (\\w+)/(\\w+)\\.(\\w+)");
            rawFont.indexIn(rawData, i);
            QString Font= rawFont.cap(1) + "/" + rawFont.cap(2) + "." + rawFont.cap(3);

            QRegExp rawColor("Color = (\\w+)");
            rawColor.indexIn(rawData, i);
            QString Color= rawColor.cap(1);

            QRegExp rawDefaultText("DefaultText = (\\w+)");
            rawDefaultText.indexIn(rawData, i);
            QString DefaultText= rawDefaultText.cap(1);

            TextMESC *text = new TextMESC(Left.toInt(), Top.toInt());
            text->setWidth(Width.toInt());
            text->setHeight(Height.toInt());
            text->setText(DefaultText);
            text->setPage(Pages);
            ItemManager::Instance()->AddItem(text);
        }
        else if (type.compare("Button") == 0)
        {

//            [Button]
//            Caption = Включить
//            Pages = Projectors
//            Left = 25
//            Top = 150
//            Font = Images/arial.ttf
//            FontSize = 20
//            Color = white
//            UpImage = Images/menu_btn.png
//            DownImage = Images/menu_light_btn.png
//            HeldImage = Images/menu_light_btn.png
//            OnClick  = Command Mitsubishil poweron

            QRegExp rawUpImage("UpImage = (\\w+.)/(\\w+)\\.(\\w+)");
            rawUpImage.indexIn(rawData, i);
            QString UpImage= rawUpImage.cap(1) + "/" + rawUpImage.cap(2) + "." + rawUpImage.cap(3);


            QRegExp rawDownImage("DownImage = (\\w+.)/(\\w+)\\.(\\w+)");
            rawDownImage.indexIn(rawData, i);
            QString DownImage= rawDownImage.cap(1) + "/" + rawDownImage.cap(2) + "." + rawDownImage.cap(3);

            QRegExp rawHeldImage("HeldImage = (\\w+.)/(\\w+)\\.(\\w+)");
            rawHeldImage.indexIn(rawData, i);
            QString HeldImage= rawHeldImage.cap(1) + "/" + rawHeldImage.cap(2) + "." + rawHeldImage.cap(3);

			QRegExp rawOnClick("OnClick\\s*=\\s*(\\w+)\\s*(\\w+)([ \\w]*)");
            rawOnClick.indexIn(rawData, i);
			QString commandType = rawOnClick.cap(1).trimmed();
			QString target = rawOnClick.cap(2).trimmed();
			QString command = rawOnClick.cap(3).trimmed();

            QRegExp rawLeft("Left = (\\d+)");
            rawLeft.indexIn(rawData, i);
            QString Left= rawLeft.cap(1);

            QRegExp rawTop("Top = (\\d+)");
            rawTop.indexIn(rawData, i);
            QString Top= rawTop.cap(1);

			QRegExp rawCaption("Caption = ([\\w \\+-]+)");
            rawCaption.indexIn(rawData, i);
            QString Caption= rawCaption.cap(1);

            QRegExp rawPages("Pages = (\\w+)");
            rawPages.indexIn(rawData, i);
            QString Pages= rawPages.cap(1);

            QRegExp rawFont("Font = (\\w+)/(\\w+)\\.(\\w+)");
            rawFont.indexIn(rawData, i);
            QString Font= rawFont.cap(1) + "/" + rawFont.cap(2) + "." + rawFont.cap(3);


            QRegExp rawColor("Color = (\\w+)");
            rawColor.indexIn(rawData, i);
            QString Color= rawColor.cap(1);

            QRegExp rawFontSize("FontSize = (\\d+)");
            rawFontSize.indexIn(rawData, i);
            QString FontSize= rawFontSize.cap(1);

            ButtonMECS *button = new ButtonMECS(Left.toInt(), Top.toInt());
            button->setText(Caption);
            button->setBackgroundImage(UpImage);
            button->SetDownImage(DownImage);
            button->SetHeldImage(HeldImage);
            button->SetOnClickAction(commandType, target, command);
            button->setPage(Pages);            
            ItemManager::Instance()->AddItem(button);

        }
        else if (type.compare("ToggleButton") == 0)
        {

//            [ToggleButton]
//            Caption = MuteL
//            Pages = Main
//            Left = 25
//            Top = 400
//            Font = Images/arial.ttf
//            FontSize = 20
//            Color = white
//            UpImage = Images/menu_btn.png
//            DownImage = Images/menu_light_btn.png
//            HeldImage = Images/menu_light_btn.png


//            OnDown = Command Mitsubishil muteon
//            OnUp = Command Mitsubishil muteoff

            QRegExp rawUpImage("UpImage = (\\w+.)/(\\w+)\\.(\\w+)");
            rawUpImage.indexIn(rawData, i);
            QString UpImage= rawUpImage.cap(1) + "/" + rawUpImage.cap(2) + "." + rawUpImage.cap(3);


            QRegExp rawDownImage("DownImage = (\\w+.)/(\\w+)\\.(\\w+)");
            rawDownImage.indexIn(rawData, i);
            QString DownImage= rawDownImage.cap(1) + "/" + rawDownImage.cap(2) + "." + rawDownImage.cap(3);

            QRegExp rawHeldImage("HeldImage = (\\w+.)/(\\w+)\\.(\\w+)");
            rawHeldImage.indexIn(rawData, i);
            QString HeldImage= rawHeldImage.cap(1) + "/" + rawHeldImage.cap(2) + "." + rawHeldImage.cap(3);

			QRegExp rawOnDown("OnDown\\s*=\\s*(\\w+)\\s*(\\w+)([ \\w]*)");
            rawOnDown.indexIn(rawData, i);
			QString commandTypeDown = rawOnDown.cap(1).trimmed();
			QString targetDown = rawOnDown.cap(2).trimmed();
			QString commandDown = rawOnDown.cap(3).trimmed();

			QRegExp rawOnUp("OnUp\\s*=\\s*(\\w+)\\s*(\\w+)([ \\w]*)");
            rawOnUp.indexIn(rawData, i);
			QString commandTypeUp = rawOnUp.cap(1).trimmed();
			QString targetUp = rawOnUp.cap(2).trimmed();
			QString commandUp = rawOnUp.cap(3).trimmed();

            QRegExp rawLeft("Left = (\\d+)");
            rawLeft.indexIn(rawData, i);
            QString Left= rawLeft.cap(1);

            QRegExp rawTop("Top = (\\d+)");
            rawTop.indexIn(rawData, i);
            QString Top= rawTop.cap(1);

			QRegExp rawCaption("Caption = ([\\w ]+)");
            rawCaption.indexIn(rawData, i);
            QString Caption= rawCaption.cap(1);

            QRegExp rawPages("Pages = (\\w+)");
            rawPages.indexIn(rawData, i);
            QString Pages= rawPages.cap(1);

            QRegExp rawFont("Font = (\\w+)/(\\w+)\\.(\\w+)");
            rawFont.indexIn(rawData, i);
            QString Font= rawFont.cap(1) + "/" + rawFont.cap(2) + "." + rawFont.cap(3);


            QRegExp rawColor("Color = (\\w+)");
            rawColor.indexIn(rawData, i);
            QString Color= rawColor.cap(1);

            QRegExp rawFontSize("FontSize = (\\d+)");
            rawFontSize.indexIn(rawData, i);
            QString FontSize= rawFontSize.cap(1);

            ToggleButtonMECS *button = new ToggleButtonMECS(Left.toInt(), Top.toInt());
            button->setText(Caption);
            button->setBackgroundImage(UpImage);
            button->SetDownImage(DownImage);
            button->SetHeldImage(HeldImage);
			button->SetOnUpAction(commandTypeUp, targetUp, commandUp);
			button->SetOnDownAction(commandTypeDown, targetDown, commandDown);
            button->setPage(Pages);
            ItemManager::Instance()->AddItem(button);
        }
    }

    return true;
}

void Project::ParseAllDevicesFromProjectRoot()
{
    QDir dir(Project::PathToProject + "controller/");
    QStringList filter;
    filter  << "*.pjlink" << "*.rj45" << "*.rs232" << "*.lirc";
    QFileInfoList dirContent = dir.entryInfoList(filter, QDir::Files | QDir::NoDotAndDotDot);


    foreach (QFileInfo info, dirContent)
    {
		qDebug() << info.filePath();
        Project::Instance()->ParseDevice(info.filePath());
    }
}

QString Project::readFile(QString filename)
{
    QFile file(filename);

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream inStream(&file);
    inStream.setCodec("Windows-1251");
    QString rawData = inStream.readAll();
    file.close();
    return rawData;
}

bool Project::ParseDevice(QString filename)
{

    QString rawData = readFile(filename);
    QFileInfo info(filename);
    if (!rawData.startsWith("protocol"))
        return false;

    QRegExp rawType("protocol (\\w+): (\\w+)");
    rawType.indexIn(rawData, 0);
    Device *parsedDevice;
    QString type = rawType.cap(2);
    QString name = rawType.cap(1);

    if ((type.compare("com") == 0) || (type.compare("usb") == 0))
    {
        QRegExp rawPort("port: (0|1)");
        rawPort.indexIn(rawData, 0);
        QString port = rawPort.cap(1);

        QRegExp rawSpeed("speed: (\\d+)");
        rawSpeed.indexIn(rawData, 0);
        QString speed = rawSpeed.cap(1);

        QRegExp rawcharacterSize("character-size: (\\d+)");
        rawcharacterSize.indexIn(rawData, 0);
        QString characterSize = rawcharacterSize.cap(1);

        QRegExp rawParity("parity: (none|.+\r\n)");
        rawParity.indexIn(rawData, 0);
        QString parity = rawParity.cap(1);

        parsedDevice = new ComDevice(name, port, speed, parity, characterSize);

        int i = 0;
        QRegExp rawMethod("command (\\w+)\n\\{\n\\s+send \\w+ \\(([^\n]+)\\)");
        while ((i = rawMethod.indexIn(rawData, i)) > 0)
        {
            i += rawMethod.matchedLength();

            parsedDevice->addCommand(rawMethod.cap(1), rawMethod.cap(2));
        }        
    }
    else if (type.compare("tcp") == 0)
    {
        QRegExp rawTargetIp("target-ip: \"([\\d|\\.]+)\\:(\\d+)");
        rawTargetIp.indexIn(rawData, 0);

        QString targetIp = rawTargetIp.cap(1);
        QString targetPort = rawTargetIp.cap(2);

        parsedDevice = new PJLinkDevice(name, targetIp, targetPort);

        int i = 0;
        QRegExp rawMethod("command (\\w+)\n\\{\n\\s+send \\w+ \\(([^\n]+)\\)");
        while ((i = rawMethod.indexIn(rawData, i)) > 0)
        {
            i += rawMethod.matchedLength();

            parsedDevice->addCommand(rawMethod.cap(1), rawMethod.cap(2));
        }

    }
    parsedDevice->SetProtocolName(info.completeSuffix());
    this->AddDevice(parsedDevice);
    return true;
}
