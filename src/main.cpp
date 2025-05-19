#include "view/MainWindow.h"
#include "controller/MainController.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    MainController controller(&w);

    w.show();
    return a.exec();
}