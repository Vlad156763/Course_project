#include "mainWindow.h"

//макроси, для кращої читабельності коду
#define START_CREATE_WIN_CONSOLE
#define END_CREATE_WIN_CONSOLE

#define START_ClASS_MAIN_WINDOW   
#define END_ClASS_MAIN_WINDOW   




START_CREATE_WIN_CONSOLE; //метод для створення консолі
#ifdef Q_OS_WIN
#include <Windows.h>
static void createConsole() {
    if (GetConsoleWindow() == nullptr) {
        AllocConsole(); // Створюю вікно консолі 
        FILE* stream;
        freopen_s(&stream, "CONOUT$", "w", stdout); // Перенаправляю stdout у консоль
        freopen_s(&stream, "CONOUT$", "w", stderr); // Перенаправляю stderr у консоль
    }
    else cerr << "Консоль запущена!\n";
}
#endif // Q_OS_WIN
END_CREATE_WIN_CONSOLE;


START_ClASS_MAIN_WINDOW; //головне вікно
MainWindow_C::MainWindow_C(QWidget* parent) : QWidget(parent){
    createConsole();
    //створення головного вікна
    this->mainWidget = new QWidget(nullptr);
    //встановлення стилів
    mainWidget->setObjectName("mainWidget");
    this->mainWidget->setStyleSheet(
        "#mainWidget {"
        "   background-color: rgb(30,30,30);"
        "}"
    );
    this->mainLayout = new QGridLayout(this->mainWidget);
  
    QIcon mainIcon("Images/title.png"); // Іконка для вікна програми
    mainWidget->setWindowIcon(mainIcon); // Встановлюю іконку

    //віджети для інструментів та для головної частини
    QWidget* mainWindowToolsWidget = new QWidget(this->mainWidget);
    QWidget* mainWindowMainAreaWidget = new QWidget(this->mainWidget);
    //компоновщики для інструментальної та для головної частин
    QGridLayout* mainWindowToolsLayout = new QGridLayout(mainWindowToolsWidget);
    QGridLayout* mainWindownMainAreaLayout = new QGridLayout(mainWindowMainAreaWidget);
    //віджети головної частини
    QWidget* mainWindowAreaWidgetLeft = new QWidget(mainWindowMainAreaWidget);
    QWidget* mainWindowAreaWidgetMiddle = new QWidget(mainWindowMainAreaWidget);
    QWidget* mainWindowAreaWidgetRight = new QWidget(mainWindowMainAreaWidget);

    //віджети для інструметів
    QWidget* mainWindowToolsMiddle = new QWidget(mainWindowToolsWidget);
    QWidget* mainWindowToolsRight = new QWidget(mainWindowToolsWidget);

    //для головної частини встановлюю коефіцієнт розтягування
    mainWindownMainAreaLayout->setColumnStretch(0, 3);
    mainWindownMainAreaLayout->setColumnStretch(1, 5);
    mainWindownMainAreaLayout->setColumnStretch(2, 3);
    //для головної частини встановлюю відступи 
    mainWindownMainAreaLayout->setSpacing(5);
    mainWindownMainAreaLayout->setContentsMargins(0, 0, 0, 0);
    //для віджету інструментів встановлюю відступи 
    mainWindowToolsLayout->setSpacing(5);
    mainWindowToolsLayout->setContentsMargins(0, 0, 0, 0);
    //для віджету інструментів встановлюю коефіцієнт розтягування
    mainWindowToolsLayout->setColumnStretch(0, 3);
    mainWindowToolsLayout->setColumnStretch(1, 5);
    mainWindowToolsLayout->setColumnStretch(2, 3);
    
    //викликаю методи для роботи з віджетом інструментів
    leftSideToolsWidget(mainWindowToolsWidget, mainWindowToolsLayout);
    rightSideToolsWidget(mainWindowToolsWidget, mainWindowToolsLayout);

    auto tools = [&]() {
      
        mainWindowToolsMiddle->setStyleSheet("border-radius: 20px;" "background-color: rgb(90,90,90);");
        mainWindowToolsRight->setStyleSheet("border-radius: 20px;" "background-color: rgb(90,90,90);");

        mainWindowToolsLayout->addWidget(mainWindowToolsMiddle, 0, 1);
        mainWindowToolsLayout->addWidget(mainWindowToolsRight, 0, 2);
        };

  

    auto leftSideMainArea = [&]() {
        mainWindowAreaWidgetLeft->setStyleSheet("border-radius: 20px;" "background-color: rgb(90,90,90);");
        mainWindownMainAreaLayout->addWidget(mainWindowAreaWidgetLeft, 0, 0);
        };

    auto middleSideMainArea = [&]() {
        mainWindowAreaWidgetMiddle->setStyleSheet("border-radius: 20px;" "background-color: rgb(90,90,90);");
        mainWindownMainAreaLayout->addWidget(mainWindowAreaWidgetMiddle, 0, 1);

        };

    auto rightSideMainArea = [&]() {
        mainWindowAreaWidgetRight->setStyleSheet("border-radius: 20px;" "background-color: rgb(90,90,90);");
        mainWindownMainAreaLayout->addWidget(mainWindowAreaWidgetRight, 0, 2);
        };

    tools();
    leftSideMainArea();
    middleSideMainArea();
    rightSideMainArea();

    //для головного вікна встановлюю коефіцієнт розгтягування
    this->mainLayout->setRowStretch(0, 1);
    this->mainLayout->setRowStretch(1, 12);
    //до головного вікна додаю віджети інструментів та головну частину
    this->mainLayout->addWidget(mainWindowToolsWidget, 0, 0);
    this->mainLayout->addWidget(mainWindowMainAreaWidget, 1, 0);


    //мінімальний розмір вікна WSVGA
    this->mainWidget->setMinimumSize(1024, 600);
}

void MainWindow_C::show() {
    this->mainWidget->showMaximized();
}

void MainWindow_C::leftSideToolsWidget(QWidget* parentWidget, QGridLayout* parentLayout) {
    //віджет і компоновщик
    QWidget* mainWindowToolsLeftWidget = new QWidget(parentWidget); mainWindowToolsLeftWidget->setObjectName("mainWindowToolsLeftWidget");
    QGridLayout* mainWindowToolsLeftLayout = new QGridLayout(mainWindowToolsLeftWidget);
    //кнопки
    QPushButton* aboutUsButton = new QPushButton("Про нас", mainWindowToolsLeftWidget);
    QPushButton* helpButton = new QPushButton("Допомога", mainWindowToolsLeftWidget);
    QPushButton* aboutProgramButton = new QPushButton("Про програму", mainWindowToolsLeftWidget);
    //встановлення розтягування
    mainWindowToolsLeftLayout->setColumnStretch(0, 3);
    mainWindowToolsLeftLayout->setColumnStretch(1, 3);
    mainWindowToolsLeftLayout->setColumnStretch(2, 3);
    //встановлення політики (як воно себе поводитиме)
    aboutUsButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    helpButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    aboutProgramButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //прикріплення сигналів натиску на кнопку зі слотами обробки
    connect(aboutUsButton, &QPushButton::pressed, this, &MainWindow_C::AboutUsButtonPressed);
    connect(helpButton, &QPushButton::pressed, this, &MainWindow_C::HelpButtonPressed);
    connect(aboutProgramButton, &QPushButton::pressed, this, &MainWindow_C::AboutProgramPressed);


    //встановлення стилів
    mainWindowToolsLeftWidget->setStyleSheet(
        "#mainWindowToolsLeftWidget {"
        "   border-radius: 20px;" 
        "   background-color: rgb(90,90,90);"
        "}"
    );


    mainWindowToolsLeftLayout->addWidget(aboutUsButton, 0, 0, 1, 1);
    mainWindowToolsLeftLayout->addWidget(helpButton, 0, 1, 1, 1);
    mainWindowToolsLeftLayout->addWidget(aboutProgramButton, 0, 2, 1, 1);

    parentLayout->addWidget(mainWindowToolsLeftWidget, 0, 0);
}

void MainWindow_C::rightSideToolsWidget(QWidget* parentWidget, QGridLayout* parentLayout) {

}

MainWindow_C::~MainWindow_C() {
    delete this->mainWidget;
}

void MainWindow_C::AboutUsButtonPressed() {
    //нове вікно про нас 
}

void MainWindow_C::HelpButtonPressed() {
    //нове вікно з допомогою
}

void MainWindow_C::AboutProgramPressed() {
    //нове вікно про програму (навіщо вона та її функціонал)
}
END_ClASS_MAIN_WINDOW;