#ifndef STUDINFO_H
#define STUDINFO_H
#include <qstring.h>
#include <qvector.h>

class SubjectInfo {
private:
    QString Subject = "";
    QVector<QString> Grades = {};

public:
    // Конструктори
    SubjectInfo() = default;
    SubjectInfo(const QString& subject, const QVector<QString>& grades)
        : Subject(subject), Grades(grades) {}
    SubjectInfo(const QString& subject, const QStringList& grades, bool tmp) //FIXIT поточний і попередній конструктори конфліктують
        : Subject(subject), Grades(grades.toVector()) {}

    // Геттери
    QString getSubject() const { return Subject; }
    QVector<QString> getGrades() const { return Grades; }

    // Сеттер
    void setGrades(const QVector<QString>& grades) { Grades = grades; }

    // Оператори порівняння
    friend bool operator<(const SubjectInfo& sub1, const SubjectInfo& sub2);
    friend bool operator>(const SubjectInfo& sub1, const SubjectInfo& sub2);
};

class Faculty {
private:
    QString Specialty = "";
    QString FacultyName = "";

public:
    Faculty() = default;
    Faculty(const QString& specialty, const QString& faculty)
        : Specialty(specialty), FacultyName(faculty) {}

    QString getSpecialty() const { return Specialty; }
    QString getFacultyName() const { return FacultyName; }
};

class Group {
private:
    QString Specialty = "";
    QString FacultyName = "";
    QString GroupName = "";

public:
    Group() = default;
    Group(const QString& specialty, const QString& faculty, const QString& group)
        : Specialty(specialty), FacultyName(faculty), GroupName(group) {}

    QString getSpecialty() const { return Specialty; }
    QString getFacultyName() const { return FacultyName; }
    QString getGroupName() const { return GroupName; }
};

class FullName {
private:
    QString Specialty = "";
    QString FacultyName = "";
    QString GroupName = "";
    QString FullNameString = "";

public:
    FullName() = default;
    FullName(const QString& specialty, const QString& faculty, const QString& group, const QString& fullname)
        : Specialty(specialty), FacultyName(faculty), GroupName(group), FullNameString(fullname) {}

    QString getSpecialty() const { return Specialty; }
    QString getFacultyName() const { return FacultyName; }
    QString getGroupName() const { return GroupName; }
    QString getFullName() const { return FullNameString; }

    void setSpecialty(const QString& Specialty)  {  this->Specialty = Specialty; }
    void setFacultyName(const QString& FacultyName)  {  this->FacultyName = FacultyName; }
    void setGroupName(const QString& GroupName)  {  this->GroupName = GroupName; }
    void setFullName(const QString& FullNameString)  {  this->FullNameString = FullNameString; }
};

class StudInfo {
private:
    QString StudFullName = "";
    QString StudSpecialty = "";
    QString StudGroup = "";
    QString StudFaculty = "";
    QVector<SubjectInfo> StudSubjects = {};

public:
    // Конструктори
    StudInfo() = default;
    StudInfo(const QString& studFullName, const QString& studSpecialty,
        const QString& studGroup, const QString& studFaculty, const QVector<SubjectInfo>& studSubjects = {})
        : StudFullName(studFullName), StudSpecialty(studSpecialty),
        StudGroup(studGroup), StudFaculty(studFaculty), StudSubjects(studSubjects) {}

    // Оператори порівняння
    friend bool operator<(const StudInfo& exmpl1, const StudInfo& exmpl2);
    friend bool operator>(const StudInfo& exmpl1, const StudInfo& exmpl2);
    friend bool operator==(const StudInfo& exmpl1, const StudInfo& exmpl2);
    friend bool operator!=(const StudInfo& exmpl1, const StudInfo& exmpl2);

    // Геттери
    QString getStudFullName() const { return StudFullName; }
    QString getStudSpecialty() const { return StudSpecialty; }
    QString getStudGroup() const { return StudGroup; }
    QString getStudFaculty() const { return StudFaculty; }
    const QVector<SubjectInfo>& getStudSubjects() const { return StudSubjects; }
    QVector<SubjectInfo>& getStudSubjectsWConst() { return StudSubjects; }

    // Сеттери
    void setStudFullName(const QString& studFullName) { StudFullName = studFullName; }
    void setStudSpecialty(const QString& studSpecialty) { StudSpecialty = studSpecialty; }
    void setStudGroup(const QString& studGroup) { StudGroup = studGroup; }
    void setStudFaculty(const QString& studFaculty) { StudFaculty = studFaculty; }

    // Методи додавання і вилучення предметів
    void addSubject(const QString& subjectName, const QVector<QString>& grades);
    bool removeSubject(const QString& subjectName);
};

class StudentBlock {
private:
    QVector<QString> Specialties;
    QVector<Faculty> Faculties;
    QVector<Group> Groups;
    QVector<FullName> Names;
    QVector<StudInfo> Students;

    QVector<QString*> SpecialtyBuffer;
    QVector<Faculty*> FacultyBuffer;
    QVector<Group*> GroupBuffer;
    QVector<FullName*> NameBuffer;
    QVector<StudInfo*> StudentsBuffer;

public:
    // Конструктори
    StudentBlock() = default;
    StudentBlock(const QVector<StudInfo>& initialStudents) : Students(initialStudents) {}

    // Геттери
    const QVector<StudInfo>& getStudents() const { return Students; }
    QVector<StudInfo>& getStudentsWConst() { return Students; }
    
    void clearAllData() {
        this->Specialties.clear();
        this->Faculties.clear();
        this->Groups.clear();
        this->Names.clear();
        this->Students.clear();
    }


    const QVector< StudInfo*>& getStudentsBuffer() const { return StudentsBuffer; }
    QVector< StudInfo*>& getNonConstStudentBuffer() { return StudentsBuffer; }
    const QVector< QString*>& getSpecBuffer() const { return SpecialtyBuffer; }
    const QVector< Faculty*>& getFacultyBuffer() const { return FacultyBuffer; }
    const QVector< Group*>& getGroupBuffer() const { return GroupBuffer; }
    const QVector< FullName*>& getNameBuffer() const { return NameBuffer; }


    // Додавання елементів
    bool addSpecialty(const QString& specialty);
    bool addFaculty(const QString& specialty, const QString& faculty);
    bool addGroup(const QString& specialty, const QString& faculty, const QString& group);
    bool addName(const QString& specialty, const QString& faculty, const QString& group, const QString& fullName);
    bool addSubject(const QString& specialty, const QString& faculty, const QString& group,
                    const QString& fullName, const QString& subjectName, const QVector<QString>& grades);
    void addStudent(const StudInfo& student);

    // Видалення елементів
    bool removeSpecialty(const QString& specialty);
    bool removeFaculty(const QString& specialty, const QString& faculty);
    bool removeGroup(const QString& specialty, const QString& faculty, const QString& group);
    bool removeName(const QString& specialty, const QString& faculty, const QString& group, const QString& fullName);
    bool removeSubject(const QString& specialty, const QString& faculty, const QString& group,
        const QString& fullName, const QString& subject);
    bool removeStudent(const QString& fullName);

    /*TODO: РОЗРОБИТИ СОРТУВАННЯ ДЛЯ БУФЕРІВ ( ПОМІСТИТИ В КІНЕЦЬ МЕТОДІВ ФІЛЬТРАЦІЙ )


                        ОГОЛОСИТИ МОЖНА ОСЬ ТУТ :) :(

    */

    // Методи ФІЛЬТРАЦІЇ
    void filterBySpec(const QString& specialty = "");
    void filterByFac(const QString& specialty = "", const QString& faculty = "");
    void filterByGroup(const QString& specialty = "", const QString& faculty = "", const QString& group = "");
    void filterByName(const QString& specialty = "", const QString& faculty = "", const QString& group = "", const QString& name = "");
    void filterByCriteria(const QString& specialty = "", const QString& faculty = "", const QString& group = "", const QString& name = "", const QString& subject = "");

    // Буферні операції
    StudInfo* findInBuffer(const QString& fullName);
    QVector<StudInfo*>& getbuffer();

};

#endif // STUDINFO_H
