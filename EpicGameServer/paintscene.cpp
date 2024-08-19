#include "paintscene.h"
#include <QDebug>

paintScene::paintScene()
{
    qpen.setWidth(5);
    qpen.setStyle(Qt::SolidLine);
}

void paintScene::setPenColor(const QColor &color)
{
    colorPixel = color;
    qpen.setColor(color); // Установить цвет ручки
}

void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    addEllipse(event -> scenePos().x() - 2,
               event -> scenePos().y() - 2,
               5,
               5,
               QPen(Qt::NoPen),
               QBrush(colorPixel));
    previousPoint = event -> scenePos();
}

void paintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    addLine(previousPoint.x(),
            previousPoint.y(),
            event -> scenePos().x(),
            event -> scenePos().y(),
            QPen(qpen));
    previousPoint = event -> scenePos();
}
