#include "addeditdevicedialog.h"
#include "ui_addeditdevicedialog.h"
#include "project.h"
#include "lircdevice.h"

#include <QDebug>
AddEditDeviceDialog::AddEditDeviceDialog(Device *device) :
    QDialog(0),
    ui(new Ui::AddEditDeviceDialog),
    m_device(device)
{
    setModal(true);
    ui->setupUi(this);

    ui->cmbLircDevices->addItems(Project::GetLircDevices());

    connect(ui->cmbType, SIGNAL(currentIndexChanged(int)), this, SLOT(onChangeCmbType(int)));
    connect(ui->cmbLircDevices, SIGNAL(currentIndexChanged(QString)), this, SLOT(onChangeCmbLircDevice(QString)));
    onChangeCmbType(ui->cmbType->currentIndex());

}

AddEditDeviceDialog::~AddEditDeviceDialog()
{
    delete ui;
}

void AddEditDeviceDialog::onChangeCmbType(int type)
{
    ui->cmbLircDevices->setEnabled(AddEditDeviceDialog::Lirc == type);
    ui->lblLircDevices->setEnabled(AddEditDeviceDialog::Lirc == type);
    ui->txtName->setEnabled(AddEditDeviceDialog::Lirc != type);
    ui->lblName->setEnabled(AddEditDeviceDialog::Lirc != type);
    ui->btnAddMethod->setEnabled(AddEditDeviceDialog::Lirc != type);
    ui->btnRemoveMethod->setEnabled(AddEditDeviceDialog::Lirc != type);
}

void AddEditDeviceDialog::onChangeCmbLircDevice(QString deviceName)
{
    ui->lstMethods->clear();
    ui->lstMethods->addItems(Project::GetLircComands(deviceName));
    ui->txtName->setText(deviceName);
}

void AddEditDeviceDialog::accept()
{
    if (m_device == NULL)
    {
        switch (ui->cmbType->currentIndex())
        {
        case (AddEditDeviceDialog::Lirc):
            m_device = new LircDevice(ui->txtName->text(), Project::GetLirc(ui->txtName->text()));
            break;
        default:

            break;
        }
    }
    //TODO: Add device editing
    if (m_device != NULL)
        Project::AddDevice(m_device);
    QDialog::accept();
}
