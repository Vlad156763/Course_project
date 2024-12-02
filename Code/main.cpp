#include "mainWindow.h"
#include "ex.h"
#include <iostream>
#include <qapplication.h>
#include <qwidget.h>
using namespace std;

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	CreateTables();
	MainWindow_C mainWindow;
	app.exec();
	app.quit();
	return 0;
}
