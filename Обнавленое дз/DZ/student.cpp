#include "Student.h"

Student::Student(int id, QString name):id(id), name(name) {} // конструктор: сразу задаем id и имя

int Student::getId() const { return id; } // возвращаем ID

QString Student::getName() const { return name; } // возвращаем имя

void Student::enrollInCourse(const QString& courseName)
{
    if (!enrolledCourses.contains(courseName)) // если курс еще не добавлен
    {
        enrolledCourses.append(courseName); // добавляем курс
    }
}

void Student::addGrade(const QString& courseName, int grade)
{
    grades[courseName].append(grade); // добавляем оценку в список по курсу
}

double Student::getAverageGrade() const
{
    int total = 0, count = 0; // сумма и количество оценок

    for (const auto& list : grades.values()) // проходим по всем курсам
    {
        for (int g : list) // проходим по оценкам
        {
            total += g; // суммируем
            count++; // считаем количество
        }
    }

    return count == 0 ? 0.0 : static_cast<double>(total) / count; // если оценок нет → 0, иначе считаем среднее
}

QList<QString> Student::getCourses() const
{
    return enrolledCourses; // возвращаем список курсов
}

QString Student::getInfo() const
{
    return QString("ID: %1 | Студент: %2 | Средний балл: %3")
        .arg(id) // подставляем ID
        .arg(name) // подставляем имя
        .arg(QString::number(getAverageGrade(), 'f', 2));  // подставляем средний балл (2 знака после запятой)
}
