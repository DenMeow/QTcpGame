#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class paintScene : public QGraphicsScene
{
    Q_OBJECT
public:
    paintScene();
    void setPenColor(const QColor &color);

private:
    QPointF previousPoint;

    // Для рисования используем события мыши
    void mousePressEvent (QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent (QGraphicsSceneMouseEvent *event);

    QPen qpen;
    QColor colorPixel;
};

#endif // PAINTSCENE_H
