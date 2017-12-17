#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QtCore/QDebug>
#include <QtWidgets/QFileDialog>

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
}
void MainWindow::initUI() {
    initActions();
    initMainToolBar();
}

void MainWindow::initMainToolBar() {
    this->ui->mainToolBar->addAction(openAction);
    this->ui->mainToolBar->addSeparator();
    this->ui->mainToolBar->addAction(drawCageAction);
    this->ui->mainToolBar->addSeparator();
    this->ui->mainToolBar->addAction(dragCageAction);
}

void MainWindow::initActions() {
    this->openAction = new QAction(tr("open"), this);
    this->drawCageAction = new QAction(tr("draw cage"), this);
    this->dragCageAction = new QAction(tr("drag cage"), this);
}

void MainWindow::connectSignalsAndSlots() {
    connect(openAction, &QAction::triggered,
            this, &MainWindow::onOpenActionTriggered);
    connect(drawCageAction, &QAction::triggered,
            this, &MainWindow::onDrawCageActionTriggered);
    connect(dragCageAction, &QAction::triggered,
            this, &MainWindow::onDragCageActionTriggered);
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

void MainWindow::onDrawCageActionTriggered(bool checked) {
    qDebug() << "draw";
}

void MainWindow::onDragCageActionTriggered(bool checked) {
    qDebug() << "drag";
}

