#include "mainWindow.h"
#include "ex.h"

void CreateTables() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("mydatabase.db");
   // dropAllTables();
    if (db.open()) {
        cqdout << "Database is open.";
        QSqlQuery query;
        query.exec("PRAGMA foreign_keys = ON;");
        // БД для спеціальностей
        if (!query.exec(
            "CREATE TABLE IF NOT EXISTS specialty ("
            "id INTEGER PRIMARY KEY,"
            "specialty TEXT);"
        )) {
            cqdout << "Error creating specialty table:" << query.lastError().text();
        }

        // БД для факультетів
        if (!query.exec(
            "CREATE TABLE IF NOT EXISTS faculty ("
            "id INTEGER PRIMARY KEY,"
            "specialty TEXT,"
            "faculty TEXT);"
        )) {
            cqdout << "Error creating faculty table:" << query.lastError().text();
        }

        // БД для груп
        if (!query.exec(
            "CREATE TABLE IF NOT EXISTS class_group ("
            "id INTEGER PRIMARY KEY,"
            "specialty TEXT,"
            "faculty TEXT,"
            "class_group INTEGER);"
        )) {
            cqdout << "Error creating class_group table:" << query.lastError().text();
        }

        // БД для студентів
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

        // БД для предметів
        if (!query.exec(
            "CREATE TABLE IF NOT EXISTS predmet ("
            "id INTEGER PRIMARY KEY,"
            "predmet TEXT,"
            "student_id TEXT,"
            "FOREIGN KEY(student_id) REFERENCES students(id)"
            " ON DELETE CASCADE"  // Видаляє предмет, якщо видален студент
            " ON UPDATE CASCADE"  // Оновлює посилання при зміненні айді
            ");"
        ))  {
            cqdout << "Error creating predmet table:" << query.lastError().text();
        }

        // БД для оцінок
        if (!query.exec(
            "CREATE TABLE IF NOT EXISTS grades ("
            "id INTEGER PRIMARY KEY, " 
            "predmet_id TEXT,"
            "student_id TEXT,"
            "grade TEXT, "   
            "FOREIGN KEY(predmet_id) REFERENCES predmet(id),"
            "FOREIGN KEY(student_id) REFERENCES students(id)"
            " ON DELETE CASCADE "
            " ON UPDATE CASCADE "
            ");"
        )) {
            cqdout << "Error creating grades table:" << query.lastError().text();
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
        throw ex(-1, "Спеціальність вже існує!");
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
        throw ex(-1, "Неможливо створити факультет! Немає спеціальності!");
    }


    query.prepare("SELECT COUNT(*) FROM faculty WHERE faculty = :faculty");
    query.bindValue(":faculty", faculty);

    if (!query.exec()) {
        qDebug() << "Error checking faculty existence:" << query.lastError().text();
        return;
    }

    if (query.next() && query.value(0).toInt() > 0) {
        qDebug() << "Error: Faculty already exists:" << faculty;
        throw ex(-1, "Факультет вже існує!");
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

void addGroup(QSqlQuery& query, const QString& specialty, const QString& faculty, const QString& class_group) {
    // Перевірка існування спеціальності
    query.prepare("SELECT COUNT(*) FROM specialty WHERE specialty = :specialty");
    query.bindValue(":specialty", specialty);
    if (!query.exec() || !query.next() || query.value(0).toInt() == 0) {
        cqdout << "This specialty is not exist";
        throw ex(-1, "Неможливо створити групу! Немає спеціальності!");
    }

    // Перевірка існування факультету
    query.prepare("SELECT COUNT(*) FROM faculty WHERE faculty = :faculty AND specialty = :specialty");
    query.bindValue(":specialty", specialty);
    query.bindValue(":faculty", faculty);
    if (!query.exec() || !query.next() || query.value(0).toInt() == 0) {
        cqdout << "This faculty is not exist";
        throw ex(-1, "Неможливо створити групу! Немає факультету!");
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
        throw ex(-1, "Група вже існує!");
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

void addStudent(QSqlQuery& query, const QString& name, const QString& specialty, const QString& faculty, const QString& class_group) {

    // Перевірка існування спеціальності
    query.prepare("SELECT COUNT(*) FROM specialty WHERE specialty = :specialty");
    query.bindValue(":specialty", specialty);
    if (!query.exec() || !query.next() || query.value(0).toInt() == 0) {
        cqdout << "This specialty is not exist";
        throw ex(-1, "Неможливо додати студента! Немає факультету!");

    }

    // Перевірка існування факультету
    query.prepare("SELECT COUNT(*) FROM faculty WHERE faculty = :faculty AND specialty = :specialty");
    query.bindValue(":specialty", specialty);
    query.bindValue(":faculty", faculty);
    if (!query.exec() || !query.next() || query.value(0).toInt() == 0) {
        cqdout << "This faculty is not exist";
        throw ex(-1, "Неможливо додати студента! Немає факультету!");
    }

    // Перевірка існування групи
    query.prepare("SELECT COUNT(*) FROM class_group WHERE faculty = :faculty AND specialty = :specialty AND class_group = :class_group");
    query.bindValue(":specialty", specialty);
    query.bindValue(":faculty", faculty);
    query.bindValue(":class_group", class_group);
    if (!query.exec() || !query.next() || query.value(0).toInt() == 0) {
        cqdout << "This group is not exist";
        throw ex(-1, "Неможливо додати студента! Немає групи!");
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
        throw ex(-1, "Студент вже існує!");
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

void addSubject(QSqlQuery& query, const QString& predmet, int studentId) {

    // Перевірка на повтор
    query.prepare("SELECT COUNT(*) FROM predmet WHERE predmet = :predmet AND student_id = :student_id");
    query.bindValue(":predmet", predmet);
    query.bindValue(":student_id", studentId);

    if (!query.exec()) {
        qDebug() << "Error checking subject existence:" << query.lastError().text();
        return;
    }

    if (query.next() && query.value(0).toInt() > 0) {
        qDebug() << "Error: A subject with this name already exists:" << predmet;
        throw ex(-1, "Цей предмет вже додано до студента!");
    }

    query.prepare("INSERT INTO predmet (predmet, student_id) VALUES (:predmet, :studentId)");
    query.bindValue(":predmet", predmet);
    query.bindValue(":studentId", studentId);

    if (!query.exec()) {
        qDebug() << "Error adding predmet:" << query.lastError().text();
    }
    else {
        qDebug() << "Predmet added successfully! Subject:" << predmet << ", Student ID:" << studentId;
    }

}

void addGrades(QSqlQuery& query, const QStringList& grades, int predmetId) {

    query.prepare("SELECT student_id FROM predmet WHERE id = :predmetId");
    query.bindValue(":predmetId", predmetId);

    if (!query.exec()) {
        qDebug() << "Error fetching student_id from predmet:" << query.lastError().text();
        return;
    }

    int studentId = -1;

    if (query.next()) {
        studentId = query.value("student_id").toInt();
    }
    else {
        qDebug() << "Error: No student found for predmet ID:" << predmetId;
        throw ex(-1, "Неможливо додати оцінки! Незнайдено студента!");
    }
    clearGradesForStudentAndPredmet(query, predmetId, studentId);
    for (const QString& grade : grades) {
        query.prepare("INSERT INTO grades (grade, predmet_id, student_id) VALUES (:grade, :predmetId, :studentId)");
        query.bindValue(":grade", grade); 
        query.bindValue(":predmetId", predmetId);
        query.bindValue(":studentId", studentId);

        if (!query.exec()) {
            qDebug() << "Error adding grade:" << query.lastError().text();
            break;
        }
        else {
            qDebug() << "Grade added successfully! Grade:" << grade << ", Predmet ID:" << predmetId;
        }
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
                << ", Class Group:" << query.value("class_group").toString();
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

//:todo нужно исправить логику
int getStudentIDforPredmet(QSqlQuery& query, const QString& StudyName, int studentId){
    query.prepare(
        "SELECT id FROM students "
        "WHERE specialty = :specialty AND faculty = :faculty "
        "AND class_group = :classGroup AND name = :StudyName"
    );
    query.bindValue(":specialty", "1"); // specialty
    query.bindValue(":faculty", "1"); // faculty
    query.bindValue(":classGroup", "Групи"); // class_group
    query.bindValue(":StudyName", "Студенти"); // name

    if (query.exec() && query.next()) {
        studentId = query.value(0).toInt();
        return studentId;
    }
    else {
        cqdout << "Error: Cannot find student ID. Reason:" << query.lastError().text();
        return studentId = -1;
    }
}

int getPredmetId(QSqlQuery& query, const QString& predmet, int predmetId) {
    query.prepare(
        "SELECT id FROM predmet "
        "WHERE predmet = :predmet;"
    );
    
    query.bindValue(":predmet", "Предмети"); // predmet

    if (query.exec() && query.next()) {
        predmetId = query.value(0).toInt(); 
        return predmetId;
    }
    else {
        cqdout << "Error: Cannot find predmet ID. Reason:" << query.lastError().text();
        return predmetId = -1;
    }
}

void getGrades(QSqlQuery& query, const QStringList& grades, int predmetId) {

    query.prepare("SELECT student_id FROM predmet WHERE id = :predmetId;");
    query.bindValue(":predmetId", predmetId);

    if (!query.exec()) {
        qDebug() << "Error fetching student_id from predmet:" << query.lastError().text();
        return;
    }

    int studentId = -1;

    if (query.next()) {
        studentId = query.value("student_id").toInt();
    }
    else {
        qDebug() << "Error: No student found for predmet ID:" << predmetId;
        return;
    }

    query.prepare("SELECT grade FROM grades WHERE predmet_id = :predmet_id AND student_id = :student_id;");
    query.bindValue(":predmet_id", predmetId);
    query.bindValue(":student_id", studentId);

    if (!query.exec()) {
        qDebug() << "Error getting grade:" << query.lastError().text();
        return;
    }

    bool found = false;
    while (query.next()) {
        found = true;
        cqdout << "Grade:" << query.value("grade").toString();
    }

    if (!found) {
        cqdout << "No grade found in the database.";
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
        throw ex(0, "Cпеціальності не знайдено!");
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
        throw ex(0, "Факультет не знайдено!");
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

void DeleteGroup(QSqlQuery& query, const QString& specialty, const QString& faculty, const QString& class_group){
    // Перевірка наявності групи в таблиці
    query.prepare("SELECT id FROM class_group WHERE class_group = :class_group");
    query.bindValue(":class_group", class_group);

    if (!query.exec()) {
        qDebug() << "Error checking group existence:" << query.lastError().text();
        return;
    }

    if (!query.next()) {
        qDebug() << "Error: No such group found";
        throw ex(0, "Групу не знайдено!");
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

void DeleteStudent(QSqlQuery& query, const QString& name, const QString& specialty, const QString& faculty, const QString& class_group) {
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
        throw ex(0, "Студента не знайдено!");
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

void DeleteSubject(QSqlQuery& query, const QString& predmet, int studentId) {

    query.prepare("SELECT id FROM predmet WHERE predmet = :predmet AND student_id = :student_id");
    query.bindValue(":predmet", predmet);
    query.bindValue(":student_id", studentId);

    if (!query.exec()) {
        qDebug() << "Error checking subject existence:" << query.lastError().text();
        return;
    }

    if (!query.next()) {
        qDebug() << "Error: This subject does not exist!" << predmet;
        throw ex(-1, "Цього предмету не існує!");
    }

    int predmetId = query.value(0).toInt();

    // Видалення оцінок , які прив'язані до цього предмету
    query.prepare("DELETE FROM grades WHERE predmet_id = :predmetId");
    query.bindValue(":predmetId", predmetId);

    if (!query.exec()) {
        qDebug() << "Error deleting grades for subject ID:" << predmetId << ". Error:" << query.lastError().text();
        return;
    }
    else {
        qDebug() << "Grades deleted successfully for subject ID:" << predmetId;
    }

    // Видалення предмету
    query.prepare("DELETE FROM predmet WHERE id = :predmetId");
    query.bindValue(":predmetId", predmetId);

    if (!query.exec()) {
        qDebug() << "Error deleting subject:" << query.lastError().text();
    }
    else {
        qDebug() << "Subject deleted successfully. Predmet:" << predmet << ", Student ID:" << studentId;
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

QStringList initializeSpecialties(QSqlQuery& query) {
    QStringList specialties;
    if (!query.exec("SELECT * FROM specialty;")) {
        qDebug() << "Error fetching specialties:" << query.lastError().text();
        return specialties;
    }

    while (query.next()) {
        QString specialtyData = QString("ID: %1, Specialty: %2")
            .arg(query.value("id").toInt())
            .arg(query.value("specialty").toString());
        specialties << specialtyData;
    }
    return specialties;
}

QStringList initializeFaculties(QSqlQuery& query) {
    QStringList faculties;
    if (!query.exec("SELECT * FROM faculty;")) {
        qDebug() << "Error fetching faculties:" << query.lastError().text();
        return faculties;
    }

    while (query.next()) {
        QString facultyData = QString("ID: %1, Specialty: %2, Faculty: %3")
            .arg(query.value("id").toInt())
            .arg(query.value("specialty").toString())
            .arg(query.value("faculty").toString());
        faculties << facultyData;
    }
    return faculties;
}

QStringList initializeClassGroups(QSqlQuery& query) {
    QStringList classGroups;
    if (!query.exec("SELECT * FROM class_group;")) {
        qDebug() << "Error fetching class groups:" << query.lastError().text();
        return classGroups;
    }

    while (query.next()) {
        QString classGroupData = QString("ID: %1, Specialty: %2, Faculty: %3, Class Group: %4")
            .arg(query.value("id").toInt())
            .arg(query.value("specialty").toString())
            .arg(query.value("faculty").toString())
            .arg(query.value("class_group").toInt());
        classGroups << classGroupData;
    }
    return classGroups;
}

QStringList initializeStudents(QSqlQuery& query) {
    QStringList students;
    if (!query.exec("SELECT * FROM students;")) {
        qDebug() << "Error fetching students:" << query.lastError().text();
        return students;
    }

    while (query.next()) {
        QString studentData = QString("ID: %1, Name: %2, Age: %3, Faculty: %4, Specialty: %5, Class Group: %6")
            .arg(query.value("id").toInt())
            .arg(query.value("name").toString())
            .arg(query.value("age").toInt())
            .arg(query.value("faculty").toString())
            .arg(query.value("specialty").toString())
            .arg(query.value("class_group").toInt());
        students << studentData;
    }
    return students;
}

QStringList initializePredmets(QSqlQuery& query) {
    QStringList predmets;
    if (!query.exec("SELECT * FROM predmet;")) {
        qDebug() << "Error fetching predmets:" << query.lastError().text();
        return predmets;
    }

    while (query.next()) {
        QString predmetData = QString("ID: %1, Predmet: %2, Student ID: %3")
            .arg(query.value("id").toInt())
            .arg(query.value("predmet").toString())
            .arg(query.value("student_id").toInt());
        predmets << predmetData;
    }
    return predmets;
}

QStringList initializeGrades(QSqlQuery& query) {
    QStringList grades;
    if (!query.exec("SELECT * FROM grades;")) {
        qDebug() << "Error fetching grades:" << query.lastError().text();
        return grades;
    }

    while (query.next()) {
        QString gradeData = QString("ID: %1, Grade: %2, Predmet ID: %3, Student ID: %4")
            .arg(query.value("id").toInt())
            .arg(query.value("grade").toString())
            .arg(query.value("predmet_id").toInt())
            .arg(query.value("student_id").toInt());
        grades << gradeData;
    }
    return grades;
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
void clearGradesForStudentAndPredmet(QSqlQuery& query, int predmetId, int studentId) {

    query.prepare("DELETE FROM grades WHERE predmet_id = :predmetId AND student_id = :studentId");

    query.bindValue(":predmetId", predmetId);
    query.bindValue(":studentId", studentId);

    if (!query.exec()) {
        qDebug() << "Error clearing grades:" << query.lastError().text();
    }
    else {
        qDebug() << "Grades cleared for Predmet ID:" << predmetId << "and Student ID:" << studentId;
    }
}
