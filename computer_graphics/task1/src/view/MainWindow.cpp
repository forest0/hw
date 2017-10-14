#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);

    lineAction      = new QAction(tr("line"), this);
    ellipseAction   = new QAction(tr("ellipse"), this);
    rectangleAction = new QAction(tr("rectangle"), this);
    polygonAction   = new QAction(tr("polygon"), this);
    freeDrawAction  = new QAction(tr("free"), this);
    undoAction      = new QAction(tr("undo"), this);
    
    ui->mainToolBar->addAction(lineAction);
    ui->mainToolBar->addAction(ellipseAction);
    ui->mainToolBar->addAction(rectangleAction);
    ui->mainToolBar->addAction(polygonAction);
    ui->mainToolBar->addAction(freeDrawAction);
    ui->mainToolBar->addAction(undoAction);
}

MainWindow::~MainWindow() {
    delete undoAction;
    delete freeDrawAction;
    delete polygonAction;
    delete rectangleAction;
    delete ellipseAction;
    delete lineAction;
    delete ui;
}
