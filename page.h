#ifndef PAGE_H
#define PAGE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>

class Page : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(QString Name READ GetName WRITE SetName)
    Q_PROPERTY(QString Background READ GetBackground WRITE SetBackground)
public:

    Page();
    Page(QString Name, QString Background);
    QString GetName();
    void UpdateBackground();
    void SetName(QString);
    void SetBackground(QString);
    QString GetBackground() {return m_background;}
    QString Save();
    void Refresh();
    QPointF GetNewPosition(){ return m_newPos; }

    static QGraphicsView *GenerateGraphicsView();
protected:
	void drawBackground(QPainter *painter, const QRectF & rect);

private:
    QString m_background;
    QImage *m_backgroundImage;
    QString m_name;
    QPointF m_newPos;

public slots:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void nameChanged(QString);
};

#endif // PAGE_H
