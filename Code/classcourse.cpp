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
void StudInfo::addSubject(const QString& subjectName, const QVector<QString>& grades) {
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
// Методи додавання 
bool StudentBlock::addSpecialty(const QString& specialty) {
    if (!Specialties.contains(specialty)) {
        Specialties.append(specialty);
        return true;
    }
    return false;
}

bool StudentBlock::addFaculty(const QString& specialty, const QString& faculty) {
    if (Specialties.contains(specialty)) {
        Faculties.append(Faculty(specialty, faculty));
        return true;
    }
    return false;
}
bool StudentBlock::addGroup(const QString& specialty, const QString& faculty, const QString& group) {
    for (const auto& fac : Faculties) {
        if (specialty == fac.getSpecialty() && faculty == fac.getFacultyName()) {
            Groups.append(Group(specialty, faculty, group));
            return true;
        }
    }
    return false;
}

bool StudentBlock::addName(const QString& specialty, const QString& faculty, const QString& group, const QString& fullName) {
    for (const auto& grp : Groups) {
        if (specialty == grp.getSpecialty() && faculty == grp.getFacultyName() && group == grp.getGroupName()) {
            Names.append(FullName(specialty, faculty, group, fullName));
            return true;
        }
    }
    return false;
}

bool StudentBlock::addSubject(const QString& specialty, const QString& faculty, const QString& group,
    const QString& fullName, const QString& subjectName, const QVector<QString>& grades) {
    for (auto& student : Students) {
        if (student.getStudSpecialty() == specialty && student.getStudFaculty() == faculty &&
            student.getStudGroup() == group && student.getStudFullName() == fullName) {
            student.addSubject(subjectName, grades);
            return true;
        }
    }
    return false;
}
void StudentBlock::addStudent(const StudInfo& student) {
    Students.append(student);
}


/*TODO: РОЗРОБИТИ СОРТУВАННЯ ДЛЯ БУФЕРІВ ( ПОМІСТИТИ В КІНЕЦЬ МЕТОДІВ ФІЛЬТРАЦІЙ )


    РОЗРОБЛЮВАТИ МОЖНА ОСЬ ТУТ :) :(

*/


// фільтрація студентів за критеріями на власний вибір

void StudentBlock::filterByCriteria(
    const QString& specialty,
    const QString& faculty,
    const QString& group,
    const QString& name,
    const QString& subject) {

    SpecialtyBuffer.clear(); // Очищуємо буфер

    for (const auto& student : Students) {
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
        StudentsBuffer.append(&student);
    }
    // Викликати сортування ось тут :) (на місці коментаря)
}
void StudentBlock::filterBySpec(const QString& specialty) {
    SpecialtyBuffer.clear();
    for (const auto& entry : Specialties) {
        if (!specialty.isEmpty() && entry != specialty) {
            continue;
        }
        SpecialtyBuffer.append(&entry);
    }
}

void StudentBlock::filterByFac(const QString& specialty, const QString& faculty) {
    FacultyBuffer.clear();
    for (const auto& entry : Faculties) {
        if ((!specialty.isEmpty() && entry.getSpecialty() != specialty) ||
            (!faculty.isEmpty() && entry.getFacultyName() != faculty)) {
            continue;
        }
        FacultyBuffer.append(&entry);
    }
    // Викликати сортування ось тут :) (на місці коментаря)
}

void StudentBlock::filterByGroup(const QString& specialty, const QString& faculty, const QString& group) {
    GroupBuffer.clear();
    for (const auto& entry : Groups) {
        if ((!specialty.isEmpty() && entry.getSpecialty() != specialty) ||
            (!faculty.isEmpty() && entry.getFacultyName() != faculty) ||
            (!group.isEmpty() && entry.getGroupName() != group)) {
            continue;
        }
        GroupBuffer.append(&entry);
    }
    // Викликати сортування ось тут :) (на місці коментаря)
}

void StudentBlock::filterByName(const QString& specialty, const QString& faculty, const QString& group, const QString& name) {
    NameBuffer.clear();
    for (const auto& entry : Names) {
        if ((!specialty.isEmpty() && entry.getFullName() != specialty) ||
            (!faculty.isEmpty() && entry.getFullName() != faculty) ||
            (!group.isEmpty() && entry.getFullName() != group) ||
            (!name.isEmpty() && entry.getFullName() != name)) {
            continue;
        }
        NameBuffer.append(&entry);
    }

    // Викликати сортування ось тут :) (на місці коментаря)
}

/*
bool StudentBlock::addSpecialty(const QString& specialty){
    for(const auto & spec : specialties){
        if(spec.getStudSpecialty() == specialty){
            qWarning("Спеціальність вже існує!");
            return;
        }
    }
    specialties.append(StudInfo("",specialty,"","",{})) // додавання лише спеціальності
}
bool StudentBlock::addFaculty(const QString& specialty, QString& faculty){
    for(const auto & fac : faculties){
        for (const auto& fac : faculties) {
        if (fac.getStudSpecialty() == specialty && fac.getStudFaculty() == faculty) {
            qWarning("Спеціальність та факультет вже існують!");
            return;
        }
    }
    faculties.append(StudInfo("", specialty, "", faculty, {})); // Додаємо спеціальність і факультет
    }

}
bool StudentBlock::addGroup(const QString& specialty, QString& faculty,const QString& group){
       for (const auto& grp : groups) {
        if (grp.getStudSpecialty() == specialty && grp.getStudFaculty() == faculty &&
            grp.getStudGroup() == group) {
            qWarning("Спеціальність, факультет і група вже існують!");
            return;
        }
    }
    groups.append(StudInfo("", specialty, group, faculty, {})); // Додаємо спеціальність, факультет та групу
}
bool StudentBlock::addName(const QString& specialty, const QString& faculty, const QString& group, const QString& fullName){
    for (const auto& name : names) {
        if (name.getStudSpecialty() == specialty && name.getStudFaculty() == faculty &&
            name.getStudGroup() == group && name.getStudFullName() == fullName) {
            qWarning("Такий студент вже існує!");
            return;
        }
    }
    names.append(StudInfo(fullName, specialty, group, faculty, {})); // Додаємо студента
}
bool StudentBlock::addStudent(const QString& specialty, const QString& faculty, const QString& group,
                              const QString& fullName, const QString& subject, const QVector<QString>& grades){
    for (auto& student : stsubjects) {
        if (student.getStudSpecialty() == specialty && student.getStudFaculty() == faculty &&
            student.getStudGroup() == group && student.getStudFullName() == fullName) {
            student.addSubject(subject, grades); // Додаємо предмет студенту
            return;
        }
    }
    // Додаємо нового студента з предметом
    StudInfo newStudent(fullName, specialty, group, faculty, { SubjectInfo(subject, grades) });
    stsubjects.append(newStudent);
}
*/
bool StudentBlock::removeSpecialty(const QString& specialty) {
    bool deleted = false;
    for (int i = 0; i < Specialties.size(); ++i) {
        if (Specialties[i] == specialty) {
            // Видаляємо всі об'єкти в інших масивах, що мають цю спеціальність
            for (int j = 0; j < Faculties.size(); ++j) {
                if (Faculties[j].getSpecialty() == specialty) {
                    Faculties.removeAt(j);
                    --j; // Компенсуємо зсув
                }
            }
            for (int j = 0; j < Groups.size(); ++j) {
                if (Groups[j].getSpecialty() == specialty) {
                    Groups.removeAt(j);
                    --j; // Компенсуємо зсув
                }
            }
            for (int j = 0; j < Names.size(); ++j) {
                if (Names[j].getSpecialty() == specialty) {
                    Names.removeAt(j);
                    --j; // Компенсуємо зсув
                }
            }
            Specialties.removeAt(i);
            deleted = true;
            --i; // Компенсуємо зсув
        }
    }
    return deleted;
}

bool StudentBlock::removeFaculty(const QString& specialty, const QString& faculty) {
    bool deleted = false;
    for (int i = 0; i < Faculties.size(); ++i) {
        if (Faculties[i].getFacultyName() == faculty) {
            // Видаляємо всі об'єкти в інших масивах, що мають цей факультет
            for (int j = 0; j < Groups.size(); ++j) {
                if (Groups[j].getFacultyName() == faculty) {
                    Groups.removeAt(j);
                    --j;
                }
            }
            for (int j = 0; j < Names.size(); ++j) {
                if (Names[j].getFacultyName() == faculty) {
                    Names.removeAt(j);
                    --j;
                }
            }
            Faculties.removeAt(i);
            deleted = true;
            --i;
        }
    }
    return deleted;
}

bool StudentBlock::removeGroup(const QString& specialty, const QString& faculty, const QString& group) {

    bool deleted = false;
    for (int i = 0; i < Groups.size(); ++i) {
        if (Groups[i].getGroupName() == group) {
            // Видаляємо всі об'єкти в інших масивах, що мають цю групу
            for (int j = 0; j < Names.size(); ++j) {
                if (Names[j].getGroupName() == group) {
                    Names.removeAt(j);
                    --j;
                }
            }
            Groups.remove(i);
            deleted = true;
            --i;
        }
    }
    return deleted;
}

bool StudentBlock::removeName(const QString& specialty, const QString& faculty, const QString& group, const QString& fullName) {
    bool deleted = false;
    for (int i = 0; i < Names.size(); ++i) {
        if (Names[i].getFullName() == fullName) {
            Names.removeAt(i);
            deleted = true;
            --i;
        }
    }
    return deleted;

}

bool StudentBlock::removeSubject(const QString& specialty, const QString& faculty, const QString& group,
    const QString& fullName, const QString& subject) {
    bool deleted = false;
    for (auto& student : Students) {
        if (student.getStudSpecialty() == specialty && student.getStudFaculty() == faculty &&
            student.getStudGroup() == group && student.getStudFullName() == fullName) {
            deleted = student.removeSubject(subject);
        }
    }
    return deleted;
}
bool StudentBlock::removeStudent(const QString& fullName) {
    for (int i = 0; i < Students.size(); ++i) {
        if (Students[i].getStudFullName() == fullName) {
            Students.removeAt(i);
            return true;
        }
    }
    return false;

}



QVector<const StudInfo*>& StudentBlock::getbuffer() {
    return this->StudentsBuffer;
}

// пошук елемента за піб студентів
StudInfo* StudentBlock::findInBuffer(const QString& fullName) {
    for (const auto& student : StudentsBuffer) {
        if (student->getStudFullName() == fullName) {
            return const_cast<StudInfo*>(student); // Повертаємо вказівник на знайденого студента
        }
    }
    qWarning("Студента не знайдено в буфері!");
    return nullptr;
}




// void StudentBlock::sortBuffer(const QString& sortBy) {
//     if (specialtyBuffer.isEmpty()) {
//         qWarning("Буфер порожній, сортування неможливе!");
//         return;
//     }

//     int n = SpecialtyBuffer.size();

//     for (int i = 1; i < n; ++i) {
//         const StudInfo* key = SpecialtyBuffer[i];
//         int j = i - 1;

//         // Порівняння залежно від параметра сортування
//         while (j >= 0) {
//             bool condition = false;
//             if (sortBy == "group") {
//                 condition = SpecialtyBuffer[j]->getStudGroup() > key->getStudGroup();
//             } else if (sortBy == "name") {
//                 condition = SpecialtyBuffer[j]->getStudFullName() > key->getStudFullName();
//             } else if (sortBy == "faculty") {
//                 condition = SpecialtyBuffer[j]->getStudFaculty() > key->getStudFaculty();
//             } else {
//                 qWarning("Невідомий параметр сортування!");
//                 return;
//             }

//             if (condition) {
//                 SpecialtyBuffer[j + 1] = SpecialtyBuffer[j];
//                 j--;
//             } else {
//                 break;
//             }
//         }
//         SpecialtyBuffer[j + 1] = key;
//     }
// }

