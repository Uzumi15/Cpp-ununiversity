#ifndef TEACHER_H
#define TEACHER_H

#include <QString>// строки Qt

class Teacher // класс Преподаватель
{
public:
    Teacher(int id = 0, QString name = ""); // конструктор

    int getId() const; // получить ID
    QString getName() const; // получить имя
    QString getInfo() const; // получить инфу

private:
    int id;// ID преподавателя
    QString name; // имя
};

#endif
