#include "mainWindow.h"

//для вінди створюю консольне вікно куди в подальшому записуватиму помилки (цього в релізі не повинно бути, це якщо якісь глюки будуть)
#ifdef Q_OS_WIN
#include <Windows.h>
void createConsole() {
    if (GetConsoleWindow() == nullptr) {
        AllocConsole(); // Створюю вікно консолі 
        FILE* stream;
        freopen_s(&stream, "CONOUT$", "w", stdout); // Перенаправляю stdout у консоль
        freopen_s(&stream, "CONOUT$", "w", stderr); // Перенаправляю stderr у консоль
    }
    else cerr << "Консоль запущена!\n";
}
#endif // Q_OS_WIN

mainWindowWidget::mainWindowWidget(QWidget* parent) : QWidget(parent) {
    QGridLayout* mainLayout = new QGridLayout(this); // Створення компоновщика на основі головного вікна
    this->setStyleSheet(
        "background-color: rgb(30,30,30);"
    );
    QWidget* mainWindowRightSize = new QWidget(this); // Віджет для правої частини
    QWidget* mainWindowTable = new QWidget(this); // Віджет для таблиці
    QWidget* tableTools = new QWidget(mainWindowTable); //віджет для управління таблицею
    QWidget* table = new QWidget(mainWindowTable); //віджет для таблиці студентів

    QLineEdit* inputCourse = new QLineEdit(tableTools); //поле для введення курсу
    QLineEdit* inputSemestr = new QLineEdit(tableTools); //поле для введення семестру
    QLineEdit* inputFaculty = new QLineEdit(tableTools); //поле для введення факультету
    QLineEdit* inputGroup = new QLineEdit(tableTools); //поле для введення гурпи
    QLineEdit* inputStudent = new QLineEdit(tableTools); //поле для введення студента



    QLabel* table_is_not_created = new QLabel("Таблиця не створена (немає студентів)");
    QLabel* right_side_not_created = new QLabel("Права частина не зроблена\n (і навіть поки не дуже продумана)");


    //блокування всіх полів крім першого
    inputSemestr->setEnabled(false);
    inputFaculty->setEnabled(false);
    inputGroup->setEnabled(false);
    inputStudent->setEnabled(false);

    //об'єдную сигнал returnPressed з власним методом onEnterPressed
    /*
    returnPressed це сигнал активується коли натиснуто enter
    в моєму випадку я сигнал натиску enter об'єдную з моїм методом який повинен реагувати 
    на це (наприклад підбирати студентів у таблиці за відповідним введеним курсом)
    */
    connect(inputCourse, &QLineEdit::returnPressed, this, [inputCourse, inputSemestr]() {
        qDebug() << "Курс введений:" << inputCourse->text();
        // Розблокування наступного поля
        inputSemestr->setEnabled(true); //розблокування наступного поля вводу
        inputSemestr->setFocus();  // Фокус на наступному полі
        });
    connect(inputSemestr, &QLineEdit::returnPressed, this, [inputSemestr, inputFaculty]() {
        qDebug() << "Курс введений:" << inputSemestr->text();
        // Розблокування наступного поля
        inputFaculty->setEnabled(true); //розблокування наступного поля вводу
        inputFaculty->setFocus();  // Фокус на наступному полі
        });
    connect(inputFaculty, &QLineEdit::returnPressed, this, [inputFaculty, inputGroup]() {
        qDebug() << "Курс введений:" << inputFaculty->text();
        // Розблокування наступного поля
        inputGroup->setEnabled(true); //розблокування наступного поля вводу
        inputGroup->setFocus();  // Фокус на наступному полі
        });
    connect(inputGroup, &QLineEdit::returnPressed, this, [inputGroup, inputStudent]() {
        qDebug() << "Курс введений:" << inputGroup->text();
        // Розблокування наступного поля
        inputStudent->setEnabled(true); //розблокування наступного поля вводу
        inputStudent->setFocus();  // Фокус на наступному полі
        });
    connect(inputStudent, &QLineEdit::returnPressed, this, [inputStudent]() {
        qDebug() << "Курс введений:" << inputStudent->text();
        });


    QGridLayout* leftSideTableLayout = new QGridLayout(mainWindowTable); // Встановлення компоновщика для таблиці
    QGridLayout* tableToolsLayout = new QGridLayout(tableTools); //встановлюю компоновщик для віджету таблиці інструментів
    
    
    QGridLayout* tableLayout = new QGridLayout(table);
    QGridLayout* rightSizeLayout = new QGridLayout(mainWindowRightSize);

    inputCourse->setPlaceholderText("Курс"); //встановлення "прозорого тексту"
    inputSemestr->setPlaceholderText("Семестр");
    inputFaculty->setPlaceholderText("Факультет");
    inputGroup->setPlaceholderText("Група");
    inputStudent->setPlaceholderText("Студент");

    
    
    //стилі для віджетів
    ///////////////////////////////////////////////////////////
    mainWindowRightSize->setStyleSheet(
        "background-color: rgb(100,60,60);"
    );
    right_side_not_created->setStyleSheet(
        "font-size: 30px;"
        "color: rgb(255,255,255);"
    );
    table_is_not_created->setStyleSheet(
        "font-size: 30px;"
        "color: rgb(255,255,255);"
    );
    ///////////////////////////////////////////////////////////
    tableTools->setStyleSheet(
        "background-color: rgb(60,60,60);"
    );
    table->setStyleSheet(
        "background-color: rgb(100,60,60);"
    );
    ///////////////////////////////////////////////////////////
    tableLayout->addWidget(table_is_not_created, 0,0,1,1, Qt::AlignCenter); 
    rightSizeLayout->addWidget(right_side_not_created, 0, 0, 1, 1, Qt::AlignCenter);
    ///////////////////////////////////////////////////////////



    leftSideTableLayout->setContentsMargins(0, 0, 0, 0); // Очищення внутрішніх відступів для вкладених віджетів
    leftSideTableLayout->addWidget(tableTools, 0, 0); // Додавання віджету до компоновщика на нульовий рядок і нульовий стовпець
    leftSideTableLayout->addWidget(table, 1, 0);

    tableToolsLayout->setContentsMargins(0, 0, 0, 0); 
    tableToolsLayout->setColumnStretch(0, 1);
    tableToolsLayout->setColumnStretch(1, 1);
    tableToolsLayout->setColumnStretch(2, 1);
    tableToolsLayout->setColumnStretch(3, 1);
    tableToolsLayout->setColumnStretch(4, 1);
    tableToolsLayout->setColumnStretch(5, 4);

    tableToolsLayout->addWidget(inputCourse, 0, 0); //ввід курсу, відносно якого буде відбуватись пошук студентів
    tableToolsLayout->addWidget(inputSemestr, 0, 1); //ввід семестру
    tableToolsLayout->addWidget(inputFaculty, 0, 2);  // факультет
    tableToolsLayout->addWidget(inputGroup, 0, 3); //група
    tableToolsLayout->addWidget(inputStudent, 0, 4); //студент
    leftSideTableLayout->setRowStretch(0, 1);
    leftSideTableLayout->setRowStretch(1, 15);

    mainLayout->addWidget(mainWindowTable, 0, 0);
    mainLayout->addWidget(mainWindowRightSize, 0, 1);
    mainLayout->setColumnStretch(0, 5);
    mainLayout->setColumnStretch(1, 2);


    this->setWindowTitle("Успішність студентів"); // Заголовок вікна
    QIcon mainIcon("Images/title.png"); // Іконка для вікна програми
    this->setWindowIcon(mainIcon); // Встановлюю іконку
    this->setMinimumSize(800, 600); // Обмежую зміну розміру вікна 
   
}

void mainWindowWidget::show()  {
    createConsole(); 
    this->showMaximized(); //вікно в повному розмірі (не f11)
    
}