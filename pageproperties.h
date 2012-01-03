#ifndef PAGEPROPERTIES_H
#define PAGEPROPERTIES_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>

#include "page.h"
class PageProperties : public QDialog
{
    Q_OBJECT
public:
    explicit PageProperties(Page *m_item);

signals:

public slots:
    void accept();

private:
    Page *m_item;

    QLineEdit *m_txtName;
    QComboBox *m_cmbBackgroundImage;

};

#endif // PAGEPROPERTIES_H
