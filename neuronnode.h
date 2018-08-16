#ifndef NEURONNODE_H
#define NEURONNODE_H

#include <QObject>
#include <QGraphicsItem>

class NeuronNode : public QGraphicsEllipseItem {

public:
    explicit NeuronNode();
    ~NeuronNode();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QColor m_color;
    QPointF getPos();
    int xpos,ypos;
    void setX(int i);
    void setY(int i);
    int getX();
    int getY();

private:
    QList<QLine*> node_lines;

};

#endif // NEURONNODE_H
