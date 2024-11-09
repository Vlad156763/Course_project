#include "mainWindow.h"

void CreateTables() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("mydatabase.db");

    if (db.open()) {
        cqdout << "Database is open.";
        QSqlQuery query;
        // ������� ��� �������������
        if (!query.exec(
            "CREATE TABLE IF NOT EXISTS specialty ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "specialty TEXT);"
        )) {
            cqdout << "Error creating specialty table:" << query.lastError().text();
        }

        // ������� ��� ����������
        if (!query.exec(
            "CREATE TABLE IF NOT EXISTS faculty ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "specialty TEXT,"
            "faculty TEXT);"
        )) {
            cqdout << "Error creating faculty table:" << query.lastError().text();
        }

        // ������� ��� ����
        if (!query.exec(
            "CREATE TABLE IF NOT EXISTS class_group ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "specialty TEXT,"
            "faculty TEXT,"
            "class_group INTEGER);"
        )) {
            cqdout << "Error creating class_group table:" << query.lastError().text();
        }

        // ������� ��� ��������
        if (!query.exec(
            "CREATE TABLE IF NOT EXISTS students ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT,"
            "age INTEGER,"
            "faculty TEXT,"
            "specialty TEXT,"
            "class_group INTEGER);"
        )) {
            cqdout << "Error creating students table:" << query.lastError().text();
        }

        cqdout << "Database is ready to write!";
    }
}

void addSpecialty(QSqlQuery& query, const QString& specialty) {
    query.prepare("INSERT INTO specialty (specialty) VALUES (:specialty)");
    query.bindValue(":specialty", specialty);
    if (!query.exec()) {
        cqdout << "Error adding specialty";
    }
    else {
        cqdout << "Specialty added successfully!";
        getSpecialty(query);
    }
}

void addFaculty(QSqlQuery& query, const QString& specialty, const QString& faculty) {
    query.prepare("INSERT INTO faculty (specialty, faculty) VALUES (:specialty, :faculty)");
    query.bindValue(":specialty", specialty);
    query.bindValue(":faculty", faculty);

    if (!query.exec()) {
        cqdout << "Error adding faculty" << query.lastError().text();;
    }
    else {
        cqdout << "Faculty added successfully!";
        getFaculty(query);
    }
}


void addGroup(QSqlQuery& query, const QString& specialty, const QString& faculty, int class_group) {
    query.prepare("INSERT INTO class_group (specialty, faculty, class_group) VALUES (:specialty, :faculty, :class_group)");
    query.bindValue(":specialty", specialty);
    query.bindValue(":faculty", faculty);
    query.bindValue(":class_group", class_group);

    if (!query.exec()) {
        cqdout << "Error adding group: " << query.lastError().text();
    }
    else {
        cqdout << "Group added successfully!";
        getGroup(query);
    }
}

void addStudent(QSqlQuery& query, const QString& name, const QString& specialty, const QString& faculty, int class_group) {
    query.prepare("INSERT INTO students (name, specialty, faculty, class_group) "
        "VALUES (:name, :specialty, :faculty, :class_group)");
    query.bindValue(":name", name);
    query.bindValue(":specialty", specialty);
    query.bindValue(":faculty", faculty);

    query.bindValue(":class_group", class_group);

    if (!query.exec()) {
        cqdout << "Error adding student: " << query.lastError().text();
    }
    else {
        cqdout << "Student added successfully!";
        getAllStudents(query);
    }
}

void getAllStudents(QSqlQuery& query) {
    query.prepare("SELECT students.id, students.name, students.faculty, "
        "students.specialty, students.class_group "
        "FROM students;");

    if (query.exec()) {
        bool found = false;
        while (query.next()) {
            cqdout << "ID:" << query.value("id").toInt()
                << ", Name:" << query.value("name").toString()
                << ", Faculty:" << query.value("faculty").toString()
                << ", Specialty:" << query.value("specialty").toString()
                << ", Class Group:" << query.value("class_group").toString();
            found = true;
        }
        if (!found) {
            cqdout << "No students found in the database.";
        }
    }
    else {
        cqdout << "Error fetching students: " << query.lastError().text();
    }
}

void getSpecialty(QSqlQuery& query) {
    query.prepare("SELECT specialty.id, specialty.specialty FROM specialty;");
    if (query.exec()) {
        bool found = false;
        while (query.next()) {
            cqdout << "ID:" << query.value("id").toInt()
                << ", Specialty:" << query.value("specialty").toString();
            found = true;
        }
        if (!found) {
            cqdout << "No specialty found in the database.";
        }
    }
    else {
        cqdout << "Error fetching specialty: " << query.lastError().text();
    }
}

void getFaculty(QSqlQuery& query) {
    query.prepare("SELECT faculty.id, faculty.specialty, faculty.faculty FROM faculty;");
    if (query.exec()) {
        bool found = false;
        while (query.next()) {
            cqdout << "ID:" << query.value("id").toInt()
                << ", Specialty:" << query.value("specialty").toString()
                << ", Faculty:" << query.value("faculty").toString();
            found = true;
        }
        if (!found) {
            cqdout << "No faculty found in the database.";
        }
    }
    else {
        cqdout << "Error fetching faculty: " << query.lastError().text();
    }
}

void getGroup(QSqlQuery& query) {
    query.prepare("SELECT class_group.id, class_group.specialty, class_group.faculty, class_group.class_group FROM class_group;");
    if (query.exec()) {
        bool found = false;
        while (query.next()) {
            cqdout << "ID:" << query.value("id").toInt()
                << ", Specialty:" << query.value("specialty").toString()
                << ", Faculty:" << query.value("faculty").toString()
                << ", Class Group:" << query.value("class_group").toInt();
            found = true;
        }
        if (!found) {
            cqdout << "No group found in the database.";
        }
    }
    else {
        cqdout << "Error fetching group: " << query.lastError().text();
    }
}

void dropAllTables() {
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    // ������ ���� ������ ��� ��������
    QStringList tables = { "specialty", "faculty", "class_group", "students" };

    // ���� ��� �������� ������ �������
    for (const QString& tableName : tables) {
        QString dropQuery = QString("DROP TABLE IF EXISTS %1").arg(tableName);
        if (!query.exec(dropQuery)) {
            qDebug() << "Error dropping table" << tableName << ":" << query.lastError().text();
        }
        else {
            qDebug() << "Table" << tableName << "dropped successfully!";
        }
    }
}