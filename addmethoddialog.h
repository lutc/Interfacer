#ifndef ADDMETHODDIALOG_H
#define ADDMETHODDIALOG_H

#include <QDialog>

namespace Ui {
class AddMethodDialog;
}

class AddMethodDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddMethodDialog(QWidget *parent = 0);
    ~AddMethodDialog();

    QString CommandName();
    QString Command();
    
private:
    Ui::AddMethodDialog *ui;
};

#endif // ADDMETHODDIALOG_H
