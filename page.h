#ifndef PAGE_H
#define PAGE_H

#include <QGraphicsScene>
#include <QObject>

class Page : public QGraphicsScene
{
public:
    Page();
    QString Name();
    void SetName(QString);
    void setBackground(QString);
    QString Save();
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
