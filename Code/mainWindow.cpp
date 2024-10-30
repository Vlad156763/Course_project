#include "mainWindow.h"

//макроси, для кращої читабельності коду
#define START_CREATE_WIN_CONSOLE
#define END_CREATE_WIN_CONSOLE

#define START_ClASS_MAIN_WINDOW   
#define END_ClASS_MAIN_WINDOW   

#define START_CLASS_SMALL_MESSAGE
#define END_CLASS_SMALL_MESSAGE


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
    //присворюю до змінної 
    //встановлення стилів
    this->setObjectName("mainWidget");
    this->setStyleSheet(
        "#mainWidget {"
        "   background-color: rgb(30,30,30);"
        "}"
    );
    this->mainLayout = new QGridLayout(this);
  
    this->setWindowTitle("Успішність студентів");
    QIcon mainIcon("Images/title.png"); // Іконка для вікна програми
    this->setWindowIcon(mainIcon); // Встановлюю іконку

    //віджети для інструментів та для головної частини
    QWidget* mainWindowToolsWidget = new QWidget(this);
    QWidget* mainWindowMainAreaWidget = new QWidget(this);
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
    //викликаю методи для роботи з головною частиною


    QString styleWidgets =
        "   border-radius: 10px;"
        "   background-color: rgb(90,90,90);";

    mainWindowAreaWidgetMiddle->setStyleSheet(styleWidgets);
    
    mainWindowAreaWidgetLeft->setStyleSheet(styleWidgets);
    mainWindowToolsMiddle->setStyleSheet(styleWidgets);
    mainWindowAreaWidgetRight->setStyleSheet(styleWidgets);
    
    mainWindowToolsLayout->addWidget(mainWindowToolsMiddle, 0, 1);

    mainWindownMainAreaLayout->addWidget(mainWindowAreaWidgetLeft, 0, 0);
    mainWindownMainAreaLayout->addWidget(mainWindowAreaWidgetMiddle, 0, 1);
    mainWindownMainAreaLayout->addWidget(mainWindowAreaWidgetRight, 0, 2);
    //для головного вікна встановлюю коефіцієнт розгтягування
    this->mainLayout->setRowStretch(0, 1);
    this->mainLayout->setRowStretch(1, 12);
    //до головного вікна додаю віджети інструментів та головну частину
    this->mainLayout->addWidget(mainWindowToolsWidget, 0, 0);
    this->mainLayout->addWidget(mainWindowMainAreaWidget, 1, 0);


    //мінімальний розмір вікна WSVGA
    this->setMinimumSize(1024, 600);
}

void MainWindow_C::show() {
    this->showMaximized();
}

void MainWindow_C::leftSideToolsWidget(QWidget* parentWidget, QGridLayout* parentLayout) {
    //віджет і компоновщик
    QWidget* mainWindowToolsLeftWidget = new QWidget(parentWidget); mainWindowToolsLeftWidget->setObjectName("mainWindowToolsLeftWidget");
    QGridLayout* mainWindowToolsLeftLayout = new QGridLayout(mainWindowToolsLeftWidget);
    //видаляю відступи для компоновщика
    mainWindowToolsLeftLayout->setSpacing(0); //відступи між внутрішніми віджетами
    mainWindowToolsLeftLayout->setContentsMargins(2, 5, 2, 5); //внутрішні відступи
    //кнопки
    QPushButton* aboutUsButton = new QPushButton("Про нас", mainWindowToolsLeftWidget); 
    QPushButton* helpButton = new QPushButton("Допомога", mainWindowToolsLeftWidget);
    QPushButton* aboutProgramButton = new QPushButton("Про програму", mainWindowToolsLeftWidget);
    //встановлення розтягування
    mainWindowToolsLeftLayout->setColumnStretch(0, 3);
    mainWindowToolsLeftLayout->setColumnStretch(1, 3);
    mainWindowToolsLeftLayout->setColumnStretch(2, 3);
    //встановлення політики (як воно себе поводитиме)
    aboutUsButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    helpButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    aboutProgramButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    
    //прикріплення сигналів натиску на кнопку зі слотами обробки
    connect(aboutUsButton, &QPushButton::pressed, this, &MainWindow_C::AboutUsButtonPressed);
    connect(helpButton, &QPushButton::pressed, this, &MainWindow_C::HelpButtonPressed);
    connect(aboutProgramButton, &QPushButton::pressed, this, &MainWindow_C::AboutProgramPressed);
    //встановюю назви об'єктів (однакові) для кнопок
    aboutUsButton->setObjectName("customButton");
    helpButton->setObjectName("customButton");
    aboutProgramButton->setObjectName("customButton");
    //встановлення стилів
    QString buttonStyle =
        "#customButton {"
        "   border-radius: 5px;"
        "   background-color: rgb(64, 64, 64);"
        "   font-size: 12px;"
        "   margin: 5px;"
        "   padding: 5px;"
        "}"
        "#customButton:hover {"
        "   background-color: rgb(120, 120, 120);"
        "}"
        "#customButton:focus {"
        "   outline: 0px;"
        "}"
        "#customButton:pressed  {"
        "  background-color: rgb(150, 150, 150);"
        "}";
    mainWindowToolsLeftWidget->setStyleSheet(
        "#mainWindowToolsLeftWidget {"
        "   border-radius: 10px;" 
        "   background-color: rgb(90,90,90);"
        "}"
    );
    
    aboutProgramButton->setStyleSheet(buttonStyle);
    helpButton->setStyleSheet(buttonStyle);
    aboutUsButton->setStyleSheet(buttonStyle);

    mainWindowToolsLeftLayout->addWidget(aboutUsButton, 0, 0, 1, 1);
    mainWindowToolsLeftLayout->addWidget(helpButton, 0, 1, 1, 1);
    mainWindowToolsLeftLayout->addWidget(aboutProgramButton, 0, 2, 1, 1);

    parentLayout->addWidget(mainWindowToolsLeftWidget, 0, 0); //додаю до компоновщика інструментів віджет з кнопками
}

void MainWindow_C::rightSideToolsWidget(QWidget* parentWidget, QGridLayout* parentLayout)  {
    //віджет і компоновщик
    QWidget* mainWindowToolsRightWidget = new QWidget(parentWidget); mainWindowToolsRightWidget->setObjectName("mainWindowToolsRightWidget");
    QGridLayout* mainWindowToolsRightLayout = new QGridLayout(mainWindowToolsRightWidget);
    
    //видаляю відступи для компоновщика
    mainWindowToolsRightLayout->setSpacing(0); //відступи між внутрішніми віджетами
    mainWindowToolsRightLayout->setContentsMargins(2, 5, 2, 5); //внутрішні відступи
    //кнопка налаштувань
    QPushButton* setingsButton = new QPushButton("Налаштування", mainWindowToolsRightWidget); setingsButton->setObjectName("setingsButton");
    setingsButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QFont font_tmp;
    font_tmp = setingsButton->font();
    font_tmp.setPointSize(10);
    setingsButton->setFont(font_tmp);

    connect(setingsButton, &QPushButton::released, this, &MainWindow_C::setingsButtonPressed);
    mainWindowToolsRightWidget->setStyleSheet(
        "#mainWindowToolsRightWidget {"
        "   border-radius: 10px;"
        "   background-color: rgb(90,90,90);"
        "}"
    );
    setingsButton->setStyleSheet(
        "#setingsButton {"
        "   border-radius: 5px;"
        "   background-color: rgb(64, 64, 64);"
        "   font-size: 12px;"
        "   margin: 5px;"
        "}"
        "#setingsButton:hover {"
        "   background-color: rgb(120, 120, 120);"
        "}"
        "#setingsButton:focus {"
        "   outline: 0px;"  
        "}"
        "#setingsButton:pressed  {"
        "  background-color: rgb(150, 150, 150);"
        "}"
    );

    mainWindowToolsRightLayout->addWidget(setingsButton, 0, 0, 1, 1);
    parentLayout->addWidget(mainWindowToolsRightWidget, 0, 2); //додаю до компоновщика віджет з кнопкою
}

MainWindow_C::~MainWindow_C() {
    delete this;
}


//кнопка про нас
void MainWindow_C::AboutUsButtonPressed() {
    /////////////////////////////////////////////////////
    //нове вікно про нас 
    /////////////////////////////////////////////////////
    QDialog* settingsWidget = new QDialog();
    QGridLayout* settingsLayout = new QGridLayout(settingsWidget);
    //віджет для пагінації (винесено сюди, щоб у майбутньому його налаштувати )
    settingsLayout->setRowStretch(1, 1);
    QWidget* Pagination = new QWidget(settingsWidget); Pagination->setObjectName("Pagination");
    settingsLayout->addWidget(Pagination, 1, 0);
    QString styleForWidget =
        "#Pagination {"
        "   background-color: rgb(90,90,90);"
        "   border-radius: 10px;"
        "   padding: 10px;"
        "}";
    Pagination->setStyleSheet(styleForWidget);
    //виклик методу який відповідає за відображення вікна про нас (без пагінації, пагінація додається окремо в поточній області видимост див. вище)
    showWindowAboutUs("Images/photo_Gaulun.jpg", "Гайлунь Владислав", "Інтерфейс", "https://github.com/Vlad156763", settingsWidget, settingsLayout);
    
}
//загальне вікно для виведення інформації про нас
void MainWindow_C::showWindowAboutUs(
    const QString& path, 
    const QString& name, 
    const QString& responsible, 
    const QString& linkToGit,
    QDialog* settingsWidget,
    QGridLayout* settingsLayout
) {
    settingsWidget->setWindowTitle("Про нас");
    QIcon mainIcon("Images/title.png");
    settingsWidget->setWindowIcon(mainIcon); // Встановлюю іконку
    settingsLayout->setRowStretch(0, 6);
    QWidget* Body = new QWidget(settingsWidget); Body->setObjectName("Body");
    settingsLayout->addWidget(Body, 0, 0);
    QString styleForWidget =
        "#Body {"
        "   background-color: rgb(90,90,90);"
        "   border-radius: 10px;"
        "   padding: 10px;"
        "}";
    Body->setStyleSheet(styleForWidget);
    // для основного віджету встановлюю компоновщик і два віджети для фото і для тексту
    QGridLayout* bodyLayout = new QGridLayout(Body);
    QWidget* textLocation = new QWidget(Body); textLocation->setObjectName("textLocation");
    textLocation->setStyleSheet(
        "#textLocation {"
        "   background-color: rgb(64, 64, 64);"
        "   font-size: 12px;"
        "   border-radius: 5px;"
        "}"
    );
    //для текстового віджету додаю компоновщик щоб красиво розприділити текст
    QGridLayout* textLayout = new QGridLayout(textLocation);
    //додаю текст
    QLabel* textName = new QLabel("Гайлунь Владислав", textLocation); textName->setObjectName("textName");
    QLabel* textLink = new QLabel(
        " < a href = '" + linkToGit + "' > Github < /a> "
    );
    QLabel* textResponsible = new QLabel("Відповідальний за: " + responsible);
    textName->setStyleSheet(
        "#textName {"
        "   font-weight: bold;"
        "   background-color: rgb(8, 82, 79);"
        "   border-radius: 5px;"
        "   border: 2px solid rgb(23,103,99);"
        "}"
    );
    textLink->setOpenExternalLinks(true); //відкриття зовнішніх посилань
    //налаштовую фото
    QPixmap photoLocationPixmap(path);
    QLabel* photoLabel = new QLabel(Body);  photoLabel->setObjectName("photoLabel");
    photoLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    photoLabel->setAlignment(Qt::AlignCenter);
    /*
    Щоб додати зображення до вікна (і маштабувати його правильно)
    треба отримати розмір мітки, в якій зберігається фото, однак до моменту виклику
    обробника подій exec НЕМОЖЛИВО отримати розмір.
    Тому я додав таймер який спрацює одразу ж як тільки обробник подій до нього дійде.
    Як це працює:
    Коли запускається обробник подій, він запускає таймер на 0 секунд, після того, як таймер
    вийшов, обробник подій виконує код у SetAutoSizeForImg а там автоматичні підлаштування для фото
    */
    auto SetAutoSizeForImg = [photoLabel, photoLocationPixmap]() {
        photoLabel->setPixmap(
            photoLocationPixmap.scaled(
                photoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation
            )
        );
        };
    QTimer::singleShot(0, SetAutoSizeForImg);
    photoLabel->setObjectName("photoLabel");
    photoLabel->setStyleSheet(
        "#photoLabel {"
        "   background-color: rgb(64, 64, 64);"
        "   border-radius: 5px;"
        "   padding: 10px;"
        "}"
    );

    //налаштування дизайну віконечка
    bodyLayout->setRowStretch(0, 4);
    bodyLayout->setRowStretch(1, 1);
    bodyLayout->addWidget(textLocation, 1, 0);
    bodyLayout->addWidget(photoLabel, 0, 0);
    textLayout->addWidget(textName, 0, 0, 1, 2);
    textName->setAlignment(Qt::AlignCenter);
    textLayout->addWidget(textLink, 1, 1);
    textLink->setAlignment(Qt::AlignRight);
    textLayout->addWidget(textResponsible, 1, 0);
    textResponsible->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    //розміри, пам'ять обробка подій
    settingsWidget->setFixedSize(400, 400);
    settingsWidget->setAttribute(Qt::WA_DeleteOnClose); //автоматичне очищення пам'яті
    settingsWidget->exec();
}


void MainWindow_C::HelpButtonPressed() {
    /////////////////////////////////////////////////////
    //нове вікно з допомогою
    /////////////////////////////////////////////////////
    //нове вікно з кнопками для додавання студентів,і для видалення 
    QDialog* settingsWidget = new QDialog();
    QGridLayout* settingsLayout = new QGridLayout(settingsWidget);
    settingsWidget->setWindowTitle("Допомога");
    QIcon mainIcon("Images/title.png");
    settingsWidget->setWindowIcon(mainIcon); // Встановлюю іконку

    settingsWidget->setFixedSize(400, 400);
    settingsWidget->setAttribute(Qt::WA_DeleteOnClose); //автоматичне очищення пам'яті
    settingsWidget->exec();
}

void MainWindow_C::AboutProgramPressed() {
    /////////////////////////////////////////////////////
    //нове вікно про програму (навіщо вона та її функціонал)
    /////////////////////////////////////////////////////
    //нове вікно з кнопками для додавання студентів,і для видалення 
    QDialog* settingsWidget = new QDialog();
    QGridLayout* settingsLayout = new QGridLayout(settingsWidget);
    settingsWidget->setWindowTitle("Про програму");
    QIcon mainIcon("Images/title.png");
    settingsWidget->setWindowIcon(mainIcon); // Встановлюю іконку

    settingsWidget->setFixedSize(400, 400);
    settingsWidget->setAttribute(Qt::WA_DeleteOnClose); //автоматичне очищення пам'яті
    settingsWidget->exec();
}


void MainWindow_C::setingsButtonPressed() {
    //нове вікно з кнопками для додавання студентів,і для видалення 
    QDialog* settingsWidget = new QDialog();
    QGridLayout* settingsLayout = new QGridLayout(settingsWidget);
    settingsWidget->setWindowTitle("Налаштування");
    QIcon mainIcon("Images/title_Setings.png");
    settingsWidget->setWindowIcon(mainIcon); // Встановлюю іконку

    //встановлення стилів
    settingsWidget->setObjectName("settingsWidget");
    settingsWidget->setStyleSheet(
        "#settingsWidget {"
        "   background-color: rgb(30,30,30);"
        "}"
    );
    
    //кнопки
    QString Add_Css =
        "#%1 {"
        "   background-color: rgb(30, 120, 30);"
        "   font-size: 14px;"
        "}"
        "#%1:hover {"
        "   background-color: rgb(40, 140, 40);"  // колір змінюється при наведенні
        "   border-radius: 5px;"
        "}"
        "#%1:focus {"
        "   border-radius: 5px;" 
        "   outline: 0px;"  // Видаляє фокусне виділення        
        "}";
    QPushButton* AddSpecialty = new QPushButton("Додати спеціальність", settingsWidget); AddSpecialty->setObjectName("AddSpecialty");
    QPushButton* AddFaculty = new QPushButton("Додати факультет", settingsWidget); AddFaculty->setObjectName("AddFaculty");
    QPushButton* AddGroup = new QPushButton("Додати групу", settingsWidget); AddGroup->setObjectName("AddGroup");
    QPushButton* AddStudent = new QPushButton("Додати студента", settingsWidget); AddStudent->setObjectName("AddStudent");
    AddSpecialty->setStyleSheet(
        Add_Css.arg("AddSpecialty")
    );
    AddFaculty->setStyleSheet(
        Add_Css.arg("AddFaculty")
    );
    AddGroup->setStyleSheet(
        Add_Css.arg("AddGroup")
    );
    AddStudent->setStyleSheet(
        Add_Css.arg("AddStudent")
    );

    QString Delete_Css =
        "#%1 {"
        "   background-color: rgb(120, 30, 30);"
        "   font-size: 14px;"
        "}"
        "#%1:hover {"
        "   background-color: rgb(140, 40, 40);"  // колір змінюється при наведенні
        "   border-radius: 5px;"

        "}"
        "#%1:focus {"
        "   border-radius: 5px;"
        "   outline: 0px;"  // Видаляє фокусне виділення        
        "}";
    QPushButton* DeleteSpecialty = new QPushButton("Видалити спеціальність", settingsWidget); DeleteSpecialty->setObjectName("DeleteSpecialty");
    QPushButton* DeleteFaculty = new QPushButton("Видалити факультет", settingsWidget); DeleteFaculty->setObjectName("DeleteFaculty");
    QPushButton* DeleteGroup = new QPushButton("Видалити групу", settingsWidget); DeleteGroup->setObjectName("DeleteGroup");
    QPushButton* DeleteStudent = new QPushButton("Видалити студента", settingsWidget); DeleteStudent->setObjectName("DeleteStudent");
    DeleteSpecialty->setStyleSheet(
        Delete_Css.arg("DeleteSpecialty")
    );
    DeleteFaculty->setStyleSheet(
        Delete_Css.arg("DeleteFaculty")
    );
    DeleteGroup->setStyleSheet(
        Delete_Css.arg("DeleteGroup")
    );
    DeleteStudent->setStyleSheet(
        Delete_Css.arg("DeleteStudent")
    );
    //політика зміни розмірів для кнопок
    AddSpecialty->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    AddFaculty->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    AddGroup->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    AddStudent->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    DeleteSpecialty->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    DeleteFaculty->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    DeleteGroup->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    DeleteStudent->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    //слоти для обробки сигналів натиску на кнопки "додати"
    connect(AddStudent, &QPushButton::released, this, &MainWindow_C::AddStudentButtonPressed);
    connect(AddGroup, &QPushButton::released, this, &MainWindow_C::AddGroupButtonPressed);
    connect(AddFaculty, &QPushButton::released, this, &MainWindow_C::AddFacultyButtonPressed);
    connect(AddSpecialty, &QPushButton::released, this, &MainWindow_C::AddSpecialtyButtonPressed);
    //слоти для обробки сигналів натиску на кнопки "видалити"
    connect(DeleteStudent, &QPushButton::released, this, &MainWindow_C::DeleteStudentButtonPressed);
    connect(DeleteGroup, &QPushButton::released, this, &MainWindow_C::DeleteGroupButtonPressed);
    connect(DeleteFaculty, &QPushButton::released, this, &MainWindow_C::DeleteFacultyButtonPressed);
    connect(DeleteSpecialty, &QPushButton::released, this, &MainWindow_C::DeleteSpecialtyButtonPressed);
    
    //додавання кнопок у головний компоновщик
    settingsLayout->addWidget(AddSpecialty, 0, 0, 1, 1);
    settingsLayout->addWidget(AddFaculty, 1, 0, 1, 1);
    settingsLayout->addWidget(AddGroup, 2, 0, 1, 1);
    settingsLayout->addWidget(AddStudent, 3, 0, 1, 1);
    settingsLayout->addWidget(DeleteSpecialty, 0, 1, 1, 1);
    settingsLayout->addWidget(DeleteFaculty, 1, 1, 1, 1);
    settingsLayout->addWidget(DeleteGroup, 2, 1, 1, 1);
    settingsLayout->addWidget(DeleteStudent, 3, 1, 1, 1);

    settingsWidget->setFixedSize(this->width() / 3, this->height() / 3 ); //розмір форми підлаштовується під розміри вікна 
    settingsWidget->setModal(true);//встановлюю модальне вікно як правду (це для того, щоб головне вікно було заблоковане
    settingsWidget->setAttribute(Qt::WA_DeleteOnClose); //автоматичне очищення пам'яті
    settingsWidget->exec();
}

void MainWindow_C::AddStudentButtonPressed() {
    /*
    Коли слот викликаний у відповідь на сигнал,  я за допомогою sender можу отримати покажчик
    на об'єкт який надіслав сигнал (а для цього об'єкту батьком є головний віджет)
    тому отримавши покажчик, я закриваю форму з налаштуваннями, і відкриваю форму з додаваням студента
    */
    QDialog* settingsWidget = qobject_cast<QDialog*>(sender()->parent());
    if (settingsWidget) settingsWidget->accept(); // Закриваю вікно налаштувань

    QDialog* settingsWidgetAddStydentWidget = new QDialog();
    settingsWidgetAddStydentWidget->setAttribute(Qt::WA_DeleteOnClose);
    QIcon mainIcon("Images/Add_icon.png");
    settingsWidgetAddStydentWidget->setWindowIcon(mainIcon); // Встановлюю іконку

    /*
    Лямбда функція для виклику специфічних методів збереження 
    От наприклад треба зберегти дані про студента це 4 методи, але якщо 
    зберети дані про групу, це тільки 3 методи, тому для кожного додавання
    треба окремий метод щоб правильно зберігати все в бд
    */
    auto saveAction = [this, settingsWidgetAddStydentWidget]() {
        this->SaveButtonFor_AddStudent(settingsWidgetAddStydentWidget);
        };

    WindowAdd_and_Delete_All_Type(
        settingsWidgetAddStydentWidget,
        "Додати студента",
        "Зберегти",
        {"Спеціальність:", "Факультет:", "Група:","Студент:"},
        {"InputSpecialty", "InputFaculty", "InputGroup", "InputStudent"},
        saveAction
    );
}
void MainWindow_C::AddGroupButtonPressed() {
    QDialog* settingsWidget = qobject_cast<QDialog*>(sender()->parent());
    if (settingsWidget) settingsWidget->accept(); // Закриваю вікно налаштувань

    QDialog* settingsWidgetAddStydentWidget = new QDialog();
    settingsWidgetAddStydentWidget->setAttribute(Qt::WA_DeleteOnClose);
    QIcon mainIcon("Images/Add_icon.png");
    settingsWidgetAddStydentWidget->setWindowIcon(mainIcon); // Встановлюю іконку
    auto saveAction = [this, settingsWidgetAddStydentWidget]() {
        this->SaveButtonFor_AddGroup(settingsWidgetAddStydentWidget);
        };

    WindowAdd_and_Delete_All_Type(
        settingsWidgetAddStydentWidget,
        "Додати групу",
        "Зберегти",
        { "Спеціальність:", "Факультет:", "Група:" },
        { "InputSpecialty", "InputFaculty", "InputGroup" },
        saveAction
    );
}
void MainWindow_C::AddFacultyButtonPressed() {
    QDialog* settingsWidget = qobject_cast<QDialog*>(sender()->parent());
    if (settingsWidget) settingsWidget->accept(); // Закриваю вікно налаштувань

    QDialog* settingsWidgetAddStydentWidget = new QDialog();
    settingsWidgetAddStydentWidget->setAttribute(Qt::WA_DeleteOnClose);
    QIcon mainIcon("Images/Add_icon.png");
    settingsWidgetAddStydentWidget->setWindowIcon(mainIcon); // Встановлюю іконку
    auto saveAction = [this, settingsWidgetAddStydentWidget]() {
        this->SaveButtonFor_AddFaculty(settingsWidgetAddStydentWidget);
        };

    WindowAdd_and_Delete_All_Type(
        settingsWidgetAddStydentWidget,
        "Додати факультет",
        "Зберегти",
        { "Спеціальність:", "Факультет:" },
        { "InputSpecialty", "InputFaculty" },
        saveAction
    );
}
void MainWindow_C::AddSpecialtyButtonPressed() {
    QDialog* settingsWidget = qobject_cast<QDialog*>(sender()->parent());
    if (settingsWidget) settingsWidget->accept(); // Закриваю вікно налаштувань

    QDialog* settingsWidgetAddStydentWidget = new QDialog();
    settingsWidgetAddStydentWidget->setAttribute(Qt::WA_DeleteOnClose);
    QIcon mainIcon("Images/Add_icon.png");
    settingsWidgetAddStydentWidget->setWindowIcon(mainIcon); // Встановлюю іконку
    auto saveAction = [this, settingsWidgetAddStydentWidget]() {
        this->SaveButtonFor_AddSpecialty(settingsWidgetAddStydentWidget);
        };

    WindowAdd_and_Delete_All_Type(
        settingsWidgetAddStydentWidget,
        "Додати спеціальність",
        "Зберегти",
        { "Спеціальність:"},
        { "InputSpecialty" },
        saveAction
    );
}
void MainWindow_C::DeleteStudentButtonPressed() {
    QDialog* settingsWidget = qobject_cast<QDialog*>(sender()->parent());
    if (settingsWidget) settingsWidget->accept(); // Закриваю вікно налаштувань

    QDialog* settingsWidgetAddStydentWidget = new QDialog();
    settingsWidgetAddStydentWidget->setAttribute(Qt::WA_DeleteOnClose);
    QIcon mainIcon("Images/Delete_icon.png");
    settingsWidgetAddStydentWidget->setWindowIcon(mainIcon); // Встановлюю іконку
    auto saveAction = [this, settingsWidgetAddStydentWidget]() {
        this->DeleteButtonFor_DeleteStudent(settingsWidgetAddStydentWidget);
        };

    WindowAdd_and_Delete_All_Type(
        settingsWidgetAddStydentWidget,
        "Видалити студента",
        "Видалити",
        { "Спеціальність:", "Факультет:", "Група:","Студент:" },
        { "InputSpecialty", "InputFaculty", "InputGroup", "InputStudent" },
        saveAction
    );
}
void MainWindow_C::DeleteGroupButtonPressed() {
    QDialog* settingsWidget = qobject_cast<QDialog*>(sender()->parent());
    if (settingsWidget) settingsWidget->accept(); // Закриваю вікно налаштувань

    QDialog* settingsWidgetAddStydentWidget = new QDialog();
    settingsWidgetAddStydentWidget->setAttribute(Qt::WA_DeleteOnClose);
    QIcon mainIcon("Images/Delete_icon.png");
    settingsWidgetAddStydentWidget->setWindowIcon(mainIcon); // Встановлюю іконку
    auto saveAction = [this, settingsWidgetAddStydentWidget]() {
        this->DeleteButtonFor_DeleteGroup(settingsWidgetAddStydentWidget);
        };

    WindowAdd_and_Delete_All_Type(
        settingsWidgetAddStydentWidget,
        "Видалити групу",
        "Видалити",
        { "Спеціальність:", "Факультет:", "Група:" },
        { "InputSpecialty", "InputFaculty", "InputGroup" },
        saveAction
    );
}
void MainWindow_C::DeleteFacultyButtonPressed() {
    QDialog* settingsWidget = qobject_cast<QDialog*>(sender()->parent());
    if (settingsWidget) settingsWidget->accept(); // Закриваю вікно налаштувань

    QDialog* settingsWidgetAddStydentWidget = new QDialog();
    settingsWidgetAddStydentWidget->setAttribute(Qt::WA_DeleteOnClose);
    QIcon mainIcon("Images/Delete_icon.png");
    settingsWidgetAddStydentWidget->setWindowIcon(mainIcon); // Встановлюю іконку
    auto saveAction = [this, settingsWidgetAddStydentWidget]() {
        this->DeleteButtonFor_DeleteFaculty(settingsWidgetAddStydentWidget);
        };

    WindowAdd_and_Delete_All_Type(
        settingsWidgetAddStydentWidget,
        "Видалити факультет",
        "Видалити",
        { "Спеціальність:", "Факультет:" },
        { "InputSpecialty", "InputFaculty" },
        saveAction
    );
}
void MainWindow_C::DeleteSpecialtyButtonPressed() {

    QDialog* settingsWidget = qobject_cast<QDialog*>(sender()->parent());
    if (settingsWidget) settingsWidget->accept(); // Закриваю вікно налаштувань

    QDialog* settingsWidgetAddStydentWidget = new QDialog();
    settingsWidgetAddStydentWidget->setAttribute(Qt::WA_DeleteOnClose);
    QIcon mainIcon("Images/Delete_icon.png");
    settingsWidgetAddStydentWidget->setWindowIcon(mainIcon); // Встановлюю іконку
    auto saveAction = [this, settingsWidgetAddStydentWidget]() {
        this->DeleteButtonFor_DeleteІSpetialty(settingsWidgetAddStydentWidget);
        };

    WindowAdd_and_Delete_All_Type(
        settingsWidgetAddStydentWidget,
        "Видалити спеціальність",
        "Видалити",
        { "Спеціальність:" },
        { "InputSpecialty" },
        saveAction
    );
}

void MainWindow_C::SaveButtonFor_AddSpecialty(QDialog* dialog) {
    // Лямбда-функція для дій з БД спеціальність
    auto dbAction = [this](vector<QString> AllLineEdits) {
        ///////////////////////////////////////////////////// 
        //додати факултет до БД
        // у векторі  AllLineEdits зберігаюсься рядки 
        // [0] - Спеціальність
        // [1] - Факультет
        /////////////////////////////////////////////////////
        //це вивід у консоль для демонстраії
        cqdout << "Додати спеціальність ";
        for (int i = 0; i < AllLineEdits.size(); i++)
            cqdout << "\t" << AllLineEdits[i];
        };
    // Викликаю загальний метод 
    SaveButtonFor_AllType(dialog, "Успішно Додано!", "8, 82, 79", dbAction, { "InputSpecialty" });
}
void MainWindow_C::SaveButtonFor_AddFaculty(QDialog* dialog) {
    // Лямбда-функція для дій з БД (додати факультет)
    auto dbAction = [this](vector<QString> AllLineEdits) {
        ///////////////////////////////////////////////////// 
        //додати факултет до БД
        // у векторі  AllLineEdits зберігаюсься рядки 
        // [0] - Спеціальність
        // [1] - Факультет
        /////////////////////////////////////////////////////
        //це вивід у консоль для демонстраії
        cqdout << "Додати факультет";
        for (int i = 0; i < AllLineEdits.size(); i++)
            cqdout << "\t" << AllLineEdits[i];
        };
    // Викликаю загальний метод 
    SaveButtonFor_AllType(dialog, "Успішно Додано!", "8, 82, 79", dbAction, { "InputSpecialty", "InputFaculty" });
}
void MainWindow_C::SaveButtonFor_AddGroup(QDialog* dialog) {
    // Лямбда-функція для дій з БД (додати групу)
    auto dbAction = [this](vector<QString> AllLineEdits) {
        /////////////////////////////////////////////////////
        //МОМЕНТО! Спочатку йде пошук по БД чи має вона таку спеціальність, факультет, групу, та студента, якщо має - помилка додавання
        // Якщо не має наприклад спеціальності такої, то створюється спеціальність, факултет, група, і студент.
        // 
        //додати групу до БД
        // у векторі  AllLineEdits зберігаюсься рядки 
        // [0] - Спеціальність
        // [1] - Факультет
        // [2] - Група
        /////////////////////////////////////////////////////
        //це вивід у консоль для демонстраії
        cqdout << "Додати групу";
        for (int i = 0; i < AllLineEdits.size(); i++)
            cqdout << "\t" << AllLineEdits[i];
        };
    // Викликаю загальний метод 
    SaveButtonFor_AllType(dialog, "Успішно Додано!", "8, 82, 79", dbAction, { "InputSpecialty", "InputFaculty", "InputGroup" });
}
void MainWindow_C::SaveButtonFor_AddStudent(QDialog* dialog) {
    // Лямбда-функція для дій з БД (додати студента)
    auto dbAction = [this](vector<QString> AllLineEdits) {
        /////////////////////////////////////////////////////
        //додати студента до БД
        // у векторі  AllLineEdits зберігаюсься рядки 
        // [0] - Спеціальність
        // [1] - Факультет
        // [2] - Група
        // [3] - ПІБ
        /////////////////////////////////////////////////////
        //це вивід у консоль для демонстраії
        cqdout << "Додати студента";
        for (int i = 0; i < AllLineEdits.size(); i++)
            cqdout << "\t" << AllLineEdits[i];
        };
    // Викликаю загальний метод 
    SaveButtonFor_AllType(dialog, "Успішно Додано!", "8, 82, 79", dbAction, {"InputSpecialty", "InputFaculty", "InputGroup", "InputStudent"});
}

void MainWindow_C::DeleteButtonFor_DeleteStudent(QDialog* dialog) {
    // Лямбда-функція для дій з БД (видалити студента)
    auto dbAction = [this](vector<QString> AllLineEdits) {
        /////////////////////////////////////////////////////
        //видалити студента з БД
        // у векторі  AllLineEdits зберігаюсься рядки 
        // [0] - Спеціальність
        // [1] - Факультет
        // [2] - Група
        // [3] - ПІБ
        /////////////////////////////////////////////////////
        //це вивід у консоль для демонстраії
        cqdout << "Видалено студента";
        for (int i = 0; i < AllLineEdits.size(); i++)
            cqdout << "\t" << AllLineEdits[i];
        };
    // Викликаю загальний метод 
    SaveButtonFor_AllType(dialog,"Успіншо видалено!", "169, 38, 38", dbAction, { "InputSpecialty", "InputFaculty", "InputGroup", "InputStudent" });
}
void MainWindow_C::DeleteButtonFor_DeleteGroup(QDialog* dialog) {
    // Лямбда-функція для дій з БД (Видалити групу)
    auto dbAction = [this](vector<QString> AllLineEdits) {
        /////////////////////////////////////////////////////
        //видалити групу з БД 
        // у векторі  AllLineEdits зберігаюсься рядки 
        // [0] - Спеціальність
        // [1] - Факультет
        // [2] - Група
        /////////////////////////////////////////////////////
        //це вивід у консоль для демонстраії
        cqdout << "Видалено групу";
        for (int i = 0; i < AllLineEdits.size(); i++)
            cqdout << "\t" << AllLineEdits[i];
        };
    // Викликаю загальний метод 
    SaveButtonFor_AllType(dialog, "Успіншо видалено!", "169, 38, 38", dbAction, { "InputSpecialty", "InputFaculty", "InputGroup" });
}
void MainWindow_C::DeleteButtonFor_DeleteFaculty(QDialog* dialog) {
    // Лямбда-функція для дій з БД (додати студента)
    auto dbAction = [this](vector<QString> AllLineEdits) {
        /////////////////////////////////////////////////////
        //видалити факультет з БД 
        // у векторі  AllLineEdits зберігаюсься рядки 
        // [0] - Спеціальність
        // [1] - Факультет
        /////////////////////////////////////////////////////
        //це вивід у консоль для демонстраії
        cqdout << "Видалено факультет";
        for (int i = 0; i < AllLineEdits.size(); i++)
            cqdout << "\t" << AllLineEdits[i];
        };
    // Викликаю загальний метод 
    SaveButtonFor_AllType(dialog, "Успіншо видалено!", "169, 38, 38", dbAction, { "InputSpecialty", "InputFaculty" });

}
void MainWindow_C::DeleteButtonFor_DeleteІSpetialty(QDialog* dialog) {
    auto dbAction = [this](vector<QString> AllLineEdits) {
        /////////////////////////////////////////////////////
        //видалити спеціальність з БД 
        // у векторі  AllLineEdits зберігаюсься рядки 
        // [0] - Спеціальність
        /////////////////////////////////////////////////////
        //це вивід у консоль для демонстраії
        cqdout << "Видалено cпеціальність";
        for (int i = 0; i < AllLineEdits.size(); i++)
            cqdout << "\t" << AllLineEdits[i];
        };
    // Викликаю загальний метод 
    SaveButtonFor_AllType(dialog, "Успіншо видалено!", "169, 38, 38", dbAction, { "InputSpecialty" });
}

template<typename LaFunc> 
void MainWindow_C::SaveButtonFor_AllType(QDialog* dialog, const QString& text, const QString& color, LaFunc dbAction, const QStringList& fieldNames) {
    //створення вектора для запису у БД всіх полів
    vector<QString> AllLineEdits;
    AllLineEdits.reserve(fieldNames.size());//резервні місця під текст
        
    // Перевірка полів за допомогою ітератора
    // Перевіряємо, чи є діти
    for (const QString& fieldName : fieldNames) { //проходжусь по кожній комірці списку 
        QLineEdit* lineEdit = dialog->findChild<QLineEdit*>(fieldName); 
        if (lineEdit == nullptr || lineEdit->text().isEmpty()) { //якщо дитина з такою унікальною назовю знайдена і пуста - попередження
            QMessageBox::warning(dialog, "Попередження", "Заповніть всі поля!");
            return;
        }
        AllLineEdits.push_back(lineEdit->text()); //записую текст з полів у вектор
    }
    // Виконання дії з базою даних(і передаю їй вектор з полями які ввів користувач)
    dbAction(AllLineEdits);
    dialog->accept(); // Закриваю діалог
    // повідомлення про успіх
    SmallMessage_C* smallMessage = new SmallMessage_C(this);
    smallMessage->show(text, color, this->mainLayout);
}

template<typename LaFunc>

void MainWindow_C::WindowAdd_and_Delete_All_Type(QDialog* dialog, const QString& title, const QString& textButton,  const QStringList& labels, const QStringList& objectNames,  LaFunc saveAction) {
    dialog->setFixedWidth(this->width() / 5);
    dialog->setWindowTitle(title);
    dialog->setObjectName("dialog");
    QGridLayout* layout = new QGridLayout(dialog);
    dialog->setModal(true);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    //створюю рядки для вводу, мітки для тексту, вказую для рядків унікальний тип, додаю це все до компоновщика
    for (int i = 0; i < labels.size(); ++i) {
        QLabel* label = new QLabel(labels[i], dialog); //створюю мітку з текстом із параметру
        QLineEdit* lineEdit = new QLineEdit(dialog); //створюю рдок для введнення
        lineEdit->setObjectName(objectNames[i]); //встановлюю унікальне ім'я для рядка введення (це для пошуку та перевірки чи вони не пусті)
        layout->addWidget(label, i, 0);//додаю до компоновщика мітки та рядки
        layout->addWidget(lineEdit, i, 1);
    }
    QPushButton* saveButton = new QPushButton(textButton, dialog); saveButton->setObjectName("saveButton");

    dialog->setStyleSheet(
        "#dialog {"
        "   background-color: rgb(30,30,30);"
        "}"
    );
    saveButton->setStyleSheet(
        "#saveButton {"
        "   border-radius: 5px;"
        "   background-color: rgb(64, 64, 64);"
        "}"
        "#saveButton:hover {"
        "   background-color: rgb(120, 120, 120);"
        "}"
        "#saveButton:focus {"
        "   outline: 0px;"
        "}"
        "#saveButton:pressed  {"
        "  background-color: rgb(150, 150, 150);"
        "}"
    );
    connect(saveButton, &QPushButton::released, [this, dialog, saveAction]() {
        saveAction(); // викликає функцію для кнопки збереження
        });
    layout->addWidget(saveButton, labels.size(), 0, 1, 2);
    layout->setAlignment(Qt::AlignTop);
    dialog->exec();
 }


END_ClASS_MAIN_WINDOW;


START_CLASS_SMALL_MESSAGE;
SmallMessage_C::SmallMessage_C(QWidget* parent) : QWidget(parent) {}
void SmallMessage_C::show(const QString& text, const QString& color, QGridLayout* layout) {
    layout->addWidget(this);
    QLabel* label = new QLabel(text, this);
    label->setObjectName("label"); //унікальна назва для CSS
    label->setFixedSize(200, 50); //фіксований розмір
    label->setStyleSheet(
        QString(
            "#label {"
            "   background-color: rgb( %1 ); "
            "   color: white;"
            "   border-radius: 10px;"
            "   padding: 11px;"
            "   font-size: 14px;"
            "}"
        ).arg(color)
    );
    //вирівнювання тексту
    label->setAlignment(Qt::AlignCenter);
    //вирівнювання віджету
    layout->addWidget(label, 1, 0, 1, 1, Qt::AlignBottom | Qt::AlignRight);
    //піднімаю віджет поверх інших
    label->raise();
    QTimer* timer = new QTimer(this); //таймер 
    //підключаю сигнал закінчення таймеру до лямбда функції яка видалить label
    connect(timer, &QTimer::timeout, [label]() { delete label; });
    //таймер для запуску один раз
    timer->setSingleShot(true);
    timer->start(3000); //запуск на 3 секунди
}
END_CLASS_SMALL_MESSAGE;
//QGridLayout* layout


