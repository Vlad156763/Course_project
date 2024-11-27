#include "mainWindow.h"

#include <qapplication.h>
#include <qwidget.h>

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	CreateTables();
	MainWindow_C mainWindow;
	mainWindow.update();
	mainWindow.showMaximized();
	app.exec();
	return 0;
}
