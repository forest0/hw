#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QtWidgets/QFileDialog>
#include "../tools/Log.h"
#include "../wrapping/Mapper.h"
#include "../wrapping/IDWMapper.h"
#include "../wrapping/ImageWrapper.h"
#include <QtGui/QRgb>
#include "../tools/Utils.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    imageView()
{
    ui->setupUi(this);
    initUI();
    this->setWindowTitle(tr("ImageWrapping"));
    this->resize(800,600);

    this->setCentralWidget(&imageView);

    connectSignalsAndSlots();
}

MainWindow::~MainWindow()
{
    delete rbfAction;
    delete idwAction;
    delete mirrorAction;
    delete openAction;
    delete ui;
}

void MainWindow::initUI() {
    initActions();
    initMainToolBar();
}

void MainWindow::initMainToolBar() {
    this->ui->mainToolBar->addAction(openAction);
    this->ui->mainToolBar->addAction(clearControlPointsAction);

    this->ui->mainToolBar->addSeparator();

    this->ui->mainToolBar->addAction(mirrorAction);
    this->ui->mainToolBar->addAction(idwAction);
    this->ui->mainToolBar->addAction(rbfAction);
}

void MainWindow::initActions() {
    this->openAction = new QAction(tr("open"), this);
    this->clearControlPointsAction = new QAction(tr("clear"), this);
    this->mirrorAction = new QAction(tr("mirror"), this);
    this->idwAction = new QAction(tr("IDW"), this);
    this->rbfAction = new QAction(tr("RBF"), this);

    updateActionsStatus();

}

void MainWindow::onOpenActionTriggered(bool checked) {
    // TODO: default position "../../../data" may cause bug
    QFileDialog *fileDialog = new QFileDialog(
            this, tr("Open Image"), "../../../data", tr("image(*.bmp)")); 
    if (fileDialog->exec() == QFileDialog::Accepted) {
        imageFilePath = fileDialog->selectedFiles()[0];
        imageView.setImage(new QImage(imageFilePath));
        this->idwAction->setEnabled(true);

        this->update();
        updateActionsStatus();
    }
}

void MainWindow::onMirrorActionTriggered(bool checked) {
    if (imageView.getImage()) {

    }

}

void MainWindow::onIDWActionTriggered(bool checked) {
    QImage *image = imageView.getImage();
    if (image && imageView.getControlPoints().size()) {
        Utils::printControlPoints(imageView.getControlPoints());
        wrapImageAndShowIt(
                new IDWMapper(imageView.getControlPoints()));
    }
}

void MainWindow::onRBFActionTriggered(bool checked) {

}

void MainWindow::onClearControlPointsActionTriggered(bool checked) {
    imageView.clearControlPoints();
    this->update();
}

void MainWindow::connectSignalsAndSlots() {
    connect(openAction, &QAction::triggered, 
            this, &MainWindow::onOpenActionTriggered);
    connect(idwAction, &QAction::triggered,
            this, &MainWindow::onIDWActionTriggered);
    connect(clearControlPointsAction, &QAction::triggered,
            this, &MainWindow::onClearControlPointsActionTriggered);
}

void MainWindow::updateActionsStatus() {
    if (imageView.getImage()) {
        this->idwAction->setEnabled(true);
        this->rbfAction->setEnabled(true);
        this->mirrorAction->setEnabled(true);
    } else {
        this->idwAction->setEnabled(false);
        this->rbfAction->setEnabled(false);
        this->mirrorAction->setEnabled(false);
    }
}

void MainWindow::wrapImageAndShowIt(Mapper *mapper) {
    ImageWrapper wrapper(mapper);
    QImage *wrappedImage = wrapper.wrap(imageView.getImage());
    ImageView wrappedView(this);
    wrappedView.setImage(wrappedImage);
    wrappedView.resize(wrappedImage->size());
    wrappedView.show();
    wrappedView.exec();

}
