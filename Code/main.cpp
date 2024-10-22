#include "mainWindow.h"
#include <qstringlist.h>
#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlerror.h>
int main(int argc, char** argv) {
	QApplication app(argc, argv);
	MainWindow_C mainWindow;
	mainWindow.show();

	
	return app.exec();
}