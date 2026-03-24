#include <QApplication>   // основа любого Qt приложения (запуск цикла)
#include <QWidget>       // базовый класс для всех окон
#include <QVBoxLayout>   // вертикальный layout
#include <QGridLayout>   // сетка (таблица размещения)
#include <QPushButton>   // кнопки
#include <QTableWidget>  // таблица
#include <QHeaderView>   // управление заголовками таблицы
#include <QInputDialog>  // всплывающие окна ввода
#include <QMessageBox>   // всплывающие сообщения
#include <QLabel>        // текстовая надпись
#include "university.h"

class UniversityUI : public QWidget // создаем класс окна
{
    University uni; // объект логики
    QTableWidget *table; // таблица
    QLabel *statsLabel; // нижняя строка

public:
    UniversityUI()
    {
        setWindowTitle("Система управления университетом"); // заголовок окна
        resize(900, 600); // размер окна

        auto *mainLayout = new QVBoxLayout(this); // главный layout

        table = new QTableWidget(0, 3); // таблица 3 столбца
        table->setHorizontalHeaderLabels({"ID / Название", "Имя / Вместимость", "Доп. Информация"});
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // растягиваем
        mainLayout->addWidget(table); // добавляем в окно

        auto *btnLayout = new QGridLayout(); // сетка кнопок

        auto *btnAddStudent = new QPushButton("1. Добавить студента"); // кнопка
        auto *btnAddTeacher = new QPushButton("2. Добавить преподавателя");
        auto *btnCreateCourse = new QPushButton("3. Создать курс");
        auto *btnEnroll = new QPushButton("4. Записать на курс");
        auto *btnGrade = new QPushButton("5. Выставить оценку");
        auto *btnShowStud = new QPushButton("6. Список студентов");
        auto *btnShowCourses = new QPushButton("7. Список курсов");
        auto *btnSave = new QPushButton("9. Сохранить в файл");

        btnLayout->addWidget(btnAddStudent, 0, 0); // строка 0 колонка 0
        btnLayout->addWidget(btnAddTeacher, 0, 1);
        btnLayout->addWidget(btnCreateCourse, 1, 0);
        btnLayout->addWidget(btnEnroll, 1, 1);
        btnLayout->addWidget(btnGrade, 2, 0);
        btnLayout->addWidget(btnShowStud, 2, 1);
        btnLayout->addWidget(btnShowCourses, 3, 0);
        btnLayout->addWidget(btnSave, 3, 1);

        mainLayout->addLayout(btnLayout); // добавляем сетку

        statsLabel = new QLabel("Студентов: 0 | Курсов: 0"); // текст внизу
        mainLayout->addWidget(statsLabel);

        // КНОПКИ

        connect(btnAddStudent, &QPushButton::clicked, [this]()
        {
            bool ok;
            int id = QInputDialog::getInt(this, "Студент", "Введите ID:", 100, 1, 9999, 1, &ok);
            if (!ok) return; // если отмена

            QString name = QInputDialog::getText(this, "Студент", "Введите Имя:", QLineEdit::Normal, "", &ok);
            if (ok && !name.isEmpty())
            {
                uni.addStudent(id, name); // добавляем студента
                updateStats(); // обновляем статистику
            }
        });

        connect(btnAddTeacher, &QPushButton::clicked, [this]()
        {
            bool ok;
            int id = QInputDialog::getInt(this, "Преподаватель", "Введите ID:", 500, 1, 9999, 1, &ok);
            if (!ok) return;

            QString name = QInputDialog::getText(this, "Преподаватель", "Введите Имя:", QLineEdit::Normal, "", &ok);
            if (ok && !name.isEmpty()) {
                uni.addTeacher(id, name); // добавляем преподавателя
                QMessageBox::information(this, "Успех", "Преподаватель добавлен"); // сообщение
                updateStats();
            }
        });

        connect(btnCreateCourse, &QPushButton::clicked, [this]()
        {
            bool ok;
            QString name = QInputDialog::getText(this, "Курс", "Название курса:", QLineEdit::Normal, "", &ok);
            if (!ok || name.isEmpty()) return;

            int cap = QInputDialog::getInt(this, "Курс", "Вместимость:", 20, 1, 100, 1, &ok);
            if (ok) {
                uni.addCourse(name, cap); // создаем курс
                updateStats();
            }
        });

        connect(btnEnroll, &QPushButton::clicked, [this]()
        {
            bool ok;
            int id = QInputDialog::getInt(this, "Запись", "ID студента:", 0, 0, 9999, 1, &ok);
            if (!ok) return;

            QString course = QInputDialog::getText(this, "Запись", "Название курса:", QLineEdit::Normal, "", &ok);
            if (ok && !course.isEmpty())
            {
                if(uni.enrollStudent(id, course))
                {
                    QMessageBox::information(this, "Успех", "Студент записан");
                } else
                {
                    QMessageBox::warning(this, "Ошибка", "Не удалось записать");
                }
            }
        });

        connect(btnGrade, &QPushButton::clicked, [this]()
        {
            bool ok;
            int id = QInputDialog::getInt(this, "Оценка", "ID:", 0, 0, 9999, 1, &ok);
            if (!ok) return;

            QString course = QInputDialog::getText(this, "Оценка", "Курс:", QLineEdit::Normal, "", &ok);
            if (!ok) return;

            int grade = QInputDialog::getInt(this, "Оценка", "Балл:", 0, 0, 100, 1, &ok);
            if (ok) {
                uni.setGrade(id, course, grade); // ставим оценку
            }
        });

        connect(btnShowStud, &QPushButton::clicked, [this]()
        {
            auto list = uni.getAllStudents(); // получаем студентов
            table->setRowCount(0); // очищаем

            for(const auto& s : list)
            {
                int row = table->rowCount(); // текущая строка
                table->insertRow(row); // добавляем строку

                table->setItem(row, 0, new QTableWidgetItem(QString::number(s.getId())));
                table->setItem(row, 1, new QTableWidgetItem(s.getName()));
                table->setItem(row, 2, new QTableWidgetItem(s.getInfo()));
            }
        });

        connect(btnShowCourses, &QPushButton::clicked, [this]()
        {
            auto list = uni.getAllCourses(); // получаем курсы
            table->setRowCount(0);

            for(const auto& c : list)
            {
                int row = table->rowCount();
                table->insertRow(row);

                table->setItem(row, 0, new QTableWidgetItem(c.getName()));
                table->setItem(row, 1, new QTableWidgetItem(QString::number(c.getCapacity())));
                table->setItem(row, 2, new QTableWidgetItem("Занято: " + QString::number(c.getCurrentCount())));
            }
        });

        connect(btnSave, &QPushButton::clicked, [this]()
        {
            uni.saveToFile("university_data.txt"); // сохраняем
            QMessageBox::information(this, "Файл", "Сохранено");
        });
    }

    void updateStats()
    {
        statsLabel->setText(uni.getStats()); // обновляем текст
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // создаем приложение
    UniversityUI w; // создаем окно
    w.show(); // показываем окно
    return a.exec(); // запускаем цикл приложения
}
