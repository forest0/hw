#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ImageView.h"
#include <QtWidgets/QAction>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onOpenActionTriggered(bool checked);
    void onDrawCageActionTriggered(bool checked);
    void onDragCageActionTriggered(bool checked);

private:
    void initUI();
    void initMainToolBar();
    void initActions();
    void connectSignalsAndSlots();

private:
    Ui::MainWindow *ui;

    ImageView imageView;

    QAction *openAction;
    QAction *drawCageAction;
    QAction *dragCageAction;

    QString imageFilePath;

};

#endif // MAINWINDOW_H
