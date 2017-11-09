#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QAction>
#include "ImageView.h"
#include "../warping/Mapper.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void onOpenActionTriggered(bool checked);
        // void onMirrorActionTriggered(bool checked);
        void onIDWActionTriggered(bool checked);
        void onRBFActionTriggered(bool checked);
        void onClearControlPointsActionTriggered(bool checked);

    private:
        void initUI();
        void initMainToolBar();
        void initActions();
        void connectSignalsAndSlots();
        void updateActionsStatus();
        void warpImageAndShowIt(Mapper *mapper);

    private:
        Ui::MainWindow *ui;
        ImageView imageView;

        QAction *openAction;
        QAction *clearControlPointsAction;
        // QAction *mirrorAction;
        QAction *idwAction;
        QAction *rbfAction;

        QString imageFilePath;
};

#endif // MAINWINDOW_H
