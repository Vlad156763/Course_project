#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <qapplication.h>
#include <qpushbutton.h>
#include <qwidget.h>
#include <qgridlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qdialog.h>
#include <qradiobutton.h>
#include <qbuttongroup.h>
#include <qmessagebox.h>
#include <qevent.h>
#include <iostream>
#define cqdout qDebug() // студія плутає макрос qDebug() із класом qDebug
using std::cerr;

class MainWindow_C: public QWidget {
    Q_OBJECT;
private:
    QWidget* mainWidget = nullptr;
    QGridLayout* mainLayout = nullptr;
    void leftSideToolsWidget(QWidget*, QGridLayout*);
    void rightSideToolsWidget(QWidget*, QGridLayout*);
private slots:
    void AboutUsButtonPressed(); //вікно "про нас"
    void HelpButtonPressed();// допомога
    void AboutProgramPressed(); //про програму
public:
     MainWindow_C(QWidget* = nullptr);
    ~MainWindow_C();
    void show();
};

#endif //!MAINWINDOW_H