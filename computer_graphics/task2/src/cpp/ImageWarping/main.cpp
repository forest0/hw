#include "view/MainWindow.h"
#include <QtWidgets/QApplication>

#include <QtGui/QImage>
#include "tools/Utils.h"
#include "warping/Mapper.h"
#include "warping/IDWMapper.h"
#include <iostream>

#include "warping/Eigen/Dense"

using std::cout;
using std::endl;

void test() {
    // QImage *image = new QImage("../../../data/grid.bmp");
    // Utils::showImage(image);
    // Mapper *mapper = new IDWMapper(Utils::getControlPoints());
    // std::cout << mapper->map(QPoint(25,233)).y() << std::endl;
    
    Eigen::Matrix2f A, b;
   A << 2, -1, -1, 3;
   b << 1, 2, 3, 1;
   cout << "Here is the matrix A:\n" << A << endl;
   cout << "Here is the right hand side b:\n" << b << endl;
   Eigen::Matrix2f x = A.ldlt().solve(b);
   cout << "The solution is:\n" << x << endl;

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
