#include "BoardView.h"
#include "ui_BoardView.h"

BoardView::BoardView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoardView)
{
    ui->setupUi(this);
}

BoardView::~BoardView()
{
    delete ui;
}
