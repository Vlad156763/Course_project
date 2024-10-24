#include "mainWindow.h"
int main(int argc, char** argv) {
	QApplication app(argc, argv);
	MainWindow_C mainWindow;
	mainWindow.show();

	
	return app.exec();
}