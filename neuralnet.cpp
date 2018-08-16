#include "neuralnet.h"
#include "neurallayer.h"
#include "neuronnode.h"
#include <QPainter>
#include <QDebug>

NeuralNet::NeuralNet() : QGraphicsItemGroup() { // Make item group
    m_height = 0;
    m_width = 90*this->getList().size();
}

NeuralNet::~NeuralNet(){

}

void NeuralNet::addLayer(NeuralLayer *layer){
    if (layer->getList().length()>m_height)
        m_height = layer->getList().length();
    layer->setPos(this->scenePos().x()+10+(90*this->getList().size()), this->scenePos().y()+12); //move layer if increasing size

    //wip set pos for nodes
    for(int i=0;i<layer->getList().size();i++){
        layer->getList().at(i)->setX(/*this->scenePos().x()+10+*/(500*this->getList().size()));
        //layer->getList().at(i)->setY(this->scenePos().y()+12);
        qDebug()<<"net node position is"<<layer->getList().at(i)->getX()<<layer->getList().at(i)->getY();
    }
    //==============

    m_layers.insert(m_layers.size(),layer); // map key is order in list
    this->addToGroup(layer);
}

void NeuralNet::removeLayer(NeuralLayer *layer){ //neural net removes layer
    this->QGraphicsItem::prepareGeometryChange();
    m_height = 0;
    QMap<int,NeuralLayer*> tempMap; //temporary map, insert everything except todelete
    for(int i=0;i<m_layers.size();i++){
        if (m_layers.value(i)!=layer){
            if (m_layers.value(i)->getList().length()>m_height){
                m_height = m_layers.value(i)->getList().length();
            }
            tempMap.insert(tempMap.size(),m_layers.value(i));
            m_layers.value(i)->setPos(90*tempMap.size()-80,15); //reposition
        }
    }
    m_layers = tempMap;
}

void NeuralNet::resize(NeuralLayer *layer){ // resize for insertion
    if (layer->getList().length()>m_height)
        m_height = layer->getList().length();
}

void NeuralNet::resize(){
    m_height = 0;
    for(int i=0;i<this->getList().size();i++){
        if (this->getList().value(i)->getList().length()>m_height)
            m_height = this->getList().value(i)->getList().length();
    }
}

QMap<int,NeuralLayer*> NeuralNet::getList(){
    return this->m_layers;
}

QList<QLineF> NeuralNet::getlinelist()
{
    return m_linelist;
}

int NeuralNet::getWidth() {
    return 90*this->getList().size();
}

QRectF NeuralNet::boundingRect() const {
    return QRectF(10,10,m_width,90*m_height);
}

void NeuralNet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                      QWidget *widget) {
    painter->setBrush(QColor(255,0,0,10));
    m_width = 90*this->getList().size();
    painter->drawRect(10,10,m_width,90*m_height);
}


//wip
//void NeuralNet::connectLayer(NeuralLayer *layer) {
//    NeuralLayer *first = this->getList().value(this->getList().size()-1);
//    for(int i=0;i<first->getList().size();i++){
//        for(int j=0;j<layer->getList().size();j++){//make lines and put into list/map
//            qDebug()<<first->getList().at(i)->getX();
//            qDebug()<<first->getList().at(i)->getY();
//            qDebug()<<layer->getList().at(j)->getX();
//            qDebug()<<layer->getList().at(j)->getY();
//            QLineF line = QLineF(first->getList().at(i)->getX(),
//                                 first->getList().at(i)->getY(),
//                                 layer->getList().at(j)->getX(),
//                                 layer->getList().at(j)->getY());
//            m_linelist.append(line);
//        }// problem is nodes are not different in position
//    }
//}

// wip
void NeuralNet::connectLayer(NeuralLayer *layer){ //Copied the same from the mainwindow
    if(this->getList().size()>1){
        NeuralLayer *first = this->getList().value(this->getList().size()-1);
        for(int j=0;j<first->getList().length();j++){//get nodes in first layer
            for(int k=0;k<layer->getList().length();k++){
                QLineF line = QLineF(first->getList().at(j)->x()+(this->getWidth()/this->getList().size())+35,
                     first->getList().at(j)->y()+35,
                    (layer->getList().at(k)->x())*(this->getWidth()/this->getList().size())+35,
                     layer->getList().at(k)->y()+35);
                m_linelist.append(line);
            }
        }
    }
}









