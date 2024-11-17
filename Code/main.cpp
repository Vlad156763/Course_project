#include "mainWindow.h"

#include <qapplication.h>
#include <qwidget.h>

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	MainWindow_C mainWindow;
	mainWindow.show();
	CreateTables();
	return app.exec();;
}
//todo: видаляти пам'ять під створені об'єкти! 
//todo: пагінація
//todo: вікно про додаток
//todo: вікно про програму (її історія створення)
