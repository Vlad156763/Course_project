#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <qapplication.h>
#include <qwidget.h>
#include <qgridlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <iostream>
#define cqdout qDebug() // студія плутає макрос qDebug() із класом qDebug
using std::cerr;
class mainWindowWidget : public QWidget {
    Q_OBJECT
public:
    mainWindowWidget(QWidget* parent = nullptr);
    void show(); //перевантаження методу відображення віджету
public slots:

};
#endif //!MAINWINDOW_H