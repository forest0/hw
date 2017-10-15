#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QAction>
#include <QtWidgets/QLabel>
#include "model/Board.h"
#include "view/BoardView.h"

namespace Ui {
class MainWindow;
}

/* main window of the app
 */
class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void drawingTypeChange(FigureType type);

private slots:
    void onDrawingTypeChange(FigureType type);
    void onShownFiguresAmountChange(unsigned int currentAmount);
    void onDeletedFiguresAmountChange(unsigned int currentAmount);

private:
    Ui::MainWindow *ui;

    BoardView boardView;

    QAction *lineAction;
    QAction *ellipseAction;
    QAction *rectangleAction;
    QAction *polygonAction;
    QAction *freeDrawAction;
    QAction *undoAction;
    QAction *redoAction;

    QLabel *fixedLabelOnStatusBar;
    QLabel *drawingTypeLabelOnStatusBar;

    void setDrawingTypeLabelText(FigureType type);

    void addActions();
    void addIcons();
    void addConnections();
    void addActionsAndConnections();
    void initStatusBar();
    void initWindow();
};

#endif // MAINWINDOW_H
