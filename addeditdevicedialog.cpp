#include "addeditdevicedialog.h"
#include "ui_addeditdevicedialog.h"
#include "project.h"
#include "lircdevice.h"
#include "comdevice.h"

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
    bool enabledLircControls = AddEditDeviceDialog::Lirc == type;
    bool enabledComControls = type == AddEditDeviceDialog::Com;

    ui->cmbLircDevices->setVisible(enabledLircControls);
    ui->lblLircDevices->setVisible(enabledLircControls);
    ui->txtName->setEnabled(!enabledLircControls);
    ui->lblName->setEnabled(!enabledLircControls);
    ui->btnAddMethod->setEnabled(!enabledLircControls);
    ui->btnRemoveMethod->setEnabled(!enabledLircControls);
    ui->horizontalLayout->setEnabled(enabledLircControls);

    ui->lblParity->setVisible(enabledComControls);
    ui->cmbParity->setVisible(enabledComControls);
    ui->lblCaseSens->setVisible(enabledComControls);
    ui->chkCaseSens->setVisible(enabledComControls);

    ui->lblSpeed->setVisible(enabledComControls);
    ui->cmbSpeed->setVisible(enabledComControls);
    ui->lblTimeout->setVisible(enabledComControls);
    ui->txtTimeout->setVisible(enabledComControls);
    ui->lblQueryPeriod->setVisible(enabledComControls);
    ui->txtQueryPeriod->setVisible(enabledComControls);
    ui->lblPort->setVisible(enabledComControls);
    ui->cmbPort->setVisible(enabledComControls);
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

        case (AddEditDeviceDialog::Com):
            m_device = new ComDevice(ui->txtName->text());
        default:

            break;
        }
    }
    m_device->SetDeviceName(ui->txtDeviceName->text());

    //TODO: Add device editing
    if (m_device != NULL)
        Project::AddDevice(m_device);
    QDialog::accept();
}
