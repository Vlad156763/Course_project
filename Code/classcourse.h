
#pragma once
#ifndef STUDINFO_H
#define STUDINFO_H
#include "classcourse_global.h"


class SubjectInfo {
private:
    QString Subject;
    QVector<int> Grades;

public:
    // Конструктори
    SubjectInfo() = default;
    SubjectInfo(const QString& subject, const QVector<int>& grades)
        : Subject(subject), Grades(grades) {}

    // Геттери
    QString getSubject() const { return Subject; }
    QVector<int> getGrades() const { return Grades; }

    // Сеттер
    void setGrades(const QVector<int>& grades) { Grades = grades; }

    // Оператори порівняння
    friend bool operator<(const SubjectInfo& sub1, const SubjectInfo& sub2);
    friend bool operator>(const SubjectInfo& sub1, const SubjectInfo& sub2);
};

class StudInfo {
private:
    QString StudFullName;
    QString StudSpecialty;
    QString StudGroup;
    QString StudFaculty;
    QVector<SubjectInfo> StudSubjects;

public:
    // Конструктори
    StudInfo() = default;
    StudInfo(const QString& studFullName, const QString& studSpecialty,
        const QString& studGroup, const QString& studFaculty)
        : StudFullName(studFullName), StudSpecialty(studSpecialty),
        StudGroup(studGroup), StudFaculty(studFaculty) {}

    //Оператори порівняння
    friend bool operator<(const StudInfo& exmpl1, const StudInfo& exmpl2);
    friend bool operator>(const StudInfo& exmpl1, const StudInfo& exmpl2);
    friend bool operator ==(const StudInfo& exmpl1, const StudInfo& exmpl2);
    friend bool operator!=(const StudInfo& exmpl1, const StudInfo& exmpl2);



    // Геттери
    QString getStudFullName() const { return StudFullName; }
    QString getStudSpecialty() const { return StudSpecialty; }
    QString getStudGroup() const { return StudGroup; }
    QString getStudFaculty() const { return StudFaculty; }
    const QVector<SubjectInfo>& getStudSubjects() const { return StudSubjects; }

    // Сеттери
    void setStudFullName(const QString& studFullName) { StudFullName = studFullName; }
    void setStudSpecialty(const QString& studSpecialty) { StudSpecialty = studSpecialty; }
    void setStudGroup(const QString& studGroup) { StudGroup = studGroup; }
    void setStudFaculty(const QString& studFaculty) { StudFaculty = studFaculty; }

    // Методи додавання і вилучення предметів
    void addSubject(const QString& subjectName, const QVector<int>& grades);
    bool removeSubject(const QString& subjectName);
};
class StudentBlock {
private:
    QVector<StudInfo> students;              // Основний масив студентів та всієї інфо
    QVector<const StudInfo*> specialtyBuffer; // Буферний масив покажчиків для однієї спеціальності

public:

    //конструктори
    StudentBlock() {}
    StudentBlock(const QVector<StudInfo>& initialStudents) : students(initialStudents) {}

    //геттери
    const QVector<StudInfo>& getStudents() const { return students; }
    const QVector<const StudInfo*>& getSpecialtyBuffer() const { return specialtyBuffer; }

    // Додавання студента в масив
    void addStudent(const StudInfo& student);

    // Видалення студента з масиву
    bool removeStudent(const QString& fullName);

    // Видалення групи
   // bool removeGroup(const QString& group);

    // Видалення факультету
   // bool removeFaculty(const QString& faculty);

    // Видалення спеціальності
    //bool removeSpecialty(const QString& specialty);

    // Фільтрація студентів за критеріями на власний вибір
    void filterByCriteria(const QString& specialty = "",
        const QString& faculty = "",
        const QString& group = "",
        const QString& name = "",
        const QString& subject = "");

    // Сортування буферу за групою
    void sortBufferByGroup();
};



#endif // STUDINFO_H



  


