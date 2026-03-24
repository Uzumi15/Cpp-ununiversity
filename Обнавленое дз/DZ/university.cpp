#include "University.h"

void University::addStudent(int id, QString name)
{
    students[id] = Student(id, name); // создаем и добавляем студента в map
}

void University::addTeacher(int id, QString name)
{
    teachers[id] = Teacher(id, name); // добавляем преподавателя
}

void University::addCourse(QString name, int cap)
{
    courses[name] = Course(name, cap); // создаем курс
}

Student* University::findStudent(int id) {
    return students.contains(id) ? &students[id] : nullptr; // если есть студент → возвращаем указатель, иначе nullptr
}

Teacher* University::findTeacher(int id)
{
    return teachers.contains(id) ? &teachers[id] : nullptr;
}

bool University::enrollStudent(int studentId, QString courseName)
{
    if (students.contains(studentId) && courses.contains(courseName))
    {
        // если студент и курс существуют
        if (courses[courseName].hasSpace()) // если есть место
        {
            courses[courseName].addStudent(studentId); // добавляем в курс
            students[studentId].enrollInCourse(courseName); // добавляем курс студенту
            return true; // успех
        }
    }
    return false; // если что-то не так
}

bool University::setGrade(int studentId, QString courseName, int grade)
{
    if (students.contains(studentId) &&
        students[studentId].getCourses().contains(courseName))
    {
        // если студент есть и он записан на курс
        students[studentId].addGrade(courseName, grade); // добавляем оценку
        return true; // успех
    }
    return false; // ошибка
}

QList<Student> University::getAllStudents() const
{
    return students.values(); // возвращаем всех студентов
}

QList<Course> University::getAllCourses() const
{
    return courses.values(); // возвращаем все курсы
}

QString University::getStats() const
{
    return QString("Всего студентов: %1 | Всего курсов: %2")
        .arg(students.size()) // количество студентов
        .arg(courses.size()); // количество курсов
}

void University::saveToFile(QString filename)
{
    QFile file(filename); // создаем объект файла

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) // открываем файл на запись
    {
        QTextStream out(&file); // создаем поток

        for (const auto& s : students) // перебираем студентов
        {
            out << "STUDENT;"
                << s.getId() << ";"
                << s.getName() << "\n";
            // записываем данные в формате: STUDENT;id;name
        }

        file.close(); // закрываем файл
    }
}

void University::loadFromFile(QString filename)
{
    /* тут пока не реализовано */
}
