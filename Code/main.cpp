#include "mainWindow.h"
#include <qapplication.h>

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	CreateTables();
	MainWindow_C mainWindow;
	app.exec();
	app.quit();
	return 0;
}
