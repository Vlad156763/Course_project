#include "mainWindow.h"
int main(int argc, char** argv) {
	QApplication app(argc, argv);
	mainWindowWidget window; // Створення вікна
	

	/*не чіпати метод show, так як він відповідає за відображення вікна
	і якщо його прибарити програма продовжить роботу у фоновому режимі*/
	window.show(); 
	return app.exec();
}