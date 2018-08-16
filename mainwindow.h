#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsItem>

class NeuronNode;
class NeuralLayer;
class NeuralNet;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void connectNetwork(NeuralNet *net);
    void actionNewNode();
    void actionNewLayer();
    void actionNewNet();
    void actionDelete();
    //void actionDeleteLayer();
    //void actionDeleteNet();
    void drawLines(NeuralNet *net);
    void keyPressEvent(QKeyEvent *event);


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    int xstart,ystart;
    QList<NeuralNet*> netList;
    NeuralLayer *chosenLayer;
    NeuralNet *chosenItem;
    NeuronNode *chosenNode;

protected:
    bool eventFilter(QObject *obj, QEvent *ev);

};

#endif // MAINWINDOW_H
