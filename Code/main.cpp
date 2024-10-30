#include "mainWindow.h"

#include <qapplication.h>
#include <qwidget.h>
#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlerror.h>


int main(int argc, char** argv) {
	QApplication app(argc, argv);
	MainWindow_C mainWindow;
	mainWindow.show();

	QStringList drivers = QSqlDatabase::drivers();
	cqdout << "Доступні драйвери:" << drivers;


	
	return app.exec();
}