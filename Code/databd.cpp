#include "mainWindow.h"

void CreateTables() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("mydatabase.db");
   // dropAllTables();
    if (db.open()) {
        cqdout << "Database is open.";
        QSqlQuery query;
        // ������� ��� �������������
        if (!query.exec(
            "CREATE TABLE IF NOT EXISTS specialty ("
            "id INTEGER PRIMARY KEY,"
            "specialty TEXT);"
        )) {
            cqdout << "Error creating specialty table:" << query.lastError().text();
        }

        // ������� ��� ����������
        if (!query.exec(
            "CREATE TABLE IF NOT EXISTS faculty ("
            "id INTEGER PRIMARY KEY,"
            "specialty TEXT,"
            "faculty TEXT);"
        )) {
            cqdout << "Error creating faculty table:" << query.lastError().text();
        }

        // ������� ��� ����
        if (!query.exec(
            "CREATE TABLE IF NOT EXISTS class_group ("
            "id INTEGER PRIMARY KEY,"
            "specialty TEXT,"
            "faculty TEXT,"
            "class_group INTEGER);"
        )) {
            cqdout << "Error creating class_group table:" << query.lastError().text();
        }

        // ������� ��� ��������
        if (!query.exec(
            "CREATE TABLE IF NOT EXISTS students ("
            "id INTEGER PRIMARY KEY,"
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
    // Перевірка на повтор

    query.prepare("SELECT COUNT(*) FROM specialty WHERE specialty = :specialty");
    query.bindValue(":specialty", specialty);

    if (!query.exec()) {
        qDebug() << "Error checking specialty existence:" << query.lastError().text();
        return;
    }

    if (query.next() && query.value(0).toInt() > 0) {
        qDebug() << "Error: Specialty already exists:" << specialty;
        return;
    }
    // Видача ID
    int nextId = getNextAvailableId(query, "specialty", "id");

    if (nextId != -1) {
        qDebug() << "Next available ID for specialty is:" << nextId;
    }
    else {
        qDebug() << "No available IDs.";
    }
    query.prepare("INSERT INTO specialty (id, specialty) VALUES (:id, :specialty)");
    query.bindValue(":id", nextId);
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

    query.prepare("SELECT COUNT(*) FROM specialty WHERE specialty = :specialty");
    query.bindValue(":specialty", specialty);
    if (!query.exec() || !query.next() || query.value(0).toInt() == 0) {
        cqdout << "This specialty is not exist";
        return;
    }

    // Перевірка на повтор

    query.prepare("SELECT COUNT(*) FROM faculty WHERE faculty = :faculty");
    query.bindValue(":faculty", faculty);

    if (!query.exec()) {
        qDebug() << "Error checking faculty existence:" << query.lastError().text();
        return;
    }

    if (query.next() && query.value(0).toInt() > 0) {
        qDebug() << "Error: Faculty already exists:" << faculty;
        return;
    }
    // Видача ID
    int nextId = getNextAvailableId(query, "faculty", "id");

    if (nextId != -1) {
        qDebug() << "Next available ID for faculty is:" << nextId;
    }
    else {
        qDebug() << "No available IDs.";
    }
    query.prepare("INSERT INTO faculty (id, specialty, faculty) VALUES (:id, :specialty, :faculty)");
    query.bindValue(":id", nextId);
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
    // Перевірка існування спеціальності
    query.prepare("SELECT COUNT(*) FROM specialty WHERE specialty = :specialty");
    query.bindValue(":specialty", specialty);
    if (!query.exec() || !query.next() || query.value(0).toInt() == 0) {
        cqdout << "This specialty is not exist";
        return;
    }

    // Перевірка існування факультету
    query.prepare("SELECT COUNT(*) FROM faculty WHERE faculty = :faculty AND specialty = :specialty");
    query.bindValue(":specialty", specialty);
    query.bindValue(":faculty", faculty);
    if (!query.exec() || !query.next() || query.value(0).toInt() == 0) {
        cqdout << "This faculty is not exist";
        return;
    }

    // Перевірка на повтор

    query.prepare("SELECT COUNT(*) FROM class_group WHERE class_group = :class_group");
    query.bindValue(":class_group", class_group);

    if (!query.exec()) {
        qDebug() << "Error checking class_group existence:" << query.lastError().text();
        return;
    }

    if (query.next() && query.value(0).toInt() > 0) {
        qDebug() << "Error: Group already exists:" << class_group;
        return;
    }
    // Видача id
    int nextId = getNextAvailableId(query, "class_group", "id");

    if (nextId != -1) {
        qDebug() << "Next available ID for group is:" << nextId;
    }
    else {
        qDebug() << "No available IDs.";
    }
    query.prepare("INSERT INTO class_group (id, specialty, faculty, class_group) VALUES (:id, :specialty, :faculty, :class_group)");
    query.bindValue(":id", nextId);
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

    // Перевірка існування спеціальності
    query.prepare("SELECT COUNT(*) FROM specialty WHERE specialty = :specialty");
    query.bindValue(":specialty", specialty);
    if (!query.exec() || !query.next() || query.value(0).toInt() == 0) {
        cqdout << "This specialty is not exist";
        return;
    }

    // Перевірка існування факультету
    query.prepare("SELECT COUNT(*) FROM faculty WHERE faculty = :faculty AND specialty = :specialty");
    query.bindValue(":specialty", specialty);
    query.bindValue(":faculty", faculty);
    if (!query.exec() || !query.next() || query.value(0).toInt() == 0) {
        cqdout << "This faculty is not exist";
        return;
    }

    // Перевірка існування групи
    query.prepare("SELECT COUNT(*) FROM class_group WHERE faculty = :faculty AND specialty = :specialty AND class_group = :class_group");
    query.bindValue(":specialty", specialty);
    query.bindValue(":faculty", faculty);
    query.bindValue(":class_group", class_group);
    if (!query.exec() || !query.next() || query.value(0).toInt() == 0) {
        cqdout << "This group is not exist";
        return;
    }

    // Перевірка на повтор

    query.prepare("SELECT COUNT(*) FROM students WHERE name = :name AND class_group = :class_group");
    query.bindValue(":name", name);
    query.bindValue(":class_group", class_group);

    if (!query.exec()) {
        qDebug() << "Error checking name existence in the specified group:" << query.lastError().text();
        return;
    }

    if (query.next() && query.value(0).toInt() > 0) {
        qDebug() << "Error: A student with this name already exists in group:" << class_group;
        return;
    }
    // Видача id
    int nextId = getNextAvailableId(query, "students", "id");

    if (nextId != -1) {
        qDebug() << "Next available ID for students is:" << nextId;
    }
    else {
        qDebug() << "No available IDs.";
    }
    query.prepare("INSERT INTO students (id, name, specialty, faculty, class_group) "
        "VALUES (:id, :name, :specialty, :faculty, :class_group)");
    query.bindValue(":id", nextId);
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

void DeleteSpecialty(QSqlQuery& query, const QString& specialty) {
    // Перевірка наявності факультету в таблиці
    query.prepare("SELECT id FROM specialty WHERE specialty = :specialty");
    query.bindValue(":specialty", specialty);

    if (!query.exec()) {
        qDebug() << "Error checking specialty existence:" << query.lastError().text();
        return;
    }

    if (!query.next()) {
        qDebug() << "Error: No such specialty found";
        return;
    }

    // Беремо айді факультети
    int specialtyid = query.value(0).toInt();

    // Видаляємо всі факультети з таким айді
    query.prepare("DELETE FROM specialty WHERE id = :id");
    query.bindValue(":id", specialtyid);

    if (!query.exec()) {
        qDebug() << "Error deleting specialty:" << query.lastError().text();
    }
    else {
        qDebug() << "Specialty deleted successfully with id:" << specialtyid;
    }
}

void DeleteFaculty(QSqlQuery& query, const QString& specialty, const QString& faculty) {
    // Перевірка наявності факультету в таблиці
    query.prepare("SELECT id FROM faculty WHERE faculty = :faculty");
    query.bindValue(":faculty", faculty);

    if (!query.exec()) {
        qDebug() << "Error checking faculty existence:" << query.lastError().text();
        return;
    }

    if (!query.next()) {
        qDebug() << "Error: No such faculty found";
        return;
    }

    // Беремо айді факультети
    int facultyid = query.value(0).toInt();

    // Видаляємо всі факультети з таким айді
    query.prepare("DELETE FROM faculty WHERE id = :id");
    query.bindValue(":id", facultyid);

    if (!query.exec()) {
        qDebug() << "Error deleting faculty:" << query.lastError().text();
    }
    else {
        qDebug() << "Faculty deleted successfully with id:" << facultyid;
    }
}

void DeleteGroup(QSqlQuery& query, const QString& specialty, const QString& faculty, int class_group){
    // Перевірка наявності групи в таблиці
    query.prepare("SELECT id FROM class_group WHERE class_group = :class_group");
    query.bindValue(":class_group", class_group);

    if (!query.exec()) {
        qDebug() << "Error checking group existence:" << query.lastError().text();
        return;
    }

    if (!query.next()) {
        qDebug() << "Error: No such group found";
        return;
    }

    // Беремо айді групи
    int groupid = query.value(0).toInt();

    // Видаляємо всіх групи з таким айді
    query.prepare("DELETE FROM class_group WHERE id = :id");
    query.bindValue(":id", groupid);

    if (!query.exec()) {
        qDebug() << "Error deleting group:" << query.lastError().text();
    }
    else {
        qDebug() << "Group deleted successfully with id:" << groupid;
    }
}

void DeleteStudent(QSqlQuery& query, const QString& name, const QString& specialty, const QString& faculty, int class_group) {
    // Перевірка наявності студента в групі 
    query.prepare("SELECT id FROM students WHERE name = :name AND class_group = :class_group");
    query.bindValue(":name", name);
    query.bindValue(":class_group", class_group);

    if (!query.exec()) {
        qDebug() << "Error checking student existence:" << query.lastError().text();
        return;
    }

    if (!query.next()) {
        qDebug() << "Error: No such student found in the specified group";
        return;
    }

    // Беремо айді студента
    int studentId = query.value(0).toInt();

    // Видаляємо всіх студентів з таким айді
    query.prepare("DELETE FROM students WHERE id = :id");
    query.bindValue(":id", studentId);

    if (!query.exec()) {
        qDebug() << "Error deleting student:" << query.lastError().text();
    }
    else {
        qDebug() << "Student deleted successfully with id:" << studentId;
    }
}

int getNextAvailableId(QSqlQuery& query, const QString& table, const QString& idField) {
    // Отримаємо всі айді з таблиці
    query.prepare(QString("SELECT %1 FROM %2 ORDER BY %1 ASC").arg(idField, table));
    if (!query.exec()) {
        qDebug() << "Error checking available IDs:" << query.lastError().text();
        return -1;  // Помилка
    }

    QVector<int> usedIds;
    while (query.next()) {
        usedIds.push_back(query.value(0).toInt());
    }

    // Пошук мінімального айді
    int nextId = 1;
    while (usedIds.contains(nextId)) {
        ++nextId;
    }

    return nextId;
}

// Функция для полной очистки бд
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