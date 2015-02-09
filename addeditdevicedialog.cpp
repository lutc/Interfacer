#include "addeditdevicedialog.h"
#include "ui_addeditdevicedialog.h"
#include "project.h"
#include "lircdevice.h"
#include "comdevice.h"
#include "pjlinkdevice.h"
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
    ui->lstMethods->clear();
    ui->txtName->clear();
    bool enabledLircControls = AddEditDeviceDialog::Lirc == type;
    bool enabledComControls = type == AddEditDeviceDialog::Com;

    bool enabledPJLinkControls = type == AddEditDeviceDialog::PJLink;
    bool enabledTcpControls = type == AddEditDeviceDialog::TcpIp;

    ui->cmbLircDevices->setVisible(enabledLircControls);
    ui->lblLircDevices->setVisible(enabledLircControls);
    ui->txtName->setEnabled(!enabledLircControls);
    ui->lblName->setEnabled(!enabledLircControls);
    ui->lstMethods->setVisible(enabledLircControls);
    ui->lblMethods->setVisible(enabledLircControls);

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

    ui->lblIp->setVisible(enabledPJLinkControls || enabledTcpControls);
    ui->frmIp->setVisible(enabledPJLinkControls || enabledTcpControls);

    ui->lblPortTcp->setVisible(enabledTcpControls);
    ui->spnPortTcp->setVisible(enabledTcpControls);
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
            m_device = new ComDevice(ui->txtName->text(), ui->cmbPort->currentText(), ui->cmbSpeed->currentText(), ui->cmbParity->currentText() );
            break;

        default:

            QString separatorIp(".");
            QString ip = ui->spnIp0->text().append(separatorIp).append(ui->spnIp1->text()).append(separatorIp).
                    append(ui->spnIp2->text()).append(separatorIp).append(ui->spnIp3->text());			
            if (ui->cmbType->currentIndex() == AddEditDeviceDialog::PJLink)
                m_device = new PJLinkDevice(ui->txtName->text(), ip);
            else
                m_device = new PJLinkDevice(ui->txtName->text(), ip, ui->spnPortTcp->text());

            break;
        }
    }
    m_device->SetProtocolName(ui->txtDeviceName->text());

    //TODO: Add device editing
    if (m_device != NULL)
        Project::Instance()->AddDevice(m_device);
    QDialog::accept();
}
