#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "neuronnode.h"
#include "neurallayer.h"
#include "neuralnet.h"
#include <QDebug>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
        //Setup
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->installEventFilter(this);
    connect(ui->actionNew_Neuron,&QAction::triggered, this, &MainWindow::actionNewNode);
    connect(ui->actionNew_Layer ,&QAction::triggered, this, &MainWindow::actionNewLayer);
    connect(ui->actionNew_Net   ,&QAction::triggered, this, &MainWindow::actionNewNet);

    scene->addEllipse(0,0,1,1);// Reference point!
    scene->addEllipse(-500,-500,1,1); //Makes scene scrollable
    scene->addEllipse(500,500,1,1);
    scene->addEllipse(-500,500,1,1);
    scene->addEllipse(500,-500,1,1);

        //Test Zone
    NeuralLayer *layer1 = new NeuralLayer;
    NeuralLayer *layer2 = new NeuralLayer;
    NeuralLayer *layer3 = new NeuralLayer;
    NeuralLayer *layer4 = new NeuralLayer;

    NeuronNode *item1 = new NeuronNode;
    layer1->addNode(item1);
    layer1->addNode(new NeuronNode);
    layer2->addNode(new NeuronNode);
    layer3->addNode(new NeuronNode);
    layer3->addNode(new NeuronNode);
    layer3->addNode(new NeuronNode);
    layer3->addNode(new NeuronNode);
    layer4->addNode(new NeuronNode);

    NeuralNet *net1 = new NeuralNet();

    net1->addLayer(layer1);
    net1->connectLayer(layer2);
    net1->addLayer(layer2);

    drawLines(net1);
    //net1->addLayer(layer3);
    //net1->addLayer(layer4);

    net1->connectLayer(new NeuralLayer);
    scene->addItem(net1);

    //connectNetwork(net1); //TODO
    netList.append(net1);
}

MainWindow::~MainWindow() {
    delete ui;
}

    //works bad, to be replaced
void MainWindow::connectNetwork(NeuralNet *net){ // TODO have a better runtime // use a map?
    if(net->getList().size()>1){
        for(int i=0;i<net->getList().size()-1;i++){ //iterate through the layers x-wise
            for(int j=0;j<net->getList().value(i)->getList().length();j++){//get nodes in first layer
                for(int k=0;k<net->getList().value(i+1)->getList().length();k++){
                    QGraphicsItem *item = scene->addLine(
                         net->getList().value(i)->getList().at(j)->x()+i*(net->getWidth()/net->getList().size())+35,
                         net->getList().value(i)->getList().at(j)->y()+35,
                        (net->getList().value(i+1)->getList().at(k)->x())+(i+1)*(net->getWidth()/net->getList().size())+35,
                         net->getList().value(i+1)->getList().at(k)->y()+35);
                    net->addToGroup(item);}}}}}


void MainWindow::actionNewNode() { // only in where layer is selected
    NeuronNode *newNode = new NeuronNode();
    if (netList.contains(chosenItem) && chosenItem->getList().values().contains(chosenLayer)){ //should be a layer
        chosenLayer->addNode(newNode);
        chosenItem->resize(chosenLayer);
    }
    this->repaint();
}

void MainWindow::actionNewLayer() { // only when net is selected
    NeuralLayer *newLayer = new NeuralLayer;
    newLayer->addNode(new NeuronNode);
    if (netList.contains(chosenItem)){ //should be a net
        chosenItem->addLayer(newLayer);
    }
    repaint();
}

void MainWindow::actionNewNet() { //should work when nothing is selected
    NeuralNet *newNet = new NeuralNet();
    NeuralLayer *newLayer = new NeuralLayer;
    newLayer->addNode(new NeuronNode);
    newNet->addLayer(newLayer);
    netList.append(newNet);
    scene->addItem(newNet);
    repaint();
}

void MainWindow::actionDelete(){
    if(netList.contains(chosenItem)){
        if(chosenItem->getList().values().contains(chosenLayer)){
            if (chosenLayer->getList().contains(chosenNode)){ //should be a list
                scene->removeItem(chosenNode); //remove from scene
                chosenLayer->removeNode(chosenNode);
                if(chosenLayer->getList().size()==0){
                    scene->removeItem(chosenLayer); //remove from screen
                    chosenItem->removeLayer(chosenLayer); //remove from parent
                    if(chosenItem->getList().size()==0){ //could delete parent
                        scene->removeItem(chosenItem);
                        netList.removeOne(chosenItem);
                    }
                }
                else
                    chosenItem->resize();
                repaint();
            }
            //Layer
            else { //should be a list
                scene->removeItem(chosenLayer); //remove from screen
                chosenItem->removeLayer(chosenLayer); //remove from parent
                if(chosenItem->getList().size()==0){ //could delete parent
                    scene->removeItem(chosenItem);
                    netList.removeOne(chosenItem);
                }
                //this->connectNetwork(chosenItem); // TODO
            }
        }
        //Net
        else { //iff selected
            scene->removeItem(chosenItem); //remove from screen
            netList.removeOne(chosenItem); //remove from memory
        }
    }
}

//wip takes lines from a list and puts them on scene
void MainWindow::drawLines(NeuralNet *net) {
    //take the list of lines from the net and draw them
    QList<QLineF> linelist = net->getlinelist();
    for(int i=0;i<linelist.size();i++){
        QGraphicsItem *line = scene->addLine(linelist.at(i));
        net->addToGroup(line);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case 16777219:
        actionDelete();
        break;
    default:
        break;
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event){ //Event Handler
    bool isOnItem=false;
    if(event->type()==QEvent::GraphicsSceneMousePress){ // Mouse clicked
        const QGraphicsSceneMouseEvent* const me = static_cast<const QGraphicsSceneMouseEvent*>(event);
        const QPointF position = me->scenePos();
        for(int i=0;i<netList.size();i++){
            if(netList.at(i)->sceneBoundingRect().contains(position)){//Get net
                chosenItem = netList.at(i);
                isOnItem=true;
                for(int j=0;j<netList.at(i)->getList().size();j++){
                    if(netList.at(i)->getList().value(j)->sceneBoundingRect().contains(position)){//Get layer
                        chosenLayer = netList.at(i)->getList().value(j);
                        for(int k=0;k<netList.at(i)->getList().value(j)->getList().size();k++){
                            if(netList.at(i)->getList().value(j)->getList().at(k)->sceneBoundingRect().contains(position)){//Get node
                                chosenNode = netList.at(i)->getList().value(j)->getList().at(k);}}}}}}}
    if(event->type()==QEvent::GraphicsSceneMousePress && isOnItem==true){ // mouse clicked on item
        xstart = QCursor::pos().x();
        ystart = QCursor::pos().y();
    }
    if(event->type()==QEvent::GraphicsSceneMouseMove && chosenItem){//TODO can this be optimized?
        int xcurrent = QCursor::pos().x();
        int ycurrent = QCursor::pos().y();
        int xhere = chosenItem->scenePos().x();
        int yhere = chosenItem->scenePos().y();
        int xdiff = xstart - xcurrent;
        int ydiff = ystart - ycurrent;
        chosenItem->setPos(xhere-xdiff,yhere-ydiff);
        xstart = xcurrent;
        ystart = ycurrent;
        xcurrent = QCursor::pos().x();
        ycurrent = QCursor::pos().y();
    }
    return false;
}
