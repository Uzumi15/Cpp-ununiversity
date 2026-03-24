#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include "Student.h"   // подключаем класс Student
#include "Teacher.h"   // подключаем класс Teacher
#include "Course.h"    // подключаем класс Course
#include <QMap>        // ассоциативный контейнер (ключ-значение)
#include <QFile>       // работа с файлами
#include <QTextStream> // поток для записи или чтения текста

class University // класс Университет (основная логика)
{
public:
    void addStudent(int id, QString name); // добавить студента
    void addTeacher(int id, QString name); // добавить преподавателя
    void addCourse(QString name, int cap); // добавить курс

    bool enrollStudent(int studentId, QString courseName); // записать студента на курс
    bool setGrade(int studentId, QString courseName, int grade); // поставить оценку

    Student* findStudent(int id);  // найти студента по ID
    Teacher* findTeacher(int id);  // найти преподавателя по ID

    QList<Student> getAllStudents() const; // получить всех студентов
    QList<Course> getAllCourses() const;   // получить все курсы

    QString getStats() const; // получить статистику (кол-во студентов и курсов)

    void saveToFile(QString filename); // сохранить данные в файл
    void loadFromFile(QString filename); // загрузить данные из файла

private:
    QMap<int, Student> students; // ID -> Студент
    QMap<int, Teacher> teachers; // ID -> Преподаватель
    QMap<QString, Course> courses; // название -> Курс
};

#endif
