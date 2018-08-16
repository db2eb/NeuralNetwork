//#include "neuron.h"
//#include "ui_neuron.h"
//#include "neuronnode.h"
//#include "neurallayer.h"
//#include "neuralnet.h"
//#include <QDebug>
//#include <QGraphicsScene>
//#include <QGraphicsEllipseItem>
//#include <QObject>

//Neuron::Neuron(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::Neuron)
//{
//    ui->setupUi(this);
//    scene = new QGraphicsScene(this);
//    ui->graphicsView->setScene(scene);

//    QPen pen;
//    QPen dashpen(Qt::black);
//    dashpen.setStyle(Qt::DashDotLine);
//    QPen thickpen(Qt::black);
//    thickpen.setWidth(4);

//        //Test Zone
//    NeuronNode *item1 = new NeuronNode();
//    NeuronNode *item2 = new NeuronNode();
//    NeuronNode *item3 = new NeuronNode();
//    NeuronNode *item4 = new NeuronNode();
//    NeuronNode *item5 = new NeuronNode();
//    NeuronNode *item6 = new NeuronNode();

//    NeuralLayer *layer1 = new NeuralLayer(10,10); //takes in xy position and height
//    NeuralLayer *layer2 = new NeuralLayer(10,10); //takes in xy position and height
//    NeuralLayer *layer3 = new NeuralLayer(10,10); //takes in xy position and height

//    layer1->addNode(item1);
//    layer1->addNode(item2);
//    layer2->addNode(item3);
//    layer3->addNode(item4);
//    layer3->addNode(item5);
//    layer3->addNode(item6);

//    NeuralNet *net1 = new NeuralNet();
//    net1->addLayer(layer1);
//    net1->addLayer(layer2);
//    net1->addLayer(layer3);

//    scene->addItem(net1);
//    scene->addItem(layer1);
//    scene->addItem(item1);
//    scene->addItem(item2);
//    scene->addItem(layer2);
//    scene->addItem(item3);

//    scene->addItem(layer3);
//    scene->addItem(item4);
//    scene->addItem(item5);
//    scene->addItem(item6);

//    connectLines(layer1,layer2);
//    connectLines(layer2,layer3);

//}

//Neuron::~Neuron()
//{
//    delete ui;
//}

//void Neuron::drawLine(NeuronNode *thisNode,NeuronNode *thatNode){
//    QPen bigpen;
//    bigpen.setWidth(5);
//    scene->addLine(thisNode->x()+25,thisNode->y()+25,thatNode->x()+25,thatNode->y()+25,bigpen);
//}

//void Neuron::connectLines(NeuralLayer *fromThere,NeuralLayer *toHere){
//    for (int i=0;i<fromThere->getList().count();i++){
//        for (int j=0;j<toHere->getList().count();j++){
//            drawLine(fromThere->getList().at(i),toHere->getList().at(j));
//        }
//    }
//}
