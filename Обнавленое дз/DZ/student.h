#ifndef STUDENT_H
#define STUDENT_H

#include <QString>// класс строки Qt
#include <QList>// список (массив) Qt
#include <QMap>// ассоциативный массив (ключ-значение)

class Student // объявляем класс Студент
{
public:
    Student(int id = 0, QString name = ""); // конструктор (по умолчанию id=0, имя пустое)

    int getId() const;   // получить ID студента
    QString getName() const; // получить имя студента

    void enrollInCourse(const QString& courseName); // записать на курс
    void addGrade(const QString& courseName, int grade); // добавить оценку

    double getAverageGrade() const; // получить средний балл
    QList<QString> getCourses() const; // получить список курсов

    QString getInfo() const; // получить информацию о студенте (строка)

private:
    int id;// ID студента
    QString name;// имя студента

    QList<QString> enrolledCourses; // список курсов
    QMap<QString, QList<int>> grades; // оценки: курс -> список оценок
};

#endif
