#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QWidget>

namespace Ui {
class BoardView;
}

class BoardView : public QWidget
{
    Q_OBJECT

public:
    explicit BoardView(QWidget *parent = 0);
    ~BoardView();

private:
    Ui::BoardView *ui;
};

#endif // BOARDVIEW_H
