#pragma once
#ifndef STUDINFO_H
#define STUDINFO_H
#include "classcourse_global.h"


class SubjectInfo {
private:
    QString Subject;
    QVector<int> Grades;

public:
    // ������������
    SubjectInfo() = default;
    SubjectInfo(const QString& subject, const QVector<int>& grades)
        : Subject(subject), Grades(grades) {}

    // �������
    QString getSubject() const { return Subject; }
    QVector<int> getGrades() const { return Grades; }

    // ������
    void setGrades(const QVector<int>& grades) { Grades = grades; }

    // ��������� ���������
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
    // ������������
    StudInfo() = default;
    StudInfo(const QString& studFullName, const QString& studSpecialty,
        const QString& studGroup, const QString& studFaculty)
        : StudFullName(studFullName), StudSpecialty(studSpecialty),
        StudGroup(studGroup), StudFaculty(studFaculty) {}

    //��������� ���������
    friend bool operator<(const StudInfo& exmpl1, const StudInfo& exmpl2);
    friend bool operator>(const StudInfo& exmpl1, const StudInfo& exmpl2);
    friend bool operator ==(const StudInfo& exmpl1, const StudInfo& exmpl2);
    friend bool operator!=(const StudInfo& exmpl1, const StudInfo& exmpl2);



    // �������
    QString getStudFullName() const { return StudFullName; }
    QString getStudSpecialty() const { return StudSpecialty; }
    QString getStudGroup() const { return StudGroup; }
    QString getStudFaculty() const { return StudFaculty; }
    const QVector<SubjectInfo>& getStudSubjects() const { return StudSubjects; }

    // �������
    void setStudFullName(const QString& studFullName) { StudFullName = studFullName; }
    void setStudSpecialty(const QString& studSpecialty) { StudSpecialty = studSpecialty; }
    void setStudGroup(const QString& studGroup) { StudGroup = studGroup; }
    void setStudFaculty(const QString& studFaculty) { StudFaculty = studFaculty; }

    // ������ ��������� � ��������� ��������
    void addSubject(const QString& subjectName, const QVector<int>& grades);
    bool removeSubject(const QString& subjectName);
};
class StudentBlock {
private:
    QVector<StudInfo> students;              // �������� ����� �������� �� �񳺿 ����
    QVector<const StudInfo*> specialtyBuffer; // �������� ����� ��������� ��� ���� ������������

public:

    //������������
    StudentBlock() {}
    StudentBlock(const QVector<StudInfo>& initialStudents) : students(initialStudents) {}

    //�������
    const QVector<StudInfo>& getStudents() const { return students; }
    const QVector<const StudInfo*>& getSpecialtyBuffer() const { return specialtyBuffer; }

    // ��������� �������� � �����
    void addStudent(const StudInfo& student);

    // ��������� �������� � ������
    bool removeStudent(const QString& fullName);

    // ��������� �����
   // bool removeGroup(const QString& group);

    // ��������� ����������
   // bool removeFaculty(const QString& faculty);

    // ��������� ������������
    //bool removeSpecialty(const QString& specialty);

    // Գ�������� �������� �� ��������� �� ������� ����
    void filterByCriteria(const QString& specialty = "",
        const QString& faculty = "",
        const QString& group = "",
        const QString& name = "",
        const QString& subject = "");

    // ���������� ������ �� ������
    void sortBufferByGroup();
};



#endif // STUDINFO_H