#include "view/MainWindow.h"
#include <QtWidgets/QApplication>

#include <QtGui/QImage>
#include "tools/Utils.h"
#include "wrapping/Mapper.h"
#include "wrapping/IDWMapper.h"
#include <iostream>


void test() {
    // QImage *image = new QImage("../../../data/grid.bmp");
    // Utils::showImage(image);
    // Mapper *mapper = new IDWMapper(Utils::getControlPoints());
    // std::cout << mapper->map(QPoint(25,233)).y() << std::endl;
    
    ImageView view;
    view.show();
    view.exec();

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    

    // test();
    
    return a.exec();
    // return 0;
}
