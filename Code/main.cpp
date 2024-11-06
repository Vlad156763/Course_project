#include "mainWindow.h"

#include <qapplication.h>
#include <qwidget.h>

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	MainWindow_C mainWindow;
	mainWindow.show();

	QStringList drivers = QSqlDatabase::drivers();
	cqdout << "Доступні драйвери:" << drivers;

	CreateTables();

	return app.exec();
}