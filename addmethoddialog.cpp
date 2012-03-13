#include "addmethoddialog.h"
#include "ui_addmethoddialog.h"

AddMethodDialog::AddMethodDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMethodDialog)
{
    ui->setupUi(this);
}

AddMethodDialog::~AddMethodDialog()
{
    delete ui;
}

QString AddMethodDialog::CommandName()
{
    return ui->txtCommandName->text();
}

QString AddMethodDialog::Command()
{
    return ui->txtCommand->text();
}
