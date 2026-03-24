#ifndef COURSE_H
#define COURSE_H

#include <QString> // строки
#include <QList>   // список

class Course // класс Курс
{
public:
    Course(QString name = "", int capacity = 5); // конструктор

    QString getName() const; // название курса
    bool hasSpace() const;   // есть ли свободные места

    void addStudent(int studentId); // добавить студента

    int getCapacity() const; // вместимость
    int getCurrentCount() const; // сколько уже записано

    QList<int> getStudentIds() const; // список студентов

private:
    QString name; // название курса
    int capacity; // максимум студентов
    QList<int> studentIds; // список ID студентов
};

#endif
