#include "neurallayer.h"
#include "neuronnode.h"
#include <QPainter>
#include <QDebug>

NeuralLayer::NeuralLayer() : QGraphicsItemGroup() {
    m_height = 0;
}

NeuralLayer::~NeuralLayer(){

}

void NeuralLayer::addNode(NeuronNode *node){
    this->addToGroup(node);
    node->setPos(20,30+(90*this->getList().length()));

    //wip. adjust absolute centers of nodes, not good idea
    node->setX(20);
    node->setY(30+(90*this->getList().length()));
    qDebug()<<"layer node position is"<<node->getX()<<node->getY();

    m_list.append(node);
}

void NeuralLayer::removeNode(NeuronNode *chosenNode){
    QList<NeuronNode*> tempList;
    m_list.removeOne(chosenNode);
    for(int i=0;i<m_list.size();i++){
        tempList.append(m_list.at(i));
        m_list.at(i)->setPos(20,30+(90*(tempList.size()-1)));
    }
    m_list = tempList;
}

QList<NeuronNode*> NeuralLayer::getList(){
    return this->m_list;
}

QRectF NeuralLayer::boundingRect() const {
    return QRectF(10,10,70,m_height);
}

void NeuralLayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                        QWidget *widget) {
    painter->setPen(Qt::DashDotLine);
    painter->setBrush(QColor(255,255,0,100));
    m_height = 85*m_list.size();
    painter->drawRect(10,10,70,85*m_list.size());
}
