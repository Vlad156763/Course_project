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
#include <qpainter.h>
#include <qrandom.h>
#include <qmovie.h>
#include <qtextedit.h>
#include <qgraphicsproxywidget.h>



#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlerror.h>
#include <QtSql/qsqlquery.h>
#include <qabstractitemview.h>

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <cstring>//для std::strrchr

using std::cerr;
using std::strrchr;
using std::vector;
using std::this_thread::sleep_for;
using namespace std::chrono;

#define FILENAME (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define cqdout (qDebug() << "┌[msg]" << FILENAME << __LINE__ << "\n└TEXT:" )

void CreateTables();
void addSpecialty(QSqlQuery& query, const QString& specialty);
void addFaculty(QSqlQuery& query, const QString& specialty, const QString& faculty);
void addGroup(QSqlQuery& query, const QString& specialty, const QString& faculty, int class_group);
void addStudent(QSqlQuery& query, const QString& name, const QString& faculty, const QString& specialty, int class_group);

void getAllStudents(QSqlQuery& query);
void getFaculty(QSqlQuery& query);
void getSpecialty(QSqlQuery& query);
void getGroup(QSqlQuery& query);
void DeleteSpecialty(QSqlQuery& query, const QString& specialty);
void DeleteFaculty(QSqlQuery& query, const QString& specialty, const QString& faculty);
void DeleteGroup(QSqlQuery& query, const QString& specialty, const QString& faculty, int class_group);
void DeleteStudent(QSqlQuery& query, const QString& name, const QString& specialty, const QString& faculty, int class_group);
int getNextAvailableId(QSqlQuery& query, const QString& tableName, const QString& idColumn);
void dropAllTables();

class counterTimer {
    int counter = 0;
public:
    int operator ++ ();
    int operator -- ();
    int operator ++ (int);
    int operator -- (int);
    int get() {
        return this->counter;
    }

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
class smartText : public QLabel {
public:
    smartText(const QString&, QWidget* = nullptr);
private:
    QString originalText; // зберігає повний текст
    void updateElidedText();
    void resizeEvent(QResizeEvent*) override;
};
class blockWidget : public QPushButton {
    Q_OBJECT
private:
    //клас коло 
    class circleQWidget : public QWidget {
    private:
        int x = 0;
        int y = 0;
        int r1 = 0;
        int r2 = 0;
        QColor color;
    public:
        circleQWidget(QWidget* = nullptr);
        void SetCoordinats(const int&, const int&);
        void SetSizeCircle(const int&, const int&);
        void SetColor(const QColor&);
        void SetChar(const QChar&);
    private:
        void paintEvent(QPaintEvent*) override;
    };
    
public:
    blockWidget(const QString&, QWidget* = nullptr);
    
    void AddStructure();

private:
    void resizeEvent(QResizeEvent* ) override;
    QColor generateColorFromString(const QString&);
    smartText* text = nullptr;
    circleQWidget* circle = nullptr;
    QHBoxLayout* layout = nullptr;

public slots:
    void specialtyButtonPressed(counterTimer&, QWidget*, QWidget*, QWidget*, const QString&);
    void GroupButtonPressed(counterTimer&, QWidget*, QWidget*, const QString&, const QString&, const QString&);
    void FacultyButtonPressed(counterTimer&,  QWidget*, QWidget*, const QString&, const QString&);
    void StudyButtonPressed(const QString&, const QString&, const QString&, const QString&);
    void PredmetButtonPressed(const QString&, const QString&, const QString&, const QString&, const QString&);
};
class configBlock{
private:
    QWidget* widget = nullptr;
public:
    configBlock();
    void setWidget(QWidget*);
    template<typename LaFunc>
    void setConfigBlock(LaFunc, QWidget*, counterTimer&);
    template<typename LaFunc>
    void setConfigPredmetBlock(LaFunc, QWidget*);

};

class MainWindow_C : public QWidget {
    Q_OBJECT;
private:
    QGridLayout* mainLayout = nullptr;
    void leftSideToolsWidget(QWidget*, QGridLayout*)const;
    void rightSideToolsWidget(QWidget*, QGridLayout*)const;
    //логіка кнопки збережння та видалення для всіх типів (шаблон для лямбда функції)
    template<typename LaFunc>
    void SaveButtonFor_AllType(QDialog*, const QString&, const QString&, LaFunc, const QStringList&);

    void SaveButtonFor_AddStudent(QDialog*);//метод для обробки кнопки "зберегти" у "додати студента"
    void SaveButtonFor_AddGroup(QDialog*); //метод для обробки кнопки "зберегти" у "додати групу"
    void SaveButtonFor_AddFaculty(QDialog*); //метод для обробки кнопки "зберегти" у "додати факультет"
    void SaveButtonFor_AddSpecialty(QDialog*); //метод для обробки кнопки "Зберегти" у "додати спеціальтість"

    void DeleteButtonFor_DeleteStudent(QDialog*); //метод для обробки кнопки "Видалити" у "видалити студента"
    void DeleteButtonFor_DeleteGroup(QDialog*);//метод для обробки кнопки "Видалити у "видалити групу"
    void DeleteButtonFor_DeleteFaculty(QDialog*); //метод для обробки кнопки "Видалити" у "видалити факултет"
    void DeleteButtonFor_DeleteІSpetialty(QDialog*); //метод для обробки кнопки "Видалити" у "видалити спеціальність"
    void showWindowAboutUs(const QString&, const QString&, const QString&, const QString&, QDialog*, QGridLayout*);//загальний метод для відображення вікон про нас
    template<typename LaFunc>
    void WindowAdd_and_Delete_All_Type(QDialog*, const QString&, const QString&, const QStringList&, const QStringList&, LaFunc, const int& = 375);

    //віджет для головної частини 
    void mainWidgetArea(QWidget*, QGridLayout*, QWidget*);

    //таймер для відслідковування віджетів головної частини
    counterTimer* TimersCounter = nullptr;
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
    void show();
    ~MainWindow_C();
    friend class blockWidget;
};
//логіка для вікон з додаванням та видаленням


#endif //!MAINWINDOW_H


