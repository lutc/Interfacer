#ifndef ITEMACTION_H
#define ITEMACTION_H

#include <QObject>
#include <QHBoxLayout>
#include <QComboBox>

class ItemAction : public QObject
{
    Q_OBJECT
public:
    explicit ItemAction(QObject *parent = 0);
    void operator =(ItemAction &);
    QHBoxLayout *GetLayout();
    QString ToString();
    void Init(QString commandType, QString target, QString command);
signals:
    void OnChangeCommand(QString command);

public slots:

private:
    QComboBox *m_cmbTypeAction;
    QComboBox *m_cmbTargetAction;
    QComboBox *m_cmbAction;

    QString m_typeAction;
    QString m_targetAction;
    QString m_action;
    QStringList m_pagesList;

private slots:
    void onTypeActionChange(int);
    void onTargetActionChange(QString);
};

#endif // ITEMACTION_H
