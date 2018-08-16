#ifndef NEURALLAYER_H
#define NEURALLAYER_H

#include <QObject>
#include <QGraphicsItem>

class NeuronNode;

class NeuralLayer : public QGraphicsItemGroup {

public:
    explicit NeuralLayer();
    ~NeuralLayer();
    QList<NeuronNode*> getList();
    QRectF boundingRect() const;
    void addNode(NeuronNode *node);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void removeNode(NeuronNode *chosenNode);

private:
    QList<NeuronNode*> m_list;
    int m_height;

};

#endif // NEURALLAYER_H
