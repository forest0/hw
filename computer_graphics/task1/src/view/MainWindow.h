#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QAction>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QAction *lineAction;
    QAction *ellipseAction;
    QAction *rectangleAction;
    QAction *polygonAction;
    QAction *freeDrawAction;
    QAction *undoAction;
};

#endif // MAINWINDOW_H
