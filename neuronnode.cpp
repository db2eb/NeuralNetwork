#include "neuronnode.h"
#include <QPainter>
#include <QDebug>
NeuronNode::NeuronNode() : QGraphicsEllipseItem() {
    m_color = QColor(0,0,255,100);
    xpos=0;
    ypos=0;
}

NeuronNode::~NeuronNode(){

}

QRectF NeuronNode::boundingRect() const {
    return QRectF(0,0,50,50);
}

void NeuronNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget) {
    painter->setBrush(m_color);
    painter->drawEllipse(0,0,50,50);
}


// Everything here is wip. tried to get absolute position of the centers for lines
QPointF NeuronNode::getPos() {
    //qDebug()<<"start node position is"<<xpos<<ypos;
    return this->pos();
}

void NeuronNode::setX(int i){
    this->xpos = xpos + i;
}

void NeuronNode::setY(int i){
    this->ypos = ypos + i;
}

int NeuronNode::getX() {
    return this->xpos+35; //centered
}

int NeuronNode::getY() {
    return this->ypos+35;
}





