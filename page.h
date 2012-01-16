#ifndef PAGE_H
#define PAGE_H

#include <QGraphicsScene>
#include <QObject>

class Page : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(QString Name READ GetName WRITE SetName)
    Q_PROPERTY(QString Background READ GetBackground WRITE SetBackground)
public:

    Page();
    QString GetName();
    void SetName(QString);
    void SetBackground(QString);
    QString GetBackground() {return m_background;}
    QString Save();
    void Parse(QString from);
protected:
    void drawBackground(QPainter *painter, const QRectF &);

private:
    QString m_background;
    QImage *m_backgroundImage;
    QString m_name;

public slots:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
signals:
    void nameChanged(QString);
};

#endif // PAGE_H
