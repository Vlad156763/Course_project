
#include "classcourse.h"

//=== SubjectInfo ===
//
// перевантажені оператори
bool operator<(const SubjectInfo& sub1, const SubjectInfo& sub2) {
    return sub1.Subject < sub2.Subject;
}

bool operator>(const SubjectInfo& sub1, const SubjectInfo& sub2) {
    return sub1.Subject > sub2.Subject;
}

// === StudInfo ===
//
// методи додавання і вилучення StudInfo (інформація про студента)
void StudInfo::addSubject(const QString& subjectName, const QVector<int>& grades) {
    for (const auto& subject : StudSubjects) {
        if (subject.getSubject() == subjectName) {
            qWarning("Предмет вже існує!");
            return;
        }
    }
    StudSubjects.append(SubjectInfo(subjectName, grades));
}

bool StudInfo::removeSubject(const QString& subjectName) {
    for (int i = 0; i < StudSubjects.size(); ++i) {
        if (StudSubjects[i].getSubject() == subjectName) {
            StudSubjects.removeAt(i);
            return true;
        }
    }
    qWarning("Предмет не знайдено!");
    return false;
}
// Перевантажені оператори


bool operator ==(const StudInfo& exmpl1, const StudInfo& exmpl2) {
    return (exmpl1.StudFullName == exmpl2.StudFullName &&
        exmpl1.StudSpecialty == exmpl2.StudSpecialty &&
        exmpl1.StudGroup == exmpl2.StudGroup &&
        exmpl1.StudFaculty == exmpl2.StudFaculty);
}

bool operator!=(const StudInfo& exmpl1, const StudInfo& exmpl2) {
    return !(exmpl1 == exmpl2);
}

bool operator>(const StudInfo& exmpl1, const StudInfo& exmpl2) {
    return exmpl1.StudFullName > exmpl2.StudFullName;
}

bool operator<(const StudInfo& exmpl1, const StudInfo& exmpl2) {
    return exmpl1.StudFullName < exmpl2.StudFullName;
}


// ===StudentBlock===
//
// додавання студента в масив
void StudentBlock::addStudent(const StudInfo& student) {
    students.append(student);
}
// видалення студента з масиву
bool StudentBlock::removeStudent(const QString& fullName) {
    for (int i = 0; i < students.size(); ++i) {
        if (students[i].getStudFullName() == fullName) {
            students.removeAt(i);
            return true;
        }
    }
    return false;

}
//сортування в буфері за групою
void StudentBlock::sortBufferByGroup() {

    if (specialtyBuffer.isEmpty()) {
        qWarning("Буфер порожній, сортування неможливе!");
        return;
    }
    int n = specialtyBuffer.size();

    for (int i = 1; i < n; ++i) {
        const StudInfo* key = specialtyBuffer[i];
        int j = i - 1;

        // Переміщуємо елементи, що більші за key (за групою), на одну позицію вперед
        while (j >= 0 && specialtyBuffer[j]->getStudGroup() > key->getStudGroup()) {
            specialtyBuffer[j + 1] = specialtyBuffer[j];
            j--;
        }

        specialtyBuffer[j + 1] = key;
    }
}

// фільтрація студентів за критеріями на власний вибір
  
void StudentBlock::filterByCriteria(
    const QString& specialty = "",
    const QString& faculty = "",
    const QString& group = "",
    const QString& name = "",
    const QString& subject = "") {

    specialtyBuffer.clear(); // Очищуємо буфер

    for (const auto& student : students) {
        // Перевірка критеріїв
        if ((!specialty.isEmpty() && student.getStudSpecialty() != specialty) ||
            (!faculty.isEmpty() && student.getStudFaculty() != faculty) ||
            (!group.isEmpty() && student.getStudGroup() != group) ||
            (!name.isEmpty() && student.getStudFullName() != name)) {
            continue; // Пропускаємо, якщо критерій не виконується
        }

        // Додаткова перевірка на предмет
        if (!subject.isEmpty()) {
            bool subjectFound = false;
            for (const auto& studSubject : student.getStudSubjects()) {
                if (studSubject.getSubject() == subject) {
                    subjectFound = true;
                    break; // вихід (достатньо знайти 1 збіг)
                }
            }
            if (!subjectFound) continue; // Якщо предмет не знайдено, пропускаємо
        }

        // Додаємо студента до буферу
        specialtyBuffer.append(&student);
    }
}






