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
#include <qfont.h>
#include <qevent.h>
#include <qtimer.h>
#include <qstringlist.h>
#include <qpixmap.h>
#include <qpainter.h>
#include <qgraphicsview.h>
#include <qgraphicsitem.h>
#include <qstyle.h>

#include <iostream>
#include <vector>

#define cqdout qDebug() // студія плутає макрос qDebug() із класом qDebug
using std::cerr;
using std::vector;

class MainWindow_C: public QWidget {
    Q_OBJECT;
private:
    QGridLayout* mainLayout = nullptr;
    void leftSideToolsWidget(QWidget*, QGridLayout*);
    void rightSideToolsWidget(QWidget*, QGridLayout*);
    //логіка кнопки збережння та видалення для всіх типів (шаблон для лямбда функції)
    template<typename LaFunc> 
    void SaveButtonFor_AllType(QDialog*,const QString&, const QString&, LaFunc, const QStringList&);
    //логіка для вікон з додаванням та видаленням
    template<typename LaFunc> 
    void WindowAdd_and_Delete_All_Type(QDialog* , const QString&, const QString&, const QStringList&, const QStringList&, LaFunc);
    
    void SaveButtonFor_AddStudent(QDialog*);//метод для обробки кнопки "зберегти" у "додати студента"
    void SaveButtonFor_AddGroup(QDialog*); //метод для обробки кнопки "зберегти" у "додати групу"
    void SaveButtonFor_AddFaculty(QDialog*); //метод для обробки кнопки "зберегти" у "додати факультет"
    void SaveButtonFor_AddSpecialty(QDialog*); //метод для обробки кнопки "Зберегти" у "додати спеціальтість"

    void DeleteButtonFor_DeleteStudent(QDialog*); //метод для обробки кнопки "Видалити" у "видалити студента"
    void DeleteButtonFor_DeleteGroup(QDialog*);//метод для обробки кнопки "Видалити у "видалити групу"
    void DeleteButtonFor_DeleteFaculty(QDialog*); //метод для обробки кнопки "Видалити" у "видалити факултет"
    void DeleteButtonFor_DeleteІSpetialty(QDialog*); //метод для обробки кнопки "Видалити" у "видалити спеціальність"
    void showWindowAboutUs(const QString&, const QString&, const QString&, const QString&, QDialog*, QGridLayout*);//загальний метод для відображення вікон про нас
private slots:
    //слоти для інструментального віджету (лівий віджет)
    void AboutUsButtonPressed(); //вікно "про нас"
    void HelpButtonPressed();// допомога
    void AboutProgramPressed(); //про програму
    //слоти для інструментального віджету (правий віджет)
    void setingsButtonPressed(); //натиснуто кнопку налаштувань
    //слоти для налаштувань (првий віджет інструментів)
    void AddStudentButtonPressed();
    void AddGroupButtonPressed();
    void AddFacultyButtonPressed();
    void AddSpecialtyButtonPressed();
    void DeleteStudentButtonPressed();
    void DeleteGroupButtonPressed();
    void DeleteFacultyButtonPressed();
    void DeleteSpecialtyButtonPressed();
public:
     MainWindow_C(QWidget* = nullptr);
    ~MainWindow_C();
    void show();
};

class SmallMessage_C : public QWidget {
public:
    SmallMessage_C(QWidget*);
    void show(const QString&, const QString&, QGridLayout*);
};
class WarningDialog : public QDialog {
public:
    WarningDialog(QWidget*, const QString&, const QString&, const QString&, QLabel*, const QString&);
    void show();
};
#endif //!MAINWINDOW_H
/*
WindowAddAll_Type (QDialog* dialog
*/