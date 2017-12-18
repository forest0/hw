#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QtCore/QDebug>
#include <QtWidgets/QFileDialog>
#include "../utils/Utils.h"
#include <iostream>

#include <QtGui/QPainter>
#include "../core/model/Triangle.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    imageView(this)
{
    ui->setupUi(this);
    initUI();
    this->setWindowTitle(tr("Image Warping with BC"));

    this->setCentralWidget(&imageView);

    connectSignalsAndSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
    if (this->openAction) {
        delete openAction;
        openAction = nullptr;
    }

    if (this->debugAction) {
        delete debugAction;
        debugAction = nullptr;
    }
}
void MainWindow::initUI() {
    initActions();
    initMainToolBar();
}

void MainWindow::initMainToolBar() {
    this->ui->mainToolBar->addAction(openAction);
    this->ui->mainToolBar->addSeparator();
    this->ui->mainToolBar->addAction(debugAction);
}

void MainWindow::initActions() {
    this->openAction = new QAction(tr("open"), this);
    this->debugAction = new QAction(tr("debug"), this);
}

void MainWindow::connectSignalsAndSlots() {
    connect(openAction, &QAction::triggered,
            this, &MainWindow::onOpenActionTriggered);
    connect(debugAction, &QAction::triggered,
            this, &MainWindow::onDebugActionTriggered);
}

void MainWindow::onOpenActionTriggered(bool checked) {
    // TODO: default position "../../../data" may cause bug
    QFileDialog *fileDialog = new QFileDialog(
            this, tr("Open Image"), "../../data", 
            tr("image(*.jpeg)")); 
    if (fileDialog->exec() == QFileDialog::Accepted) {
        imageFilePath = fileDialog->selectedFiles()[0];
        imageView.setImage(new QImage(imageFilePath));

        this->update();
    }
}

void MainWindow::onDebugActionTriggered(bool checked) {
}
