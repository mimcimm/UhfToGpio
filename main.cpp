#include "serialProcess.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SerialProcess serialProcess;

      system("echo 41 > /sys/class/gpio/export");
      system("echo out > /sys/class/gpio/gpio41/direction");

   //serialProcess;
    return a.exec();
}
