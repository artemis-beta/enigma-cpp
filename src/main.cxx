#include "enigma_mainwindow.hxx"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Enigma_MainWindow w;
    w.show();
    return a.exec();
}
