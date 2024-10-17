#include <qapplication.h>  //стандартна бібліотека для роботи з графічними додатками
#include <qlabel.h> //створення міток з (текстом,зображенням)



int main(int argc, char* argv[]) {
    QApplication app(argc, argv); //створення об'єкту та ініціалізація програми

    QLabel* label = new QLabel("Привіт"); //створення покажчика на мітку "Привіт"
    label->setWindowTitle("Тестова програма"); //встановлення заголовку вікна
    label->resize(200, 200);//встановлення розміру вікна 200 на 200 
    label->show(); //відображення вікна на екрані


    return app.exec();
}
