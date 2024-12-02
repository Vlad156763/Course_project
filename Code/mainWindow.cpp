#include "mainWindow.h"
#include "ex.h"

//#ifdef Q_OS_WIN
//#include <Windows.h>
//static void createConsole() {
//    if (GetConsoleWindow() == nullptr) {
//        AllocConsole(); // Створюю вікно консолі 
//        FILE* stream;
//        freopen_s(&stream, "CONOUT$", "w", stdout); // Перенаправляю stdout у консоль
//        freopen_s(&stream, "CONOUT$", "w", stderr); // Перенаправляю stderr у консоль
//    }
//    else cerr << "Консоль запущена!\n";
//}
//#endif // Q_OS_WIN

MainWindow_C::MainWindow_C(QWidget* parent) : QWidget(parent) {
    //createConsole();
    //встановлення таймеру
    try {
        QIcon mainIcon("Images/title.png"); // Іконка для вікна програми
        QDir imagesDir("Images"); // Директорія Images
        if (!imagesDir.exists()) {
            throw ex(1);
        }
        QString photoNames[16]{
            "Add_icon.png",
            "arrowL.png",
            "arrowR.png",
            "Delete_icon.png",
            "IvanBondarenko.jpg",
            "load.gif",
            "photo_Gaulun.jpg",
            "RodionShevchenko.jpg",
            "sashaTretiak.jpg",
            "searchIcon.png",
            "sortDOWN.png",
            "sortUP.png",
            "title.png",
            "title_Setings.png",
            "vladMamont.jpg",
            "warning.png"
        };
        for (int i = 0; i < 16; i++) {
            if (QIcon("Images/"+ photoNames[i]).isNull()) {
                throw ex(2);
            }
        }
        this->setWindowIcon(mainIcon); // Встановлюю іконку
        //віджети для інструментів та для головної частини
        this->TimersCounter = new counterTimer();
        this->SandSBlocks = new SandS();
        //присворюю до змінної встановлення стилів
        this->setObjectName("mainWidget");
        this->setStyleSheet(
            "#mainWidget {"
            "   background-color: rgb(30,30,30);"
            "}"
        );
        this->mainLayout = new QGridLayout(this);
        this->mainLayout->setSpacing(5);
        this->mainLayout->setContentsMargins(10, 10, 10, 10);
        this->setWindowTitle("Успішність студентів");

        QWidget* mainWindowToolsWidget = new QWidget(this);
        QWidget* mainWindowMainAreaWidget = new QWidget(this);
        //компоновщики для інструментальної та для головної частин
        QGridLayout* mainWindowToolsLayout = new QGridLayout(mainWindowToolsWidget);
        QGridLayout* mainWindownMainAreaLayout = new QGridLayout(mainWindowMainAreaWidget);
        //віджети головної частини
        QWidget* mainWindowAreaWidgetMiddle = new QWidget(mainWindowMainAreaWidget);
        QWidget* mainWindowAreaWidgetRight = new QWidget(mainWindowMainAreaWidget);

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
        ToolsMiddleWidget(mainWindowToolsWidget, mainWindowToolsLayout);

        //викликаю метод для роботи з головною частиною
        mainWidgetArea(mainWindowToolsWidget, mainWindownMainAreaLayout, *mainWindowMainAreaWidget);

        QString styleWidgets =
            "   border-radius: 10px;"
            "   background-color: rgb(90,90,90);";
        mainWindowAreaWidgetMiddle->setStyleSheet(styleWidgets);
        mainWindowAreaWidgetRight->setStyleSheet(styleWidgets);
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
        this->update();
        this->showMaximized();
    }
    catch (ex& error) {
        auto showErrorDialog = [this](const char* msg) {
            QLabel* iconLabel = new QLabel();
            iconLabel->setPixmap(this->style()->standardIcon(QStyle::SP_MessageBoxCritical).pixmap(40, 40));

            QGridLayout* layout = new QGridLayout(this);
            this->setObjectName("this");
            this->setStyleSheet(
                "#this {"
                "   color: rgb(255,255,255);"
                "   background-color: rgb(30,30,30);"
                "}"
            );
            this->setWindowTitle("Помилка");
            //текст
            QLabel* textLabel = new QLabel(msg, this);
            textLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
            textLabel->setObjectName("textLabel");
            textLabel->setStyleSheet(
                "#textLabel {"
                "   color: #ffffff;"
                "}"
            );
            iconLabel->setParent(this);
            iconLabel->setAlignment(Qt::AlignCenter);
            //кнопка
            QPushButton* button = new QPushButton("Ок", this);
            button->setObjectName("button");
            button->setStyleSheet(
                "#button {"
                "   color: rgb(255,255,255);"
                "   background-color: rgb(60,60,60);"
                "}"
                "#button:focus {"
                "   outline: 0px;"  // Видаляє фокусне виділення        
                "}"
            );
            button->setFixedSize(75, 25);
            connect(button, &QPushButton::released, [this]() {
                this->close();
                }
            );
            //додаю віджети у сітку
            layout->setColumnStretch(0, 1);
            layout->setColumnStretch(1, 2);
            layout->addWidget(iconLabel, 0, 0);
            layout->addWidget(textLabel, 0, 1);
            layout->addWidget(button, 1, 1, 1, 2, Qt::AlignRight);
            this->setFixedHeight(100);
            this->show();
        };
        if (error.getErrorCode() == 1) {
            showErrorDialog("Перевстановіть програму!\nКаталог з фото незнайдено!");
        }
        else if (error.getErrorCode() == 2) {
            showErrorDialog("Перевстановіть програму!\nДеякі фото пошкоджені або видалені!");
        }  
    }  
}
MainWindow_C::~MainWindow_C() {
delete this->TimersCounter;
this->close();
delete this->SandSBlocks;
}

void MainWindow_C::ToolsMiddleWidget(QWidget* parentWidget, QGridLayout* parentLayout) {
    QWidget* mainWindowToolsMiddle = new QWidget(parentWidget);
    QGridLayout* mainWindowToolsMiddleLayout = new QGridLayout(mainWindowToolsMiddle);
    QString styleWidgets =
        "   border-radius: 10px;"
        "   background-color: rgb(90,90,90);";
    mainWindowToolsMiddle->setStyleSheet(styleWidgets);
    parentLayout->addWidget(mainWindowToolsMiddle, 0, 1);


    QLabel* iconSearch = new QLabel(mainWindowToolsMiddle);
    QLineEdit* lineEdit = new QLineEdit(mainWindowToolsMiddle);
    lineEdit->setFixedHeight(40);
    lineEdit->setStyleSheet(
        "QLineEdit {"
        "   background-color: rgb(70,70,70);"
        "   border-radius: 5px;"
        "   color: #ffffff;"
        "   font-size: 20px;"
        "   padding: 5px;"
        "}"
    );
    /*
    QString SpecialtyName = "1";
QString FacultyName = "2";
QString GroupName = "3";
QString StudyName = "4";

    */
    auto is_correct = [](QLineEdit* lineEdit)->bool {
        QRegularExpression regex(R"(^s:\s*+[0-9A-Za-zа-яА-ЯєЄіІїЇґҐ \`\'\"\-\_]+\s*f:\s*[0-9A-Za-zа-яА-ЯєЄіІїЇґҐ \`\'\"\-\_]+\s*g:\s*[0-9A-Za-zа-яА-ЯєЄіІїЇґҐ \`\'\"\-\_]+\s*n:\s*[0-9A-Za-zа-яА-ЯєЄіІїЇґҐ \`\'\"\-\_]+\s*$)");
        QString text = lineEdit->text();
        return regex.match(text).hasMatch();
        };
    QObject::connect(lineEdit, &QLineEdit::returnPressed, [is_correct, lineEdit, mainWindowToolsMiddle, mainWindowToolsMiddleLayout, this]() {
        try {
            if (!is_correct(lineEdit)) { throw ex(0); };
            QString StudyName, GroupName, FacultyName, SpecialtyName;
            //todo: запит на отримання предметів студента за спеціальністю, факультетом, групою і піб
            QWidget* PredmetBox;
            blockWidget* tmp = new blockWidget(mainWindowToolsMiddle);
            QDialog* dialog = tmp->setDialogForPredmet(StudyName, GroupName, FacultyName, SpecialtyName, &PredmetBox);
            configBlock block;
            block.setWidget(PredmetBox);
            block.setLayout(PredmetBox->layout());
            block.setConfigPredmetBlock(
                [this, SpecialtyName, FacultyName, GroupName, StudyName, tmp, PredmetBox, block](QGridLayout* layout, QWidget* widget)->bool {
                    //SandSBlocks
                    ///////////////////////////////////////////////////////////////////////////////////////////////////
                    //HERE: відбувається поступове отримання предметів за спеціальністю, факульетом, групою, Піб студента (значення спеціальність, факультет можуть бути пусті) із об'єкта SandSBlocks за допомогою counter            
                    static int counter = 0;
                    QString PredmetName = "Предмети";
                    if (counter++ >= 3) { counter = 0; return true; }
                    ///////////////////////////////////////////////////////////////////////////////////////////////////
                    blockWidget* block = new blockWidget(PredmetName, PredmetBox);
                    connect(block, &QPushButton::released, [this, block, SpecialtyName, FacultyName, GroupName, StudyName, PredmetName]() {
                        block->PredmetButtonPressed(SpecialtyName, FacultyName, GroupName, StudyName, PredmetName);
                        });

                    block->AddStructure();
                    layout->addWidget(block, counter++ + 1, 0);
                    return false;
                },
                PredmetBox,
                "Предмети"
            );
            dialog->exec();
        }
        catch (ex& error) {
            auto TextInLineEditIsWrong = [this](const char* msg) {
                QLabel* iconLabel = new QLabel();
                iconLabel->setPixmap(this->style()->standardIcon(QStyle::SP_MessageBoxWarning).pixmap(40, 40));
                iconLabel->setAttribute(Qt::WA_DeleteOnClose);
                WarningDialog warning(this, msg, "Попередження", "Images/warning.png", iconLabel, "Ок");
                warning.show();
                };
            if (error.getErrorCode() == 0) {
                TextInLineEditIsWrong("Введено неправильний запит!");
            }
        }  
    });
    iconSearch->setPixmap(QPixmap("Images/searchIcon.png").scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    mainWindowToolsMiddleLayout->addWidget(iconSearch, 0, 0);
    mainWindowToolsMiddleLayout->addWidget(lineEdit, 0, 1);
}
void MainWindow_C::leftSideToolsWidget(QWidget* parentWidget, QGridLayout* parentLayout)  {
    //віджет і компоновщик
    QWidget* mainWindowToolsLeftWidget = new QWidget(parentWidget); mainWindowToolsLeftWidget->setObjectName("mainWindowToolsLeftWidget");
    QGridLayout* mainWindowToolsLeftLayout = new QGridLayout(mainWindowToolsLeftWidget);
    //видаляю відступи для компоновщика
    mainWindowToolsLeftLayout->setSpacing(0); //відступи між внутрішніми віджетами
    mainWindowToolsLeftLayout->setContentsMargins(2, 5, 2, 5); //внутрішні відступи
    //кнопки
    QPushButton* aboutUsButton = new QPushButton("Про нас", mainWindowToolsLeftWidget);
    QPushButton* helpButton = new QPushButton("Допомога", mainWindowToolsLeftWidget);


    //встановлення розтягування
    mainWindowToolsLeftLayout->setColumnStretch(0, 3);
    mainWindowToolsLeftLayout->setColumnStretch(1, 3);
    //встановлення політики (як воно себе поводитиме)
    aboutUsButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    helpButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    //прикріплення сигналів натиску на кнопку зі слотами обробки
    connect(aboutUsButton, &QPushButton::released, this, &MainWindow_C::AboutUsButtonPressed);
    connect(helpButton, &QPushButton::released, this, &MainWindow_C::HelpButtonPressed);
    //встановюю назви об'єктів (однакові) для кнопок
    aboutUsButton->setObjectName("customButton");
    helpButton->setObjectName("customButton");
    //встановлення стилів
    QString buttonStyle =
        "#customButton {"
        "   border-radius: 5px;"
        "   background-color: rgb(64, 64, 64);"
        "   font-size: 12px;"
        "   margin: 5px;"
        "   padding: 5px;"
        "   color: rgb(255, 255, 255);"
        "   font-weight: bold;"
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
    helpButton->setStyleSheet(buttonStyle);
    aboutUsButton->setStyleSheet(buttonStyle);
    mainWindowToolsLeftLayout->addWidget(aboutUsButton, 0, 0, 1, 1);
    mainWindowToolsLeftLayout->addWidget(helpButton, 0, 1, 1, 1);

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
        "   color: rgb(255,255,255);"
        "   background-color: rgb(64, 64, 64);"
        "   font-size: 12px;"
        "   font-weight: bold;"
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
void MainWindow_C::mainWidgetArea(QWidget* parent, QGridLayout* parent_grid, QWidget& mainWedgetTools) {
    cqdout << "Вивід шляху відбувається так: (Спеціальність) (Факультет) (Група) (Студент) (Предмет)";
    auto CSS = [](QWidget* widget, const QString& string) {
        widget->setStyleSheet(
            QString(
                "#%1 {"
                "   border-radius: 10px;"
                "   background-color: rgb(90,90,90);"
                "}"
            ).arg(string)
        );
       
    };
    QWidget* LeftSide = new QWidget(parent); LeftSide->setObjectName("LeftSide"); CSS(LeftSide, "LeftSide");
    QWidget* MiddleSide = new QWidget(parent); MiddleSide->setObjectName("MiddleSide"); CSS(MiddleSide, "MiddleSide");
    QWidget* RightSide = new QWidget(parent); RightSide->setObjectName("RightSide"); CSS(RightSide, "RightSide");
    //сітки для віджетів з блоками
    QGridLayout* LeftSideLayout = new QGridLayout(LeftSide);
    QGridLayout* MiddleSideLayout = new QGridLayout(MiddleSide);
    QGridLayout* RightSideLayout = new QGridLayout(RightSide);
    //HERE: зчитування всіх: спеціальностей, факультетів, груп, студентів, предметів, з БД і запис у масиви класу sortBlock
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    QStringList specialties = initializeSpecialties(query);
    QStringList faculties = initializeFaculties(query);
    QStringList classGroups = initializeClassGroups(query);
    QStringList students = initializeStudents(query);
    QStringList predmets = initializePredmets(query);

    qDebug() << "Specialties:" << specialties;
    qDebug() << "Faculties:" << faculties;
    qDebug() << "Class Groups:" << classGroups;
    qDebug() << "Students:" << students;
    qDebug() << "Predmets:" << predmets;

    //підключення натиску на спеціальність для факульетів
    
    configBlock block;
    block.setWidget(LeftSide);
    block.setLayout(LeftSideLayout);
    block.setConfigBlock(
        [this, &mainWedgetTools, RightSide, MiddleSide](QGridLayout* layout, QWidget* widget)->bool {
            ///////////////////////////////////////////////////////////////////////////////////////////////////
            //HERE: відбувається поступове отримання всіх спеціальностей із об'єкта SandSBlocks за допомогою counter            
            static int counter = 0;
            QString SpecialtyName = "спеціальність";
            if (counter++ >= 300) { counter = 0; return true; }

            ///////////////////////////////////////////////////////////////////////////////////////////////////
            blockWidget* block = new blockWidget(SpecialtyName, widget);
            connect(block, &QPushButton::released, block, 
                [this, block, RightSide, MiddleSide, SpecialtyName, &mainWedgetTools]() mutable {
                    block->specialtyButtonPressed(*this->TimersCounter, mainWedgetTools, RightSide, MiddleSide, SpecialtyName, *SandSBlocks);
                });
            block->AddStructure();
            layout->addWidget(block, counter++ + 1, 0);
            return false;
        },
        mainWedgetTools, 
        *this->TimersCounter, 
        "Cпеціальності"

    );
    //коли натиснуто на блок з групою, весь віджет оновлюється щоб показати студентів у цій групі по центру
    block.setWidget(MiddleSide);
    block.setLayout(MiddleSideLayout);
    block.setConfigBlock(
        [this, &mainWedgetTools, MiddleSide](QGridLayout* layout, QWidget* widget)->bool {
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //HERE: відбувається поступове отримання всіх груп із об'єкта SandSBlocks за допомогою counter            
        static int counter = 0;
        QString GroupName = "Групи";
        if (counter++ >= 3) { return true;  counter = 0; }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        blockWidget* block = new blockWidget(GroupName, widget);
        connect(block, &QPushButton::released, [this, &mainWedgetTools, block, MiddleSide, GroupName]() { block->GroupButtonPressed(*this->TimersCounter, mainWedgetTools, MiddleSide, GroupName, "", "", *SandSBlocks); });
        block->AddStructure();
        layout->addWidget(block, counter++ + 1, 0);
        return false;
        },
        mainWedgetTools,
        * this->TimersCounter,
        "Групи"
    );
    //коли натиснуто блок з факультету, оновлюється блоки з групами
    block.setWidget(RightSide);
    block.setLayout(RightSideLayout);
    block.setConfigBlock(
        [this, &mainWedgetTools, MiddleSide](QGridLayout* layout, QWidget* widget)->bool {
            ///////////////////////////////////////////////////////////////////////////////////////////////////
            //HERE: відбувається поступове отримання всіх факультетів із об'єкта SandSBlocks за допомогою counter            
            static int counter = 0;
            QString FacultyName = "факультети";
            if (counter++ >= 3) { counter = 0;  return true; }
            ///////////////////////////////////////////////////////////////////////////////////////////////////
            blockWidget* block = new blockWidget(FacultyName, widget);
            connect(block, &QPushButton::released, [this, &mainWedgetTools, block, MiddleSide, FacultyName]() { block->FacultyButtonPressed(*this->TimersCounter, mainWedgetTools, MiddleSide, FacultyName, "", *SandSBlocks); });
            block->AddStructure();
            layout->addWidget(block, counter++ + 1, 0);
            return false;
        }, 
        mainWedgetTools,
        *this->TimersCounter,
        "Факультети"
    );
    parent_grid->addWidget(LeftSide, 0, 0);
    parent_grid->addWidget(MiddleSide, 0, 1);
    parent_grid->addWidget(RightSide, 0, 2);
}

//кнопка про нас
void MainWindow_C::AboutUsButtonPressed() {
    try {
        QIcon mainIcon("Images/title.png"); // Іконка для вікна програми
        QDir imagesDir("Images"); // Директорія Images
        if (!imagesDir.exists()) {
            throw ex(1);
        }
        if (mainIcon.isNull()) {
            throw ex(2);
        }
        //нове вікно про нас
        QDialog* settingsWidget = new QDialog(); settingsWidget->setObjectName("settingsWidget");
        QGridLayout* settingsLayout = new QGridLayout(settingsWidget);
        settingsWidget->setWindowIcon(mainIcon); // Встановлюю іконку
        settingsWidget->setWindowTitle("Про нас");
        settingsLayout->setRowStretch(0, 6);


        QWidget* Body = new QWidget(settingsWidget); Body->setObjectName("Body");
        QGridLayout* bodyLayout = new QGridLayout(Body);

        settingsWidget->setFixedSize(400, 400);
        settingsLayout->addWidget(Body, 0, 0);
        //віджет для пагінації (винесено сюди, щоб у майбутньому його налаштувати )
        settingsLayout->setRowStretch(1, 1);
        QWidget* Pagination = new QWidget(settingsWidget); Pagination->setObjectName("Pagination");
        QGridLayout* PaginationLayout = new QGridLayout(Pagination);
        PaginationLayout->setSpacing(5);
        PaginationLayout->setContentsMargins(5, 5, 5, 5);
        QPushButton* ButtonNavigateLright = new QPushButton(Pagination);
        QPushButton* ButtonNavigateLeft = new QPushButton(Pagination);
        ButtonNavigateLeft->setStyleSheet(
            "QPushButton {"
            "   background-color: #787878;"
            "   border: none;"
            "   border-radius: 5px;"
            "}"
            "QPushButton:focus {"
            "   outline: 0px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #828282;"
            "}"
            "QPushButton:pressed {"
            "   background-color: #a0a0a0;"
            "}"
        );
        ButtonNavigateLright->setStyleSheet(
            "QPushButton {"
            "   background-color: #787878;"
            "   border: none;"
            "   border-radius: 5px;"
            "}"
            "QPushButton:focus {"
            "   outline: 0px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #828282;"
            "}"
            "QPushButton:pressed {"
            "   background-color: #a0a0a0;"
            "}"
        );

        ButtonNavigateLeft->setFixedSize(30, 30);
        ButtonNavigateLright->setFixedSize(30, 30);
        if (QIcon("Images/arrowL.png").isNull()) {
            throw ex(2);
        }
        if (QIcon("Images/arrowR.png").isNull()) {
            throw ex(2);
        }
        if (QIcon("Images/photo_Gaulun.jpg").isNull()) {
            throw ex(2);
        }
        if (QIcon("Images/vladMamont.jpg").isNull()) {
            throw ex(2);
        }
        if (QIcon("Images/IvanBondarenko.jpg").isNull()) {
            throw ex(2);
        }
        if (QIcon("Images/sashaTretiak.jpg").isNull()) {
            throw ex(2);
        }
        if (QIcon("Images/RodionShevchenko.jpg").isNull()) {
            throw ex(2);
        }

        ButtonNavigateLeft->setIcon(QIcon("Images/arrowL.png"));
        ButtonNavigateLright->setIcon(QIcon("Images/arrowR.png"));

        PaginationLayout->addWidget(ButtonNavigateLeft, 0, 0, Qt::AlignRight);
        PaginationLayout->addWidget(ButtonNavigateLright, 0, 1, Qt::AlignLeft);

        auto showDev = [this, Body, bodyLayout](int& currentDevelopVar) {
            if (currentDevelopVar == 0) {
                showWindowAboutUs("Images/photo_Gaulun.jpg", "Гайлунь Владислав", "Інтерфейс", "https://github.com/Vlad156763", Body, bodyLayout);
            }
            else if (currentDevelopVar == 1) {
                showWindowAboutUs("Images/vladMamont.jpg", "Мамонт Владислав", "Базу даних", "https://github.com/Teensik", Body, bodyLayout);
            }
            else if (currentDevelopVar == 2) {
                showWindowAboutUs("Images/sashaTretiak.jpg", "Третяк Олександр", "Алгоритми", "https://github.com/MrS1ngULaR1TY", Body, bodyLayout);
            }
            else if (currentDevelopVar == 3) {
                showWindowAboutUs("Images/RodionShevchenko.jpg", "Шевченко Родіон", "Розробку класів", "https://github.com/laidwannabe", Body, bodyLayout);
            }
            else if (currentDevelopVar == 4) {
                showWindowAboutUs("Images/IvanBondarenko.jpg", "Бондаренко Іван", "Обробку винятків", "https://github.com/butterflyway1", Body, bodyLayout);
            }
            else if (currentDevelopVar > 4) {
                showWindowAboutUs("Images/photo_Gaulun.jpg", "Гайлунь Владислав", "Інтерфейс", "https://github.com/Vlad156763", Body, bodyLayout);
                currentDevelopVar = 0;
            }
            else if (currentDevelopVar < 0) {
                showWindowAboutUs("Images/IvanBondarenko.jpg", "Бондаренко Іван", "Обробку винятків", "https://github.com/butterflyway1", Body, bodyLayout);
                currentDevelopVar = 4;
            }
            };
        static int currentDevelopVar = 0;

        connect(ButtonNavigateLright, &QPushButton::released, [this, showDev]() {
            showDev(++currentDevelopVar);
            });
        connect(ButtonNavigateLeft, &QPushButton::released, [this, showDev]() {
            showDev(--currentDevelopVar);
            });

        settingsLayout->addWidget(Pagination, 1, 0);
        QString styleForWidget =
            "#Pagination {"
            "   background-color: rgb(90,90,90);"
            "   border-radius: 10px;"
            "   padding: 10px;"
            "}";
        settingsWidget->setStyleSheet(
            "#settingsWidget {"
            "   background-color: rgb(30,30,30);"
            "}"
        );
        settingsWidget->setAttribute(Qt::WA_DeleteOnClose); //автоматичне очищення пам'яті
        Pagination->setStyleSheet(styleForWidget);
        //виклик методу який відповідає за відображення вікна про нас (без пагінації, пагінація додається окремо в поточній області видимост див. вище)
        showWindowAboutUs("Images/photo_Gaulun.jpg", "Гайлунь Владислав", "Інтерфейс", "https://github.com/Vlad156763", Body, bodyLayout);
        settingsWidget->exec();
    }
    catch (ex& error) {
        auto dialogEW = [this](const char* msg, const char* title, QStyle::StandardPixmap style) {
            QLabel* iconLabel = new QLabel();
            iconLabel->setPixmap(this->style()->standardIcon(style).pixmap(40, 40));
            iconLabel->setAttribute(Qt::WA_DeleteOnClose);
            WarningDialog warning(this, msg, title, "", iconLabel, "Ок");
            warning.show();
            };
        if (error.getErrorCode() == 1) {
            dialogEW("Перевстановіть програму!\nКаталог з фото незнайдено!!", "Помилка", QStyle::SP_MessageBoxCritical);
        }
        else if (error.getErrorCode() == 2) {
            dialogEW("Перевстановіть програму!\nДеякі фото пошкоджені або видалені!", "Помилка", QStyle::SP_MessageBoxCritical);
        }
    }
   
}
//загальне вікно для виведення інформації про нас
void MainWindow_C::showWindowAboutUs( const QString& path, const QString& name, const QString& responsible, const QString& linkToGit, QWidget* Body, QGridLayout* bodyLayout)  {
    QString styleForWidget =
        "#Body {"
        "   background-color: rgb(90,90,90);"
        "   border-radius: 10px;"
        "   padding: 10px;"
        "}";
    Body->setStyleSheet(styleForWidget);
    // для основного віджету встановлюю компоновщик і два віджети для фото і для тексту

    QWidget* textLocation = new QWidget(Body); textLocation->setObjectName("textLocation");
    textLocation->setStyleSheet(
        "#textLocation {"
        "   background-color: rgb(64, 64, 64);"
        "   color: rgb(255, 255, 255); "
        "   font-size: 12px;"
        "   border-radius: 5px;"
        "}"
    );
    //для текстового віджету додаю компоновщик щоб красиво розприділити текст
    QGridLayout* textLayout = new QGridLayout(textLocation);
    //додаю текст
    QLabel* textName = new QLabel(name, textLocation); textName->setObjectName("textName");
    QLabel* textLink = new QLabel(
        "<a href='" + linkToGit + "' style='color: rgb(53, 133, 129);'>Github</a>", textLocation
    );
    textLink->setTextFormat(Qt::RichText);
    QLabel* textResponsible = new QLabel("Відповідальний за: " + responsible, textLocation); textResponsible->setObjectName("textResponsible");
    textResponsible->setStyleSheet("#textResponsible { color: rgb(255, 255, 255); }");
    textName->setStyleSheet(
        "#textName {"
        "   font-weight: bold;"
        "   color: rgb(255, 255, 255); "
        "   background-color: rgb(8, 82, 79);"
        "   border-radius: 5px;"
        "   border: 2px solid rgb(23,103,99);"
        "}"
    );
    textLink->setOpenExternalLinks(true); //відкриття зовнішніх посилань
    //налаштовую фото
    
    QLabel* photoLabel = new QLabel(Body);  photoLabel->setObjectName("photoLabel");
    photoLabel->setPixmap(QPixmap(path).scaled(215, 215, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    photoLabel->setAlignment(Qt::AlignCenter);
   
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
}

void MainWindow_C::HelpButtonPressed() {
    //нове вікно з кнопками для додавання студентів,і для видалення 
    QDialog* settingsWidget = new QDialog(); settingsWidget->setObjectName("settingsWidget");
    settingsWidget->setStyleSheet("#settingsWidget {    background-color: rgb(30, 30, 30); padding: 5px; }");

    QGridLayout* settingsLayout = new QGridLayout(settingsWidget);
    settingsWidget->setWindowTitle("Допомога");
    QIcon mainIcon("Images/title.png");
    settingsWidget->setWindowIcon(mainIcon); // Встановлюю іконку

    QWidget* MainWidget = new QWidget(settingsWidget); MainWidget->setObjectName("MainWidget");
    QGridLayout* MainLayout = new QGridLayout(MainWidget);

    QScrollArea* WidgetScroll = new QScrollArea(MainWidget);

    QLabel* MainText = new QLabel(MainWidget); MainText->setObjectName("MainText");
    MainText->setTextInteractionFlags(Qt::TextSelectableByMouse);
    MainText->setWordWrap(true); // Увімкнути перенесення тексту
    WidgetScroll->setWidget(MainText);
    WidgetScroll->setWidgetResizable(true);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    this->setEnabled(false);
    MainText->setText(
        "<html>"
        "   <body>"
        "       <div style='text-align: center; font-size: 20px; color: #ffffff; font-weight: bold;'>"  
        "           Зараз ми вам допоможемо!"
        "       </div>"
        "       <hr>"
        "       <div style = 'font-size: 18px; color: #ffffff; font-weight: bold;'>"
        "           Знайомство"
        "       </div>"
        "       <div style = 'font-size: 14px; color: #ffffff;'>"
        "           Раді що завітали до нас! Ми - студенти-програмісти університету \"Запорізька політехніка\" які виконують курсовий проєкт в цілях отримати залік. Бажаємо приємного користування додатком! "
        "       </div>"
        "       <div style = 'font-size: 18px; color: #ffffff; font-weight: bold;'>"
        "           Що це?"
        "       </div>"
        "       <div style = 'font-size: 14px; color: #ffffff;'>"
        "           Цей додаток був розроблений в цілях структурувати оцінки студентів у одне місце, а також полегшити взаємодію з ними."
        "       </div>"
        "       <div style = 'font-size: 18px; color: #ffffff; font-weight: bold;'>"
        "       Як користуватись?"  
        "       </div>"
        "       <ol>"
        "           <li>"
        "               <div style = 'font-size: 14px; color: #ffffff; font-weight: bold;'>"
        "                   Головне вікно (Успішність студентів)"
        "               </div>"
        "               <div style = 'font-size: 14px; color: #ffffff;'>"
        "                   Поточне вікно зустрічає вас 2-ма частинами <i>верхньою </i> та <i>нижньою</i> які візуально поділені на 3 підчастини кожна."
        "                   <br><u>Верхня частина</u> - відповідає за керування, тут можна: переглянути розробликів, відкрити вікно з допомогою, знайти студента та перейти до налаштувань." 
        "                   Пошук студента відбувається за специфічним стандартом вказуючи спеціальність, факультет, групу та піб студента. Наприклад: (s: спеціальність f: факультет g: група n: піб) "
        "                   де, все що в () це записується в поле пошуку. Також не можна вводити інші символи окрім: англійських, українських літер (будь-якого регістру), цифри, символи ( ` ' \" - _) та пробіл. Всі інші символи викликатимуть помилку. "
        "                   <br><u>Нижня частина</u>- відповідає за навігацію та пошук студента вручну натискаючи на <i>блоки</i>. "/*сортування тут*/
        "                   <br><u>Блоки</u> - це кнопки, які допомагають знайти оцінки студента. "
        "                   <br><u>Лівий віджет блоків</u> - відповідає за блоки із (спеціальністю), і якщо натиснути на нього, Ви отримаєте всі групи, факультети і тд. які мають обрану спеціальність."
        "                   <br><u>Центральний віджет блоків</u> - відповідає одразу за групи, та за студентів. Одразу Вам буде видно тільки групи, так щоб отримати блоки із студентами треба зробити *клік* "
        "                   по блоку з групою. Після цього у Вас з'явиться доступ до студентів які є у групі. Натиснувши на будь-який блок із студентом ви відкриєте вікно з <i>предметами студента </i>."
        "                   <br><u>Правий віджет блоків</u> - у цьому віджеті ви можете обрати певний факультет щоб зменшити пошуки груп та студентів."
      
        "               </div>"
        "           </li>"
        "           <li>"
        "               <div style = 'font-size: 14px; color: #ffffff; font-weight: bold;'>"
        "                   Вікно (Про нас)"
        "               </div>"
        "               <div  style = 'font-size: 14px; color: #ffffff;'>"
        "                   Це вікно призначене для перегляду розробників, їх акаунтів на Github, фото яке розробники бажали вставити, а також хто за що був відповідальний.<br>"  
        "                   Для навігації використовуйте пагінацію яка розташована знизу (стрілочки вліво-вправо) щоб переглядати всіх розробників.<br>"
        "               </div>"
        "           </li>"
        "           <li>"
        "               <div style = 'font-size: 14px; color: #ffffff; font-weight: bold;'>"
        "                   Вікно (Допомога)"
        "               </div>"
        "               <div  style = 'font-size: 14px; color: #ffffff;'>"
        "                   В цьому вікні ви можете почитати що означає кожен віджет, для чого ця програма була створена, як нею користуватись. Цей віджет вам гарантовано допоможе!<br>"
        "               </div>"
        "           </li>"
        //here:  якщо буде додано пошук, то напиши про нього тут
        "           <li>"
        "               <div style = 'font-size: 14px; color: #ffffff; font-weight: bold;'>"
        "                   Вікно (Налаштування)"
        "               </div>"
        "               <div  style = 'font-size: 14px; color: #ffffff;'>"
        "                   Вікно зустріне вас 8-ма кнопками, які додають студетів/групи/факультети і тд. (Після натиску на будь-яку кнопку з цього меню Вам буде надано поле для введеня "
        "                   і підказака що саме треба ввести у поле. Якщо ви спробуєте одразу зберегти (нічого не написавши у поле/поля буде попередження. Якщо міститиме символи, які не були перелічені \"пошуку\" буде попередження. Якщо ви додасте спеціальність/факультет/групу і тд. "
        "                   яка вам більше не потрібна, ви можете її в будь-який час видалити за допомогою відповідних кнопок. "
        "                   Якщо ви заповнили поля для додавання/видалення і натиснули збереги (або видалити) то у правому нижньому куту екрану з'явиться повідомлення про це."  
        "               </div>"
        "           </li>"
        "           <li>"
        "               <div style = 'font-size: 14px; color: #ffffff; font-weight: bold;'>"
        "                   Вікно (Предмети студента)"
        "               </div>"
        "               <div  style = 'font-size: 14px; color: #ffffff;'>"
        "                   Тут ви можете бачити ще одні блоки, але вони пов'язані з предметами поточного студента. Ви можете <i>додати</i> або <i>видалити</i> певний предмет вказавши його назву."
        "               </div>"
        "           </li>"
        "           <li>"
        "               <div style = 'font-size: 14px; color: #ffffff; font-weight: bold;'>"
        "                   Вікно (Оцінки студента)"
        "               </div>"
        "               <div  style = 'font-size: 14px; color: #ffffff;'>"
        "                   В цьому вікні є текстове поле в яке Ви додаєте оцінки (не важливо як, зчитані будуть тільки числа без будь-яких символів) при додаванні оцінок у текстове поле і натисканні"
        "                   \"зберегти\", після повторного перезаходу, ті оцінки, які були введені виведуться знову для редагування. Ви можете видалити всі оцінки залишивши пусте поле і зберегти його"
        "                   , а можете одразу додати всі оцінки які має цей студент."
        "               </div>"
        "           </li>"
        "       </ol>"
        "       <hr>"
        "       <div style='text-align: center; font-size: 20px; color: #ffffff; font-weight: bold;'>"  
        "           Бажаємо приємного користування!"
        "       </div>"
        "   </body>"
        "</html>"
    );



    MainText->setStyleSheet(
        "#MainText {" 
        "   background-color: transparent;"
        "   padding: 10px;"
        "}"
    );
    MainWidget->setStyleSheet(
        "#MainWidget {"
        "   background-color: rgb(90,90,90);"
        "   border-radius: 10px;"
        "}"
    );
    WidgetScroll->setStyleSheet(
        "QScrollArea {"
        "   border: none;"
        "   background-color: transparent;"
        "}"
        "QScrollBar:vertical {"
        "    width: 8px;"
        "    margin: 0px;"
        "    padding: 0px;"
        "    border-radius: 4px;"
        "    background-color: rgb(90,90,90);"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: rgb(64,64,64);"
        "    min-height: 20px;"
        "    border-radius: 4px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    height: 0px;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "    background: none;" //ось це прибирає прозорість блоку, де знаходиться повзунок 
        "}"
    );
    this->setEnabled(true);
    QApplication::restoreOverrideCursor();
    MainLayout->addWidget(WidgetScroll);
    settingsLayout->addWidget(MainWidget);
    settingsWidget->setFixedSize(500, 500);
    MainLayout->setSpacing(0);
    MainLayout->setContentsMargins(0, 5, 5, 5);
    settingsWidget->setAttribute(Qt::WA_DeleteOnClose); //автоматичне очищення пам'яті
    settingsWidget->exec();
}
void MainWindow_C::setingsButtonPressed() {
    //нове вікно з кнопками для додавання студентів,і для видалення 
    QDialog* settingsWidget = new QDialog();
    settingsWidget->setAttribute(Qt::WA_DeleteOnClose); //автоматичне очищення пам'яті
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
        "   color: rgb(255, 255,255);"
        "   font-size: 14px;"
        "   border-radius: 5px;"
        "   font-weight: bold;"
        "}"
        "#%1:hover {"
        "   background-color: rgb(40, 140, 40);"  // колір змінюється при наведенні
        "}"
        "#%1:focus {"
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
        "   color: rgb(255,255,255);"
        "   font-size: 14px;"
        "   border-radius: 5px;"
        "   font-weight: bold;"
        "}"
        "#%1:hover {"
        "   background-color: rgb(140, 40, 40);"  // колір змінюється при наведенні
        "}"
        "#%1:focus {"
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

    settingsWidget->setFixedSize(this->width() / 3 + 60, this->height() / 3 + 20); //розмір форми підлаштовується під розміри вікна 
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
        { "Спеціальність:", "Факультет:", "Група:","Студент:" },
        { "InputSpecialty", "InputFaculty", "InputGroup", "InputStudent" },
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
        { "Спеціальність:" },
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
// БД
void MainWindow_C::SaveButtonFor_AddSpecialty(QDialog* dialog) {
    // Лямбда-функція для дій з БД спеціальність
    auto dbAction = [this](vector<QString> AllLineEdits) {
        if (AllLineEdits.size() < 1) {
            cqdout << "No data to add Specialty!";
            return;
        }
        QString specialty = AllLineEdits[0]; // Спеціальність

        QSqlDatabase db = QSqlDatabase::database();
        QSqlQuery query(db);

        addSpecialty(query, specialty); // Функція для додавання спеціальності

        };

    // Викликаю загальний метод 
    SaveButtonFor_AllType(dialog, "Успішно додано!", "8, 82, 79", dbAction, { "InputSpecialty" });
}
void MainWindow_C::SaveButtonFor_AddFaculty(QDialog* dialog) {
    // Лямбда-функція для дій з БД (додати факультет)
    auto dbAction = [this](vector<QString> AllLineEdits) {
        if (AllLineEdits.size() < 2) {
            cqdout << "No data to add Faculty!";
            return;
        }
        QString specialty = AllLineEdits[0]; // Спеціальність
        QString faculty = AllLineEdits[1]; ; // Факультет

        QSqlDatabase db = QSqlDatabase::database();
        QSqlQuery query(db);

        addFaculty(query, specialty, faculty); // Функція для додавання факультету
        };

    // Викликаю загальний метод 
    SaveButtonFor_AllType(dialog, "Успішно додано!", "8, 82, 79", dbAction, { "InputSpecialty", "InputFaculty" });
}
void MainWindow_C::SaveButtonFor_AddGroup(QDialog* dialog) {
    // Лямбда-функція для дій з БД (додати групу)
    auto dbAction = [this](vector<QString> AllLineEdits) {
        if (AllLineEdits.size() < 3) {
            cqdout << "No data to add group!";
            return;
        }
        QString specialty = AllLineEdits[0]; // Спеціальність 
        QString faculty = AllLineEdits[1]; ; // Факультет
        QString groupString = AllLineEdits[2]; // Група как строка

        QSqlDatabase db = QSqlDatabase::database();
        QSqlQuery query(db);

        addGroup(query, specialty, faculty, groupString); // Функція для додавання групи
        };

    // Викликаю загальний метод 
    SaveButtonFor_AllType(dialog, "Успішно додано!", "8, 82, 79", dbAction, { "InputSpecialty", "InputFaculty", "InputGroup" });
}
void MainWindow_C::SaveButtonFor_AddStudent(QDialog* dialog) {
    // Лямбда-функція для дій з БД (додати студента)
    auto dbAction = [this](vector<QString> AllLineEdits) {
        // Перевіримо, чи достатьо даних
        if (AllLineEdits.size() < 4) {
            cqdout << "No data to add Students!";
            return;
        }

        QString specialty = AllLineEdits[0]; // Спеціальність
        QString faculty = AllLineEdits[1]; // Факультет
        QString groupString = AllLineEdits[2]; // Група как строка
        QString name = AllLineEdits[3]; // ПІБ

        QSqlDatabase db = QSqlDatabase::database(); 
        QSqlQuery query(db); // Створюємл обьект базиданих

        // Функція додавання студента
        addStudent(query, name, faculty, specialty, groupString); // Функція для додавання студента
        };

    // Загальний метод
    SaveButtonFor_AllType(dialog, "Успішно додано!", "8, 82, 79", dbAction, { "InputSpecialty", "InputFaculty", "InputGroup", "InputStudent" });
}

void MainWindow_C::DeleteButtonFor_DeleteStudent(QDialog* dialog) {
    // Лямбда-функція для дій з БД (додати студента)
    auto dbAction = [this](vector<QString> AllLineEdits) {
        // Перевіримо, чи достатьо даних
        if (AllLineEdits.size() < 4) {
            cqdout << "No data to add Students!";
            return;
        }

        QString specialty = AllLineEdits[0]; // Спеціальність
        QString faculty = AllLineEdits[1]; // Факультет
        QString groupString = AllLineEdits[2]; // Група как строка
        QString name = AllLineEdits[3]; // ПІБ

        QSqlDatabase db = QSqlDatabase::database();
        QSqlQuery query(db); // Створюємл обьект базиданих
        
        DeleteStudent(query, name, faculty, specialty, groupString);
        };
    // Викликаю загальний метод 
    SaveButtonFor_AllType(dialog, "Успіншо видалено!", "169, 38, 38", dbAction, { "InputSpecialty", "InputFaculty", "InputGroup", "InputStudent" });
}
void MainWindow_C::DeleteButtonFor_DeleteGroup(QDialog* dialog) {
    // Лямбда-функція для дій з БД (Видалити групу)
    // Лямбда-функція для дій з БД (додати групу)
    auto dbAction = [this](vector<QString> AllLineEdits) {
        if (AllLineEdits.size() < 3) {
            cqdout << "No data to add group!";
            return;
        }
        QString specialty = AllLineEdits[0]; // Спеціальність 
        QString faculty = AllLineEdits[1]; ; // Факультет
        QString groupString = AllLineEdits[2]; // Група как строка

        QSqlDatabase db = QSqlDatabase::database();
        QSqlQuery query(db);
        DeleteGroup(query, specialty, faculty, groupString);
        };
    // Викликаю загальний метод 
    SaveButtonFor_AllType(dialog, "Успіншо видалено!", "169, 38, 38", dbAction, { "InputSpecialty", "InputFaculty", "InputGroup" });
}
void MainWindow_C::DeleteButtonFor_DeleteFaculty(QDialog* dialog) {
    // Лямбда-функція для дій з БД (додати факультет)
    auto dbAction = [this](vector<QString> AllLineEdits) {
        if (AllLineEdits.size() < 2) {
            cqdout << "No data to add Faculty!";
            return;
        }
        QString specialty = AllLineEdits[0]; // Спеціальність
        QString faculty = AllLineEdits[1]; ; // Факультет

        QSqlDatabase db = QSqlDatabase::database();
        QSqlQuery query(db);

        query.prepare("SELECT COUNT(*) FROM specialty WHERE specialty = :specialty");
        query.bindValue(":specialty", specialty);
        if (!query.exec() || !query.next() || query.value(0).toInt() == 0) {
            cqdout << "This specialty is not exist";
            return;
        }
        DeleteFaculty(query, specialty, faculty);
     };
    // Викликаю загальний метод 
    SaveButtonFor_AllType(dialog, "Успіншо видалено!", "169, 38, 38", dbAction, { "InputSpecialty", "InputFaculty" });

}
void MainWindow_C::DeleteButtonFor_DeleteІSpetialty(QDialog* dialog) {
    auto dbAction = [this](vector<QString> AllLineEdits) {

        if (AllLineEdits.size() < 1) {
            cqdout << "No data to delete Specialty!";
            return;
        }
        QString specialty = AllLineEdits[0]; // Спеціальність

        QSqlDatabase db = QSqlDatabase::database();
        QSqlQuery query(db);

        DeleteSpecialty(query, specialty);
        };

    // Викликаю загальний метод 
    SaveButtonFor_AllType(dialog, "Успішно видалено!", "169, 38, 38", dbAction, { "InputSpecialty" });
}

template<typename LaFunc>
void MainWindow_C::SaveButtonFor_AllType(QDialog* dialog, const QString& text, const QString& color, LaFunc dbAction, const QStringList& fieldNames) {
    //створення вектора для запису у БД всіх полів
    vector<QString> AllLineEdits;
    AllLineEdits.reserve(fieldNames.size());//резервні місця під текст
    auto is_correct = [](QLineEdit* lineEdit)->bool {
        QRegularExpression regex(R"(^[0-9A-Za-zа-яА-ЯєЄіІїЇґҐ \`\'\"\-\_]+$)");
        QString text = lineEdit->text();
        return regex.match(text).hasMatch();
        };
    // Перевірка полів за допомогою ітератора
    // Перевіряємо, чи є діти
    for (const QString& fieldName : fieldNames) { //проходжусь по кожній комірці списку 
        QLineEdit* lineEdit = dialog->findChild<QLineEdit*>(fieldName);
        
        if (lineEdit == nullptr || lineEdit->text().isEmpty()) { //якщо дитина з такою унікальною назовю знайдена і пуста - попередження
            QLabel* iconLabel = new QLabel();
            iconLabel->setPixmap(this->style()->standardIcon(QStyle::SP_MessageBoxWarning).pixmap(40, 40));
            iconLabel->setAttribute(Qt::WA_DeleteOnClose);
            WarningDialog warning(dialog, "Заповніть всі поля!", "Попередження", "Images/warning.png", iconLabel, "Ок");
            warning.show();
            return;
        }
        if (!is_correct(lineEdit)) {
            QLabel* iconLabel = new QLabel();
            iconLabel->setPixmap(this->style()->standardIcon(QStyle::SP_MessageBoxWarning).pixmap(40, 40));
            iconLabel->setAttribute(Qt::WA_DeleteOnClose);
            WarningDialog warning(dialog, "Некоректні символи!", "Попередження", "Images/warning.png", iconLabel, "Ок");
            warning.show();
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
void MainWindow_C::WindowAdd_and_Delete_All_Type(QDialog* dialog, const QString& title, const QString& textButton, const QStringList& labels, const QStringList& objectNames, LaFunc saveAction, const int& sizeW) {
    dialog->setFixedWidth(sizeW);
    dialog->setWindowTitle(title);
    dialog->setObjectName("dialog");
    QGridLayout* layout = new QGridLayout(dialog);
    dialog->setModal(true);
    //створюю рядки для вводу, мітки для тексту, вказую для рядків унікальний тип, додаю це все до компоновщика
    for (int i = 0; i < labels.size(); ++i) {
        QLabel* label = new QLabel(labels[i], dialog); //створюю мітку з текстом із параметру
        label->setObjectName("label");
        label->setStyleSheet("#label {color: rgb(255,255,255);}");
        QLineEdit* lineEdit = new QLineEdit(dialog); //створюю рдок для введнення
        lineEdit->setStyleSheet("QLineEdit { background: rgb(60, 60, 60); color: rgb(255,255,255);}");
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
        "   color: rgb(255,255,255);"
        "   font-weight: bold;"
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
    QObject::connect(saveButton, &QPushButton::released, [dialog, saveAction]() {
        saveAction(); // викликає функцію для кнопки збереження
        });
    layout->addWidget(saveButton, labels.size(), 0, 1, 2);
    layout->setAlignment(Qt::AlignTop);
    dialog->exec();
}

SmallMessage_C::SmallMessage_C(QWidget* parent) : QWidget(parent) {}
void SmallMessage_C::show(const QString& text, const QString& color, QGridLayout* layout, Qt::Alignment aligment, int row, int column, int rowSpan, int ColumnSpan) {
    QLabel* label = new QLabel(text, this);
    label->setObjectName("label"); //унікальна назва для CSS
    label->setFixedSize(160, 40); //фіксований розмір
    label->setStyleSheet(
        QString(
            "#label {"
            "   background-color: rgb( %1 ); "
            "   color: white;"
            "   border-radius: 10px;"
            "   padding: 11px;"
            "   font-size: 14px;"
            "   font-weight: bold;"
            "}"
        ).arg(color)
    );
    //вирівнювання тексту
    label->setAlignment(Qt::AlignCenter);

    //вирівнювання віджету
    layout->addWidget(label, row, column, rowSpan, ColumnSpan, aligment);
    QTimer* timer = new QTimer(this); //таймер 
    //підключаю сигнал закінчення таймеру до лямбда функції яка видалить label

    connect(timer, &QTimer::timeout, [label]() { label->deleteLater();  });
    //таймер для запуску один раз
    timer->setSingleShot(true);
    timer->start(3000); //запуск на 3 секунди
}
WarningDialog::WarningDialog(QWidget* parent, const QString& msg, const QString& titleText, const QString& wayIconTitle, QLabel* IconMsg, const QString& textButton) : QDialog(parent) {
    QGridLayout* layout = new QGridLayout(this);
    this->setObjectName("this");
    this->setStyleSheet(
        "#this {"
        "   color: rgb(255,255,255);"
        "   background-color: rgb(30,30,30);"
        "}"
    );
    //іконка
    QIcon mainIcon(wayIconTitle);
    this->setWindowIcon(mainIcon);
    this->setWindowTitle(titleText);
    //іконка
    IconMsg->setParent(this);
    IconMsg->setAlignment(Qt::AlignCenter);
    //текст
    QLabel* textLabel = new QLabel(msg, this);
    textLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    textLabel->setObjectName("textLabel");
    textLabel->setStyleSheet(
        "#textLabel {"
        "   color: #ffffff;"
        "   margin-left: 20px;"
        "}"
    );
    //кнопка
    QPushButton* button = new QPushButton(textButton, this);
     button->setObjectName("button");
    button->setStyleSheet(
        "#button {"
        "   color: rgb(255,255,255);"
        "   background-color: rgb(60,60,60);"
        "}"
        "#button:focus {"
        "   outline: 0px;"  // Видаляє фокусне виділення        
        "}"
    );
    button->setFixedSize(75, 25);
    button->setFixedHeight(25);
    connect(button, &QPushButton::released, [this]() {
            this->accept();
        }
    );
    //додаю віджети у сітку
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 2);
    layout->addWidget(IconMsg, 0, 0);
    layout->addWidget(textLabel, 0, 1);
    layout->addWidget(button, 1, 1, 1, 2, Qt::AlignRight);
}
void WarningDialog::show() {
    this->setFixedHeight(100);
    this->exec();
}
smartText::smartText(const QString& text, QWidget* parent) : QLabel(text, parent), originalText(text) {}
void smartText::updateElidedText() {
    QFontMetrics metrics(font());
    QString elidedText = metrics.elidedText(originalText, Qt::ElideRight, width());
    QLabel::setText(elidedText);
}
void smartText::resizeEvent(QResizeEvent* event) {
    QLabel::resizeEvent(event);
    updateElidedText();
}
blockWidget::circleQWidget::circleQWidget(QWidget* parent) : QWidget(parent) {}
void blockWidget::circleQWidget::SetCoordinats(const int& x, const int& y) {
        this->x = x;
        this->y = y;
    }
void blockWidget::circleQWidget::SetSizeCircle(const int& r1, const int& r2) {
    this->r1 = r1;
    this->r2 = r2;
}
void blockWidget::circleQWidget::SetColor(const QColor& color) {
    this->color = color;
}
void blockWidget::circleQWidget::SetChar(const QChar& symbol) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* text = new QLabel(symbol, this); text->setObjectName("text");
    text->setAlignment(Qt::AlignCenter);
    layout->setSpacing(0);
    layout->getContentsMargins(0, 0, 0, 0);
    text->setStyleSheet(
        "#text {"
        "   color: #ffffff;"
        "   font-size: 20px;"
        "   font-weight: bold;"
        "}"
    ); 
    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(text);
}
void blockWidget::circleQWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true); // Згладжування
    painter.setPen(Qt::NoPen);
    QBrush brush(this->color);
    painter.setBrush(brush);
    painter.drawEllipse(this->x, this->y, this->r1, this->r2);
}
blockWidget::blockWidget(const QString& text, QWidget* parent) : QPushButton(parent) {
    this->layout = new QHBoxLayout(this);
    this->text = new smartText(text, this);
    this->circle = new circleQWidget(this);
    layout->setSpacing(0);
    layout->setContentsMargins(10, 10, 10, 10);
}
blockWidget::blockWidget(QWidget* parent) : QPushButton(parent) {
    this->layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(10, 10, 10, 10);
}
void blockWidget::AddStructure() {
    this->setObjectName("this");
    this->circle->SetCoordinats(0, 0);
    this->circle->SetSizeCircle(60, 60);
    this->circle->setFixedSize(60, 60);
    this->circle->SetChar(this->text->text()[0]);
    this->circle->SetColor(generateColorFromString(this->text->text()));
    this->text->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    this->text->setObjectName("text");
    this->setFixedHeight(80);

    this->text->setStyleSheet(
        "#text {"
        "   color: #ffffff;"
        "   font-weight: bold;"
        "   margin-left: 5px;"
        "   font-size: 16px;"
        "}"
    );
    this->setStyleSheet(
        "#this {"
        "   border-radius: 10px;"
        "   background-color: rgb(120, 120, 120);"
        "   color: #ffffff;"
        "   margin-left: 3px;"
        "   margin-right: 3px;"
        "}"
        "#this:hover {"
        "   background-color: rgb(150, 150, 150);"
        "}"
        "#this:focus {"
        "   outline: 0px;"
        "}"
        "#this:pressed  {"
        "  background-color: rgb(170, 170, 170);"
        "}"
    );
    this->layout->addWidget(this->circle, 0);
    this->layout->addWidget(text, 1);
}
void blockWidget::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    //віджет з текстом займає  (-20) на відступи (-120) на коло
    this->text->setFixedWidth(this->parentWidget()->width() - 20 - 120);
}
QColor blockWidget::generateColorFromString(const QString& input) {
    size_t hash = qHash(input);
    int hue = hash % 360;
    int saturation = 100 + (hash % 50);
    int lightness = 100 + (hash % 50);
    // Якщо колір вийшов занадто сірим
    if (saturation < 160 && lightness > 140 && lightness < 160) {
        hue = (hue + 180) % 360;// зміщую відтінок на 180 градусів
    }
    return QColor::fromHsl(hue, saturation, lightness);
}
void blockWidget::specialtyButtonPressed(counterTimer& counterTimers, QWidget& mainWedgetTools, QWidget* RightSide, QWidget* MiddleSide, const QString& SpecialtyName, SandS& SandSAllBlocks) {
    cqdout << "specialtyButtonPressed" << '(' << SpecialtyName << ')' << "(None)" << "(None)" << "(None)" << "(None)";
    static QPointer<blockWidget> prevPressedButton = nullptr;
    if (prevPressedButton && prevPressedButton != this) {
        prevPressedButton->setStyleSheet(
            "blockWidget {"
            "   border-radius: 10px;"
            "   background-color: rgb(120, 120, 120);"
            "   color: #ffffff;"
            "   margin-left: 3px;"
            "   margin-right: 3px;"
            "}"
            "blockWidget:hover {"
            "   background-color: rgb(150, 150, 150);"
            "}"
            "blockWidget:focus {"
            "   outline: 0px;"
            "}"
        );
    }
    this->setStyleSheet(
        "blockWidget {"
        "   border-radius: 10px;"
        "   background-color: rgb(120, 150, 120);"
        "   color: #ffffff;"
        "   margin-left: 3px;"
        "   margin-right: 3px;"
        "}"
        "blockWidget:hover {"
        "   background-color: rgb(150, 180, 150);"
        "}"
        "blockWidget:focus {"
        "   outline: 0px;"
        "}"
    );
    prevPressedButton = this;
    
    configBlock block;
    block.setWidget(RightSide);
    block.setLayout(RightSide->layout());
    block.setConfigBlock(
        [&counterTimers, &mainWedgetTools, MiddleSide, SpecialtyName, &SandSAllBlocks](QGridLayout* layout, QWidget* widget)->bool {
            ///////////////////////////////////////////////////////////////////////////////////////////////////
            //HERE: відбувається поступове отримання факультетів, які мають спеціальність SpecialtyName із об'єкта SandSBlocks за допомогою counter            
            static int counter = 0;
            //ця зміна повинна мати будь-який факультет, який має спеціальність SpecialtyName
            QString FacultyName = "Факультет з спеціальністю";
            if (counter++ >= 3) { counter = 0;  return true; }
            ///////////////////////////////////////////////////////////////////////////////////////////////////
            blockWidget* block = new blockWidget(FacultyName, widget);
            connect(block, &QPushButton::released,
                [&counterTimers, &mainWedgetTools, block, MiddleSide, SpecialtyName, FacultyName, &SandSAllBlocks]() {
                    block->FacultyButtonPressed(counterTimers, mainWedgetTools, MiddleSide, FacultyName, SpecialtyName, SandSAllBlocks);
                });
            block->AddStructure();
            layout->addWidget(block, counter++ + 1, 0);
            return false;
        }, 
        mainWedgetTools, 
        counterTimers,
        "Факультети"
    );
    block.setWidget(MiddleSide);
    block.setLayout(MiddleSide->layout());
    block.setConfigBlock(
        [&counterTimers, &mainWedgetTools, MiddleSide, SpecialtyName, &SandSAllBlocks](QGridLayout* layout, QWidget* widget)->bool {
            ///////////////////////////////////////////////////////////////////////////////////////////////////
            //HERE: відбувається поступове отримання груп, які мають спеціальність SpecialtyName із об'єкта SandSBlocks за допомогою counter            
            static int counter = 0;
            QString GroupName = "Група з спеціальністю ";
            if (counter++ >= 3) { counter = 0;  return true; }

            ///////////////////////////////////////////////////////////////////////////////////////////////////
            blockWidget* block = new blockWidget(GroupName, widget);
            connect(block, &QPushButton::released, [&counterTimers, &mainWedgetTools, block, MiddleSide, SpecialtyName, GroupName, &SandSAllBlocks]() {block->GroupButtonPressed(counterTimers, mainWedgetTools, MiddleSide, GroupName, "", SpecialtyName, SandSAllBlocks); });
            block->AddStructure();
            layout->addWidget(block, counter++ + 1, 0);
            return false;
        }, 
        mainWedgetTools, 
        counterTimers,
        "Групи"
    );
}
void blockWidget::GroupButtonPressed(counterTimer& counterTimers, QWidget& mainWedgetTools, QWidget* widget, const QString& GroupName, const QString& FacultyName, const QString& SpecialtyName, SandS& SandSAllBlocks) {
    cqdout << "GroupButtonPressed" << '(' << SpecialtyName << ')' << '(' << FacultyName << ')' << '(' << GroupName << ')' << "(None)" << "(None)";
    configBlock block;
    block.setWidget(widget);
    block.setLayout(widget->layout());
    block.setConfigBlock(
        [&counterTimers, &mainWedgetTools, widget, SpecialtyName, FacultyName, GroupName, &SandSAllBlocks](QGridLayout* layout, QWidget* widget)->bool {
            ///////////////////////////////////////////////////////////////////////////////////////////////////
            //HERE: відбувається поступове отримання ПІБ студенітів, які мають спеціальність, факультет і групу (спеціальність, факультет можуть бути пусті) із об'єкта SandSBlocks за допомогою counter            
            static int counter = 0;
            QString StudyName = "Студенти";
            if (counter++ >= 3) { counter = 0;  return true; }

            ///////////////////////////////////////////////////////////////////////////////////////////////////
            blockWidget* block = new blockWidget(StudyName, widget);
            // кнопки поки не пригвинчую, так як кнопки зі студентами треба привязати до вікна редагування їх оцінок
            connect(block, &QPushButton::released, [&counterTimers, &mainWedgetTools, block, widget, FacultyName, StudyName, GroupName, SpecialtyName, &SandSAllBlocks]() {block->StudyButtonPressed(StudyName, GroupName, FacultyName, SpecialtyName, SandSAllBlocks); });
            block->AddStructure();
            layout->addWidget(block, counter++ + 1, 0);
            return false;
        },
        mainWedgetTools,
        counterTimers,
        "Студенти"
    );
}

void blockWidget::StudyButtonPressed(const QString& StudyName, const QString& GroupName, const QString& FacultyName, const QString& SpecialtyName, SandS& SandSAllBlocks) {
    cqdout << "StudyButtonPressed" << '(' << SpecialtyName << ')' << '(' << FacultyName << ')' << '(' << GroupName << ')' << '(' << StudyName << ')';

    QWidget*PredmetBox;
    QDialog* dialog = this->setDialogForPredmet(StudyName, GroupName, FacultyName, SpecialtyName, &PredmetBox);
    configBlock block;
    block.setWidget(PredmetBox);
    block.setLayout(PredmetBox->layout());
    block.setConfigPredmetBlock(
        [SpecialtyName, FacultyName, GroupName, StudyName, this, PredmetBox, block, &SandSAllBlocks](QGridLayout* layout, QWidget* widget)->bool {
            ///////////////////////////////////////////////////////////////////////////////////////////////////
            //HERE: відбувається поступове отримання предметів за спеціальністю, факульетом, групою, Піб студента (значення спеціальність, факультет можуть бути пусті) із об'єкта SandSBlocks за допомогою counter            
            static int counter = 0;
            QString PredmetName = "Предмети";
            if (counter++ >= 3) { counter = 0;  return true; }

            ///////////////////////////////////////////////////////////////////////////////////////////////////
            blockWidget* block = new blockWidget(PredmetName, PredmetBox);
            connect(block, &QPushButton::released, [this, SpecialtyName, FacultyName, GroupName, StudyName, PredmetName]() {
                this->PredmetButtonPressed(SpecialtyName, FacultyName, GroupName, StudyName, PredmetName);
            });

            block->AddStructure();
            layout->addWidget(block, counter++ + 1, 0);
            return false;
        },
        PredmetBox,
        "Предмети"
    );
    dialog->exec();    
}
QDialog* blockWidget::setDialogForPredmet(const QString& StudyName, const QString& GroupName, const QString& FacultyName, const QString& SpecialtyName, QWidget** PredmetBoxM) {
    QDialog* settingsWidget = new QDialog(); settingsWidget->setObjectName("settingsWidget");
    settingsWidget->setStyleSheet(
        "#settingsWidget {"
        "   background-color: rgb(30,30,30);"
        "}"
    );
    QGridLayout* settingsLayout = new QGridLayout(settingsWidget);
    settingsWidget->setWindowTitle("Предмети студента");
    QIcon mainIcon("Images/title.png");
    settingsWidget->setWindowIcon(mainIcon); // Встановлюю іконку

    QWidget* PredmetBox = new QWidget(settingsWidget); PredmetBox->setObjectName("PredmetBox");
    *PredmetBoxM = PredmetBox;
    QGridLayout* PredmetBoxLayout = new QGridLayout(PredmetBox);
    QWidget* WidgetButton = new QWidget(settingsWidget); WidgetButton->setObjectName("WidgetButton");
    QGridLayout* layoutButton = new QGridLayout(WidgetButton);

    PredmetBox->setStyleSheet(
        "#PredmetBox {"
        "   border-radius: 10px;"
        "   background-color: rgb(90,90,90);"
        "}"
    );
    WidgetButton->setStyleSheet(
        "#WidgetButton {"
        "   border-radius: 10px;"
        "   background-color: rgb(90,90,90);"
        "}"
    );


    //частина з кнопками 
    QPushButton* addPredmet = new QPushButton("Додати предмет", WidgetButton); addPredmet->setObjectName("addPredmet");
    QPushButton* delPredmet = new QPushButton("Видалити предмет", WidgetButton); delPredmet->setObjectName("delPredmet");
    //вікно з додаванням та видаленням предметів

    auto WindowAddAndDelPredmet = [settingsLayout, settingsWidget, this](const QString& title, const QString& Label, const QString& textButton, QString& PredmetName, const QString& textW, const QString& color) {
        QDialog* dialog = new QDialog(); dialog->setObjectName("dialog");
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        QGridLayout* layout = new QGridLayout(dialog); layout->setObjectName("layout");
        dialog->setFixedWidth(375);
        QIcon icon("Images/title.png");
        QLabel* text = new QLabel(Label, dialog); text->setObjectName("text");
        QLineEdit* line = new QLineEdit(dialog); line->setObjectName("line");
        QPushButton* button = new QPushButton(textButton, dialog); button->setObjectName("button");

        auto is_correct = [](QLineEdit* lineEdit)->bool {
            QRegularExpression regex(R"(^[0-9A-Za-zа-яА-ЯєЄіІїЇґҐ \`\'\"\-\_]+$)");
            QString text = lineEdit->text();
            return regex.match(text).hasMatch();
            };
        QObject::connect(button, &QPushButton::released, [settingsLayout, settingsWidget, textW, color, &PredmetName, dialog, line, is_correct, this]() {
            
            if (line->text().isEmpty()) {
                QLabel* iconLabel = new QLabel();
                iconLabel->setPixmap(dialog->style()->standardIcon(QStyle::SP_MessageBoxWarning).pixmap(40, 40));
                WarningDialog warning(dialog, "Заповніть всі поля!", "Попередження", "Images/warning.png", iconLabel, "Ок");
                warning.show();
            } else if (!is_correct(line)) {
                QLabel* iconLabel = new QLabel();
                iconLabel->setPixmap(this->style()->standardIcon(QStyle::SP_MessageBoxWarning).pixmap(40, 40));
                iconLabel->setAttribute(Qt::WA_DeleteOnClose);
                WarningDialog warning(dialog, "Некоректні символи!", "Попередження", "Images/warning.png", iconLabel, "Ок");
                warning.show();
                return;
            }
            else {
                PredmetName = line->text();
                SmallMessage_C* smallWindow = new SmallMessage_C(settingsWidget);
                smallWindow->show(textW, color, settingsLayout, Qt::AlignHCenter | Qt::AlignTop, 0, 0, 1, 2);
                dialog->accept();
            }
            });
        text->setStyleSheet(
            "#text {"
            "   color: #ffffff;"
            "}"
        );
        line->setStyleSheet(
            "#line { "
            "   background: rgb(60, 60, 60); "
            "   color: rgb(255,255,255);"
            "}"
        );
        dialog->setStyleSheet(
            "#dialog {"
            "   background-color: rgb(30,30,30);"
            "}"
        );
        button->setStyleSheet(
            "#button {"
            "   border-radius: 5px;"
            "   background-color: rgb(64, 64, 64);"
            "   color: rgb(255,255,255);"
            "   font-weight: bold;"
            "}"
            "#button:hover {"
            "   background-color: rgb(120, 120, 120);"
            "}"
            "#button:focus {"
            "   outline: 0px;"
            "}"
            "#button:pressed  {"
            "  background-color: rgb(150, 150, 150);"
            "}"
        );
        layout->addWidget(text, 0, 0);
        layout->addWidget(line, 0, 1);
        layout->addWidget(button, 1, 0, 1, 2);

        dialog->setWindowIcon(icon);
        dialog->setWindowTitle(title);


        dialog->exec();
        };
    QObject::connect(addPredmet, &QPushButton::released, [WindowAddAndDelPredmet, SpecialtyName, FacultyName, GroupName, StudyName]() {
        QString PredmetName;
        WindowAddAndDelPredmet("Додати предмет", "Додати предмет:", "Додати", PredmetName, "Успішно додано!", "8, 82, 79");

        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // todo: додати предмет до БД SpecialtyName, FacultyName, GroupName, StudyName, PredmetName 
        QSqlDatabase db = QSqlDatabase::database();
        QSqlQuery query(db);
        int studentId = -1;

        // Запрос на отримання студента
        studentId = getStudentIDforPredmet(query, StudyName, studentId);

        if (studentId != -1) {
            addSubject(query, PredmetName, studentId);
            cqdout << "Subject added successfully for student ID:" << studentId;
        }
        else {
            cqdout << "Failed to add subject. No matching student found.";
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        cqdout << SpecialtyName << ", " << FacultyName << ", " << GroupName << ", " << StudyName << ", " << PredmetName;
        });
    QObject::connect(delPredmet, &QPushButton::released, [WindowAddAndDelPredmet, SpecialtyName, FacultyName, GroupName, StudyName]() {
        QString PredmetName;

        WindowAddAndDelPredmet("Видалити предмет", "Видалити предмет:", "Видалити", PredmetName, "Успішно видалено!", "169, 38, 38");
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        // todo: видалити предмет до БД SpecialtyName, FacultyName, GroupName, StudyName, PredmetName 
        QSqlDatabase db = QSqlDatabase::database();
        QSqlQuery query(db);
        int studentId = -1;

        // Запрос на отримання студента
        studentId = getStudentIDforPredmet(query, StudyName, studentId);

        if (studentId != -1) {
            DeleteSubject(query, PredmetName, studentId);
            cqdout << "Subject deleted successfully for student ID:" << studentId;
        }
        else {
            cqdout << "Failed to delete subject. No matching student found.";
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        });

    settingsLayout->setRowStretch(0, 25);
    settingsLayout->setRowStretch(1, 1);
    settingsLayout->addWidget(PredmetBox, 0, 0, 1, 2);
    settingsLayout->addWidget(WidgetButton, 1, 0, 1, 2);

    addPredmet->setFixedHeight(30);
    delPredmet->setFixedHeight(30);

    addPredmet->setStyleSheet(
        "#addPredmet {"
        "   border-radius: 5px;"
        "   color: rgb(255,255,255);"
        "   background-color: rgb(64, 64, 64);"
        "   font-size: 12px;"
        "   font-weight: bold;"
        "   margin: 5px;"
        "}"
        "#addPredmet:hover {"
        "   background-color: rgb(120, 120, 120);"
        "}"
        "#addPredmet:focus {"
        "   outline: 0px;"
        "}"
        "#addPredmet:pressed  {"
        "  background-color: rgb(150, 150, 150);"
        "}"
    );
    delPredmet->setStyleSheet(
        "#delPredmet {"
        "   border-radius: 5px;"
        "   color: rgb(255,255,255);"
        "   background-color: rgb(64, 64, 64);"
        "   font-size: 12px;"
        "   font-weight: bold;"
        "   margin: 5px;"
        "}"
        "#delPredmet:hover {"
        "   background-color: rgb(120, 120, 120);"
        "}"
        "#delPredmet:focus {"
        "   outline: 0px;"
        "}"
        "#delPredmet:pressed  {"
        "  background-color: rgb(150, 150, 150);"
        "}"
    );
    layoutButton->setSpacing(0);
    layoutButton->setContentsMargins(0, 0, 0, 0);
    layoutButton->addWidget(addPredmet, 1, 0);
    layoutButton->addWidget(delPredmet, 1, 1);

    settingsWidget->setFixedSize(600, 600);
    settingsWidget->setAttribute(Qt::WA_DeleteOnClose); //автоматичне очищення пам'яті
    return settingsWidget;
}

void blockWidget::PredmetButtonPressed(const QString& SpecialtyName, const QString& FacultyName, const QString& GroupName, const QString& StudentName, const QString& PredmetName) {
    cqdout << "PredmetButtonPressed" << '(' << SpecialtyName << ')' << '(' << FacultyName << ')' << '(' << GroupName << ')' << '(' << StudentName << ')' << '(' << PredmetName << ')';

    QDialog* dialog = new QDialog(); dialog->setObjectName("dialog");
    dialog->setWindowTitle("Оцінки студента");
    QIcon mainIcon("Images/title.png");
    dialog->setWindowIcon(mainIcon); // Встановлюю іконку
    dialog->setStyleSheet(
        "#dialog {"
        "   background-color: rgb(30,30,30);"
        "}"
    );
    dialog->setFixedSize(600, 600);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    QGridLayout* layout = new QGridLayout(dialog);

    QWidget* Eval = new QWidget(dialog); Eval->setObjectName("Eval");
    Eval->setStyleSheet(
        "#Eval {"
        "   border-radius: 10px;"
        "   background-color: rgb(90,90,90);"
        "}"
    );
    QGridLayout* EvalLayout = new QGridLayout(Eval);
    QTextEdit* Edit = new QTextEdit(Eval); Edit->setObjectName("Edit");
    Edit->setStyleSheet(
        "#Edit {"
        "   color: #ffffff;"
        "   background-color: rgb(60,60,60);"
        "}"
    );
    Edit->setReadOnly(false); 

    EvalLayout->addWidget(Edit);
    QWidget* SaveButtonWidget = new QWidget(dialog); SaveButtonWidget->setObjectName("SaveButtonWidget");
    QGridLayout* SaveButtonLayout = new QGridLayout(SaveButtonWidget);
    SaveButtonLayout->setSpacing(0);
    SaveButtonLayout->setContentsMargins(0, 0, 0, 0);
    SaveButtonWidget->setStyleSheet(
        "#SaveButtonWidget {"
        "   border-radius: 10px;"
        "   background-color: rgb(90,90,90);"
        "}"
    );

    QPushButton* addOneEval = new QPushButton("Зберегти", SaveButtonWidget); addOneEval->setObjectName("addOneEval");
    addOneEval->setStyleSheet(
        "#addOneEval {"
        "   border-radius: 5px;"
        "   background-color: rgb(64, 64, 64);"
        "   color: rgb(255,255,255);"
        "   font-size: 12px;"
        "   font-weight: bold;"
        "   margin: 5px;"
        "}"
        "#addOneEval:hover {"
        "   background-color: rgb(120, 120, 120);"
        "}"
        "#addOneEval:focus {"
        "   outline: 0px;"
        "}"
        "#addOneEval:pressed  {"
        "  background-color: rgb(150, 150, 150);"
        "}"
    );
    SaveButtonLayout->addWidget(addOneEval);

    addOneEval->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    addOneEval->setFixedHeight(30);
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // todo: зчитую всі оцінки, які є SpecialtyName, FacultyName, GroupName, StudentName, PredmetName
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    QStringList grades = initializeGrades(query);
    //для прикладу запишу уже в рядок для редагування трохи чисел

    qDebug() << "Grades:" << grades;
    Edit->setText("1, 2, 3, 4, 18, 100, 1, 100");
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    connect(addOneEval, &QPushButton::released, [dialog, Edit]() {
        //зчитую весь рядок оцінок
        QString Evals = Edit->toPlainText();
        //регулярний вираз для отримання тільки чисел
        QRegularExpression regex(R"(\d+)");
        QRegularExpressionMatchIterator matchIterator = regex.globalMatch(Evals);
        QStringList numbers;
        //записую у вектор тільки числа які вдалось найти
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            numbers << match.captured(0);
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        //todo: запис оцінок по PredmetName для SpecialtyName, FacultyName, GroupName, StudentName 
        QString PredmetName;
        QSqlDatabase db = QSqlDatabase::database();
        QSqlQuery query(db);
        int predmet_id = -1;

        predmet_id = getPredmetId(query, PredmetName, predmet_id);

        if (predmet_id != -1) {
            addGrades(query, numbers, predmet_id);
            cqdout << "Grade added successfully for predment ID:" << predmet_id;
        }
        else {
            cqdout << "Failed to add grade. No matching predmet found.";
        }
        getGrades(query, numbers, predmet_id);
        cqdout << numbers; //оцінки певного студента
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        dialog->accept();
        });


    layout->setRowStretch(0, 25);
    layout->setRowStretch(1, 1);
    layout->addWidget(SaveButtonWidget, 1, 0, 1, 2);
    layout->addWidget(Eval, 0, 0, 1, 2);

    dialog->exec();
}
void blockWidget::FacultyButtonPressed(counterTimer& counterTimers, QWidget& mainWedgetTools, QWidget* MiddleSide, const QString& FacultyName, const QString& SpecialtyName, SandS& SandSAllBlocks) {
    cqdout << '(' << SpecialtyName << ')' << '(' << FacultyName << ')' << "(None)" << "(None)" << "(None)";
    static QPointer<blockWidget> prevPressedButton = nullptr;
    if (prevPressedButton && prevPressedButton != this) {
        prevPressedButton->setStyleSheet(
            "blockWidget {"
            "   border-radius: 10px;"
            "   background-color: rgb(120, 120, 120);"
            "   color: #ffffff;"
            "   margin-left: 3px;"
            "   margin-right: 3px;"
            "}"
            "blockWidget:hover {"
            "   background-color: rgb(150, 150, 150);"
            "}"
            "blockWidget:focus {"
            "   outline: 0px;"
            "}"
        );
    }
    this->setStyleSheet(
        "blockWidget {"
        "   border-radius: 10px;"
        "   background-color: rgb(120, 150, 120);"
        "   color: #ffffff;"
        "   margin-left: 3px;"
        "   margin-right: 3px;"
        "}"
        "blockWidget:hover {"
        "   background-color: rgb(150, 180, 150);"
        "}"
        "blockWidget:focus {"
        "   outline: 0px;"
        "}"
    );
    prevPressedButton = this;

    configBlock block;
    block.setWidget(MiddleSide);
    block.setLayout(MiddleSide->layout());
    block.setConfigBlock(
        [&counterTimers, &mainWedgetTools, MiddleSide, SpecialtyName, FacultyName, &SandSAllBlocks](QGridLayout* layout, QWidget* widget)->bool {
            ///////////////////////////////////////////////////////////////////////////////////////////////////
            //HERE: відбувається поступове отримання груп, які мають факультет і спеціальність (спеціальність може бути пуста) із об'єкта SandSBlocks за допомогою counter            
            static int counter = 0;
            QString GroupName = "Група з спеціальністю і факультетом";
            if (counter++ >= 3) { counter = 0;  return true; }

            ///////////////////////////////////////////////////////////////////////////////////////////////////
            blockWidget* block = new blockWidget(GroupName, widget);
            connect(block, &QPushButton::released, [&counterTimers, &mainWedgetTools, block, MiddleSide, FacultyName, SpecialtyName, GroupName, &SandSAllBlocks]() {block->GroupButtonPressed(counterTimers, mainWedgetTools, MiddleSide, GroupName, FacultyName, SpecialtyName, SandSAllBlocks); });
            block->AddStructure();
            layout->addWidget(block, counter++ + 1, 0);
            return false;
        }, 
        mainWedgetTools,
        counterTimers,
        "Групи"
    );
}
configBlock::configBlock() {}
void configBlock::setWidget(QWidget* widget) {
    this->widget = widget;
}
void configBlock::setLayout(QLayout* layout ) {
    this->layout = layout;
}

template<typename LaFunc>
void configBlock::setConfigBlock(LaFunc workDB, QWidget& mainWedgetTools, counterTimer& counterTimers, const QString& textTitle ) {
    //видалення всіх блоків (якщо вони є) з сітки
    QLayoutItem* item;
    while ((item = this->layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    QScrollArea* WidgetScroll = new QScrollArea(widget);
    QWidget* WidgetCapasity = new QWidget(WidgetScroll);
    QGridLayout* LayoutCapasity = new QGridLayout(WidgetCapasity);
    LayoutCapasity->setAlignment(Qt::AlignTop);

    WidgetScroll->setWidget(WidgetCapasity);
    WidgetScroll->setWidgetResizable(true);
    WidgetScroll->setContentsMargins(0, 0, 0, 0);
    this->layout->setContentsMargins(5, 5, 5, 5);

    //віджет зверху щоб додати текст і кнопку сортування
    QWidget* WidgetTop = new QWidget(WidgetCapasity); WidgetTop->setObjectName("WidgetTop");
    WidgetTop->setFixedHeight(50);
    QHBoxLayout* LayoutTop = new QHBoxLayout(WidgetTop); 
    LayoutTop->setSpacing(10);
    LayoutTop->setContentsMargins(10, 5, 10, 5);
    QLabel* TextTop = new QLabel(textTitle, WidgetTop); TextTop->setObjectName("TextTop");
    QPushButton* ButtonSort = new QPushButton(WidgetTop); ButtonSort->setObjectName("ButtonSort");

    WidgetTop->setStyleSheet(
        "#WidgetTop {"
        "   background-color: rgb(70,70,70);"
        "   border-radius: 10px;"
        "}"
    );
    TextTop->setStyleSheet(
        "#TextTop {"
        "   font-weight: bold;"
        "   color: #ffffff;"
        "}"
    );
    ButtonSort->setStyleSheet(
        "#ButtonSort {"
        "   background-color: rgb(120,120,120);"
        "   border-radius: 5px;"
        "   color: rgb(255,255,255);"
        "   font-weight: bold;"
        "}"
        "#ButtonSort:focus {"
        "   outline: 0px;"
        "}"
        "#ButtonSort:hover {"
        "   background-color: rgb(140, 140, 140);"
        "}"
        "#ButtonSort:pressed {"
        "  background-color: rgb(160, 160, 160);"
        "}"
    );
    enum ButtonSortStatusEnum {
        sortZ_A,
        sortA_Z
    };
    
    ButtonSort->setFixedSize(30, 30);
    ButtonSort->setIcon(QIcon("Images/sortUP.png"));
    QObject::connect(ButtonSort, &QPushButton::released, [ButtonSort, textTitle]() {
        static ButtonSortStatusEnum ButtonSortStatus = sortA_Z;
        if (ButtonSortStatus == sortA_Z) {
            QApplication::setOverrideCursor(Qt::BusyCursor);
            if (textTitle == "Cпеціальності") {}
            else if (textTitle == "Факультети") {}
            else if (textTitle == "Групи") {}
            else if (textTitle == "Студенти") {}
            QApplication::restoreOverrideCursor(); // Відновлення стандартного курсора
            
            ButtonSort->setIcon(QIcon("Images/sortDOWN.png"));
            ButtonSortStatus = sortZ_A;
        }
        else {
            QApplication::setOverrideCursor(Qt::BusyCursor);
            if (textTitle == "Cпеціальності") {}
            else if (textTitle == "Факультети") {}
            else if (textTitle == "Групи") {}
            else if (textTitle == "Студенти") {}
            QApplication::restoreOverrideCursor(); // Відновлення стандартного курсора
            ButtonSort->setIcon(QIcon("Images/sortUP.png"));
            ButtonSortStatus = sortA_Z;
        }
        });


    TextTop->setAlignment(Qt::AlignCenter);

    LayoutTop->addWidget(TextTop, 0);
    LayoutTop->addWidget(ButtonSort, 1);
    
    this->layout->addWidget(WidgetTop);
    this->layout->addWidget(WidgetScroll);

    // Гіфка завантаження
    QLabel* gifLoad = new QLabel(WidgetCapasity);
    QMovie* gif = new QMovie("Images/load.gif");
    gif->setScaledSize(QSize(50, 50));
    gifLoad->setMovie(gif);
    LayoutCapasity->addWidget(gifLoad, 0, 0);
    gifLoad->setAlignment(Qt::AlignCenter);
    gif->start();

    // Таймер для поступового додавання віджетів
    QTimer* timer = new QTimer(&mainWedgetTools);
    counterTimers++;

    QApplication::setOverrideCursor(Qt::BusyCursor);
    mainWedgetTools.setEnabled(false);
    // Підключення таймера до функції
    QObject::connect(timer, &QTimer::timeout,
        [&counterTimers, &mainWedgetTools, timer, WidgetCapasity, gif, gifLoad, LayoutCapasity, workDB]() mutable {
            if (workDB(LayoutCapasity, WidgetCapasity)) {
                QTimer::singleShot(500, [&mainWedgetTools, &counterTimers, &gif, &gifLoad]() {
                    gif->stop();
                    gif->deleteLater();
                    gifLoad->deleteLater();
                    counterTimers--; 
                    QApplication::restoreOverrideCursor(); // Відновлення стандартного курсора
                    if (counterTimers.get() == 0) {
                        mainWedgetTools.setEnabled(true);  // Розблокування вікна                        
                    }
                });
                timer->stop();
            }
        }
    );

    WidgetScroll->setStyleSheet(
        "QScrollArea {"
        "   border: none;"
        "   background-color: transparent;"
        "}"
        "QScrollBar:vertical {"
        "    width: 10px;"
        "    margin: 0px;"
        "    padding: 0px;"
        "    border-radius: 10px;"
        "    background-color: rgb(90,90,90);"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: rgb(64,64,64);"
        "    min-height: 20px;"
        "    border-radius: 5px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    height: 0px;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "    background: none;" //ось це прибирає прозорість блоку, де знаходиться повзунок 
        "}"
    );
    WidgetCapasity->setStyleSheet(
        "QWidget {"
        "   background: transparent;"
        "}"
    );
    timer->start(0);
}

template<typename LaFunc>
void configBlock::setConfigPredmetBlock(LaFunc workDB, QWidget* mainWedgetTools, const QString& textTitle) {
    //видалення всіх блоків (якщо вони є) з сітки
    QLayoutItem* item;
    while ((item = this->layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    QScrollArea* WidgetScroll = new QScrollArea(widget);
    QWidget* WidgetCapasity = new QWidget(WidgetScroll);
    QGridLayout* LayoutCapasity = new QGridLayout(WidgetCapasity);
    LayoutCapasity->setAlignment(Qt::AlignTop);

    WidgetScroll->setWidget(WidgetCapasity);
    WidgetScroll->setWidgetResizable(true);
    WidgetScroll->setContentsMargins(0, 0, 0, 0);
    this->layout->setContentsMargins(5, 5, 5, 5);

    //віджет зверху щоб додати текст і кнопку сортування
    QWidget* WidgetTop = new QWidget(WidgetCapasity); WidgetTop->setObjectName("WidgetTop");
    WidgetTop->setFixedHeight(50);
    QHBoxLayout* LayoutTop = new QHBoxLayout(WidgetTop);
    LayoutTop->setSpacing(10);
    LayoutTop->setContentsMargins(10, 5, 10, 5);
    QLabel* TextTop = new QLabel(textTitle, WidgetTop); TextTop->setObjectName("TextTop");
    QPushButton* ButtonSort = new QPushButton(WidgetTop); ButtonSort->setObjectName("ButtonSort");

    WidgetTop->setStyleSheet(
        "#WidgetTop {"
        "   background-color: rgb(70,70,70);"
        "   border-radius: 10px;"
        "}"
    );
    TextTop->setStyleSheet(
        "#TextTop {"
        "   font-weight: bold;"
        "   color: #ffffff;"
        "}"
    );
    ButtonSort->setStyleSheet(
        "#ButtonSort {"
        "   background-color: rgb(120,120,120);"
        "   border-radius: 5px;"
        "   color: rgb(255,255,255);"
        "   font-weight: bold;"
        "}"
        "#ButtonSort:focus {"
        "   outline: 0px;"
        "}"
        "#ButtonSort:hover {"
        "   background-color: rgb(140, 140, 140);"
        "}"
        "#ButtonSort:pressed {"
        "  background-color: rgb(160, 160, 160);"
        "}"
    );
    enum ButtonSortStatusEnum {
        sortZ_A,
        sortA_Z
    };

    ButtonSort->setFixedSize(30, 30);
    ButtonSort->setIcon(QIcon("Images/sortUP.png"));
    QObject::connect(ButtonSort, &QPushButton::released, [ButtonSort, textTitle]() {
        static ButtonSortStatusEnum ButtonSortStatus = sortA_Z;
        if (ButtonSortStatus == sortA_Z) {
            QApplication::setOverrideCursor(Qt::BusyCursor);
            if (textTitle == "Cпеціальності") {}
            else if (textTitle == "Факультети") {}
            else if (textTitle == "Групи") {}
            else if (textTitle == "Студенти") {}
            QApplication::restoreOverrideCursor(); // Відновлення стандартного курсора

            ButtonSort->setIcon(QIcon("Images/sortDOWN.png"));
            ButtonSortStatus = sortZ_A;
        }
        else {
            QApplication::setOverrideCursor(Qt::BusyCursor);
            if (textTitle == "Cпеціальності") {}
            else if (textTitle == "Факультети") {}
            else if (textTitle == "Групи") {}
            else if (textTitle == "Студенти") {}
            QApplication::restoreOverrideCursor(); // Відновлення стандартного курсора
            ButtonSort->setIcon(QIcon("Images/sortUP.png"));
            ButtonSortStatus = sortA_Z;
        }
        });


    TextTop->setAlignment(Qt::AlignCenter);

    LayoutTop->addWidget(TextTop, 0);
    LayoutTop->addWidget(ButtonSort, 1);

    this->layout->addWidget(WidgetTop);
    this->layout->addWidget(WidgetScroll);

    // Гіфка завантаження
    QLabel* gifLoad = new QLabel(WidgetCapasity);
    QMovie* gif = new QMovie("Images/load.gif");
    gif->setScaledSize(QSize(50, 50));
    gifLoad->setMovie(gif);
    LayoutCapasity->addWidget(gifLoad, 0, 0);
    gifLoad->setAlignment(Qt::AlignCenter);
    gif->start();

    // Таймер для поступового додавання віджетів
    QTimer* timer = new QTimer(mainWedgetTools);

    mainWedgetTools->setEnabled(false);
    QApplication::setOverrideCursor(Qt::BusyCursor);
    // Підключення таймера до функції
    QObject::connect(timer, &QTimer::timeout,
        [ mainWedgetTools, timer, WidgetCapasity, gif, gifLoad, LayoutCapasity, workDB]() mutable {
            if (workDB(LayoutCapasity, WidgetCapasity)) {
                QTimer::singleShot(500, [&mainWedgetTools, &gif, &gifLoad]() {
                    gif->stop();
                    gif->deleteLater();
                    gifLoad->deleteLater();
                    mainWedgetTools->setEnabled(true);  // Розблокування вікна
                    QApplication::restoreOverrideCursor();
                    });
                timer->stop();
            }
        }
    );
    timer->start();

    WidgetScroll->setStyleSheet(
        "QScrollArea {"
        "   border: none;"
        "   background-color: transparent;"
        "}"
        "QScrollBar:vertical {"
        "    width: 10px;"
        "    margin: 0px;"
        "    padding: 0px;"
        "    border-radius: 10px;"
        "    background-color: rgb(90,90,90);"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: rgb(64,64,64);"
        "    min-height: 20px;"
        "    border-radius: 5px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    height: 0px;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "    background: none;" //ось це прибирає прозорість блоку, де знаходиться повзунок 
        "}"
    );
    WidgetCapasity->setStyleSheet(
        "QWidget {"
        "   background: transparent;"
        "}"
    );
    timer->start(0);
}

int counterTimer::operator ++ () {
    return ++this->counter;
}
int counterTimer::operator -- () {
    return --this->counter;
}
int counterTimer::operator ++ (int) {
    return this->counter++;
}
int counterTimer::operator -- (int) {
    return this->counter--;
}