#ifndef TEST_AND_DEBUGING_MAINWINDOW_H
#define TEST_AND_DEBUGING_MAINWINDOW_H

#include <qpushbutton.h>

#define START_DYNAMIC_RESIZE_TEXT_IN_BUTTON
#define END_DYNAMIC_RESIZE_TEXT_IN_BUTTON

#define START_WATCH_SIZE_WIDGET
#define END_WATCH_SIZE_WIDGET


START_DYNAMIC_RESIZE_TEXT_IN_BUTTON;
//клас для зміни розміру тексту в кнопці відносно коефіцієнту
class dynamicResizeTextInButton : public QPushButton {
public:
    // Конструктор для створення кнопки
    dynamicResizeTextInButton(const QString& text, const int& textСoefficient_P, QWidget* parent)
        : QPushButton(text, parent), textСoefficient(textСoefficient_P) {}
private:
    double textСoefficient = 1;
    // Перевизначений метод обробки події зміни розміру
    void resizeEvent(QResizeEvent* event) override {
        QPushButton::resizeEvent(event); // базовий метод
        myResizeEventForButton();
    }
    void myResizeEventForButton() {
        // Отримую нові розміри кнопки
        int newWidth = this->width(); //повертає розміри кнопки
        int newHeight = this->height();//повертає розміри кнопки
        // Визначаю новий розмір шрифту
        int newFontSize = qMin(newWidth, newHeight) / this->textСoefficient; // для адаптації тексту, обирається сторона, та що менша 
        QFont font = this->font();
        font.setPointSize(newFontSize); //встановлюю новий розмір шрифту 
        this->setFont(font); //додаю ноий розмір шрифту до кнопки
    }
};
END_DYNAMIC_RESIZE_TEXT_IN_BUTTON;


START_WATCH_SIZE_WIDGET;
//клас для виведення в консоль розміри поточного вікна 
class watchSizeWidget : public QWidget {
public:
    watchSizeWidget(QWidget* parent = nullptr) : QWidget(parent) {}
private:
    // Перевизначаю метод обробки події зміни розміру
    void resizeEvent(QResizeEvent* event) override {
        QWidget::resizeEvent(event); // базовий метод
        logSize(); // викликаю метод для виведення розмірів
    }
    void logSize() {
        // Отримую нові розміри віджету
        int width = this->width();
        int height = this->height();
        // Виводжу розміри і назву класу у консоль
        qDebug() << "New size:" << width << "x" << height;
    }
};
END_WATCH_SIZE_WIDGET;
#endif // !TEST_AND_DEBUGING(MAINWINDOW)_H






