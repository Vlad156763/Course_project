#include "mainWindow.h"
#include <iostream>
#include <qapplication.h>
#include <qwidget.h>
using namespace std;
int main(int argc, char** argv) {
	QApplication app(argc, argv);
	CreateTables();
	MainWindow_C mainWindow;
	mainWindow.update();
	mainWindow.showMaximized();
	app.exec();
	return 0;
}
