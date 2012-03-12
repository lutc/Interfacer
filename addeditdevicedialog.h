#ifndef ADDEDITDEVICEDIALOG_H
#define ADDEDITDEVICEDIALOG_H

#include <QDialog>
#include <QGridLayout>

#include "lircdevice.h"
#include "comdevice.h"

namespace Ui {
class AddEditDeviceDialog;
}

class AddEditDeviceDialog : public QDialog
{
    Q_OBJECT

public:
    enum {Lirc, TcpIp, Com, Usb} types;

    explicit AddEditDeviceDialog(Device *);
    ~AddEditDeviceDialog();

private:
    Ui::AddEditDeviceDialog *ui;

    Device *m_device;

public slots:
    void onChangeCmbType(int);
    void onChangeCmbLircDevice(QString);
    void accept();
private slots:
    void on_btnAddMethod_clicked();
};

#endif // ADDEDITDEVICEDIALOG_H
