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
	return ui->txtCommandName->text().toLower().replace("1", "one").replace("2", "two").replace("3","three").replace("4","four")
			.replace("5", "five").replace("6", "six").replace("7", "seven").replace("8", "eight").replace("9", "nine").replace("0", "zero");
}

QString AddMethodDialog::Command()
{
    return ui->txtCommand->text();
}
