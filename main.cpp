#include "Windows/MainWindowQml.h"
#include <QApplication>

int main(int argc, char *argv[])
{
   QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
   QCoreApplication::setOrganizationName("Some organization");
   QGuiApplication app(argc, argv);
   MainWindowQml mainWindow{"qrc:/MainWindow.qml"};
   return app.exec();
}
