#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "../tools/Utils.h"
#include <QtWidgets/QFrame>
#include <QtWidgets/QMenu>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    boardView()
{

    initWindow();
    addActionsAndConnections();
}

void MainWindow::addActions() {
    lineAction      = new QAction(tr("line"), this);
    ellipseAction   = new QAction(tr("ellipse"), this);
    rectangleAction = new QAction(tr("rectangle"), this);
    polygonAction   = new QAction(tr("polygon"), this);
    freeDrawAction  = new QAction(tr("free"), this);
    undoAction      = new QAction(tr("undo"), this);
    redoAction      = new QAction(tr("redo"), this);

    // add actions to editMenu
    editMenu->addAction(lineAction);
    editMenu->addAction(ellipseAction);
    editMenu->addAction(rectangleAction);
    editMenu->addAction(polygonAction);
    editMenu->addAction(freeDrawAction);

    editMenu->addSeparator();

    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);

    // add actions to toolbar
    ui->mainToolBar->addAction(lineAction);
    ui->mainToolBar->addAction(ellipseAction);
    ui->mainToolBar->addAction(rectangleAction);
    ui->mainToolBar->addAction(polygonAction);
    ui->mainToolBar->addAction(freeDrawAction);

    ui->mainToolBar->addSeparator();

    ui->mainToolBar->addAction(undoAction);
    ui->mainToolBar->addAction(redoAction);

    // redo and undo is disabled at the beginning
    undoAction->setEnabled(false);
    redoAction->setEnabled(false);

    addIcons();
}

void MainWindow::addIcons() {
    
    lineAction->setIcon(QIcon(":/resources/icon/line.png"));
    ellipseAction->setIcon(QIcon(":/resources/icon/ellipse.png"));
    rectangleAction->setIcon(QIcon(":/resources/icon/rectangle.png"));
    polygonAction->setIcon(QIcon(":/resources/icon/polygon.png"));
    freeDrawAction->setIcon(QIcon(":/resources/icon/free.png"));

    undoAction->setIcon(QIcon(":/resources/icon/undo.png"));
    redoAction->setIcon(QIcon(":/resources/icon/redo.png"));

    this->setWindowIcon(QIcon(":/resources/icon/mainIcon.png"));
}

void MainWindow::addConnections() {
    // click one of drawing type action, notify statusbar and board(model) to make response
    connect(this, &MainWindow::drawingTypeChange,
            this, &MainWindow::onDrawingTypeChange);

    connect(boardView.getBoard(), &Board::shownFiguresAmountChange,
            this, &MainWindow::onShownFiguresAmountChange);
    connect(boardView.getBoard(), &Board::deletedFiguresAmountChange,
            this, &MainWindow::onDeletedFiguresAmountChange);

    // drawing type related action
    connect(lineAction, &QAction::triggered, [this](bool checked) {
        emit drawingTypeChange(FigureType::line);
    });
    connect(ellipseAction, &QAction::triggered, [this](bool checked) {
        emit drawingTypeChange(FigureType::ellipse);
    });
    connect(rectangleAction, &QAction::triggered, [this](bool checked) {
        emit drawingTypeChange(FigureType::rectangle);
    });
    connect(polygonAction, &QAction::triggered, [this](bool checked) {
        emit drawingTypeChange(FigureType::polygon);
    });
    connect(freeDrawAction, &QAction::triggered, [this](bool checked) {
        emit drawingTypeChange(FigureType::freeDraw);
    });

    // click undo/redo action, notify board(model) to make response
    connect(undoAction, &QAction::triggered, [this](bool checked){
        boardView.getBoard()->popBackFromShownFigures();
    });
    connect(redoAction, &QAction::triggered, [this](bool checked){
        boardView.getBoard()->popBackFromDeletedFigures();
    });

}

void MainWindow::addActionsAndConnections() {
    addActions();
    addConnections();
}

void MainWindow::initMenuBar() {
    editMenu = new QMenu(tr("Edit"), this);
    ui->menuBar->addMenu(editMenu);
}

// TODO: alignment
void MainWindow::initStatusBar() {
    fixedLabelOnStatusBar = new QLabel(tr("current drawing: "), this);
    drawingTypeLabelOnStatusBar = new QLabel(this);

    // style
    fixedLabelOnStatusBar->setFrameStyle(
            QFrame::Panel | QFrame::Plain);
    fixedLabelOnStatusBar->setLineWidth(0);
    drawingTypeLabelOnStatusBar->setFrameStyle(
            QFrame::Panel | QFrame::Plain);
    drawingTypeLabelOnStatusBar->setLineWidth(0);

    // set text
    drawingTypeLabelOnStatusBar->setText(
        Utils::toString(boardView.getBoard()->getCurrentDrawingType()).c_str());
    setDrawingTypeLabelText(boardView.getBoard()->getCurrentDrawingType());

    // add to status bar
    ui->statusBar->addPermanentWidget(fixedLabelOnStatusBar);
    ui->statusBar->addPermanentWidget(drawingTypeLabelOnStatusBar);
}

void MainWindow::initWindow() {
    ui->setupUi(this);
    this->resize(800, 600);
    this->setCentralWidget(&boardView);
    this->setWindowTitle("Simple Graffit Board");

    initMenuBar();
    initStatusBar();
}

MainWindow::~MainWindow() {
    delete drawingTypeLabelOnStatusBar;
    delete fixedLabelOnStatusBar;
    delete editMenu;
    delete redoAction;
    delete undoAction;
    delete freeDrawAction;
    delete polygonAction;
    delete rectangleAction;
    delete ellipseAction;
    delete lineAction;
    delete ui;
}

void MainWindow::setDrawingTypeLabelText(FigureType type) {
    this->drawingTypeLabelOnStatusBar->setText(
            Utils::toString(type).c_str());
}

void MainWindow::onDrawingTypeChange(FigureType type) {
    boardView.getBoard()->setCurrentDrawingType(type);
    drawingTypeLabelOnStatusBar->setText(
            Utils::toString(type).c_str());
}

void MainWindow::onShownFiguresAmountChange(
        unsigned int currentAmount) {

    undoAction->setEnabled(currentAmount != 0);
}

void MainWindow::onDeletedFiguresAmountChange(
        unsigned int currentAmount) {

    redoAction->setEnabled(currentAmount != 0);
}
