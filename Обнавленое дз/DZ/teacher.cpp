#include "Teacher.h"

Teacher::Teacher(int id, QString name):id(id), name(name) {} // конструктор

int Teacher::getId() const
{
    return id; // вернуть ID
}

QString Teacher::getName() const
{
    return name; // вернуть имя
}

QString Teacher::getInfo() const
{
    return QString("ID: %1 | Преподаватель: %2")
        .arg(id)   // вставляем ID
        .arg(name); // вставляем имя
}
