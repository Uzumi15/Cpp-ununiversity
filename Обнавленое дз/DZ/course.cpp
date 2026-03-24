#include "Course.h"

Course::Course(QString name, int capacity):name(name), capacity(capacity) {} // конструктор

QString Course::getName() const
{
    return name;  // вернуть название
}

bool Course::hasSpace() const
{
    return studentIds.size() < capacity; // проверяем есть ли место
}

int Course::getCapacity() const
{
    return capacity; // максимум
}

int Course::getCurrentCount() const
{
    return studentIds.size(); // текущее количество
}

QList<int> Course::getStudentIds() const
{
    return studentIds; // вернуть список студентов
}

void Course::addStudent(int studentId)
{
    if (hasSpace() && !studentIds.contains(studentId))
    {
        // если есть место и студент не добавлен
        studentIds.append(studentId); // если есть место и студент не добавлен то добавляем
    }
}
