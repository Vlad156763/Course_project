#include "mainWindow.h"

#include <qapplication.h>
#include <qwidget.h>

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	MainWindow_C mainWindow;
	mainWindow.update();
	mainWindow.showMaximized();
	CreateTables();
	app.exec();
	return 0;
}