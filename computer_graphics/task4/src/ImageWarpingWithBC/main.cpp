#include "view/MainWindow.h"
#include <QtWidgets/QApplication>

#include "view/ImageView.h"

int main(int argc, char *argv[]) {
   QApplication a(argc, argv);
   MainWindow w;
   w.show();
   
   return a.exec();
}
