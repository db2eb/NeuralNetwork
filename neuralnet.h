#ifndef NEURALNET_H
#define NEURALNET_H

#include <QObject>
#include <QGraphicsItem>

class NeuralLayer;

class NeuralNet : public QGraphicsItemGroup {

public:
    explicit NeuralNet();
    ~NeuralNet();
    int getWidth();
    void resize(NeuralLayer *layer);
    void resize();
    void addLayer(NeuralLayer *layer);
    void removeLayer(NeuralLayer *layer);
    QMap<int,NeuralLayer*> getList();
    QList<QLineF> getlinelist();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    void connectLayer(NeuralLayer *layer);

private:
    QList<NeuralLayer*> m_list;
    QList<QLineF> m_linelist;
    QMap<int,NeuralLayer*> m_layers;
    int m_height, m_width;

};

#endif // NEURALNET_H
