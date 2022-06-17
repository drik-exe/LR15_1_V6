/*6. Разработайте программу, реализующую работу с бинарными файлами.Необходимо хранить информацию о группах :
•	номер группы(уникален);
•	ФИО куратора;
•	специальность;
•	средний балл по группе.
Реализовать следующие функции, вызываемые из меню :
Ввод информации  о группах с клавиатуры и сохранение ее в бинарном файле с выбранным пользователем названием.
Просмотр содержимого бинарного файла с выбранным пользователем названием.
Вывод информации о группах по введенной пользователем фамилии куратора из выбранного пользователем файла.
Вывод информации обо всех группах со средним баллом ниже 7.*/


#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

struct Group
{
    char Groups[20]{};
    char Name[20]{};
    char Surname[20]{};
    char Otch[20]{};
    char Spec[20]{};
    double Medmark;


};

double MaxMark(Group group[], int size) {
    double max = group[0].Medmark;
    for (size_t i = 1; i < size; i++)
    {
        if (max < group[i].Medmark) {
            max = group[i].Medmark;
        }
    }
    return max;
}

void Menu() {

    cout << "/////////////////////////////////////////////////" << endl << endl;
    cout << "\t\tМЕНЮ" << endl;
    cout << "\n 1 - Ввод информации о группе: ";
    cout << "\n 2 - Просмотр содержания файла: ";
    cout << "\n 3 - Вывести информация о группе по введёной фамилии куратора: ";
    cout << "\n 4 - Вывод информации обо всех группах со средним баллом ниже 7: ";
    cout << "\n 5 - Удаление информации из выбранного бинарного файла о группе с выбранным номером: ";
    cout << "\n 6 - Изменение информации о ФИО куратора для всех групп из выбранного файла, имеющих средний балл меньше, чем вводит пользователь: ";
    cout << "\n 7 - Вывод названий специальностей с максимальным средним баллом из выбранного файла: ";
    cout << "\n 8 - Изменение информации о ФИО куратора по введенному номеру группы. Файл вводит пользователь: ";
    cout << endl << "/////////////////////////////////////////////////" << endl << endl;

}


int main()
{
    setlocale(0, "");
    string namef;
    int count_group = 0;
    int back;
    int choice;
    fstream file;
    Group group[20];

    cout << "Создаём новый файл(1) или выбираем существующий(2): ";
    cin >> choice;
    if (choice == 1) {
        cout << "Enter name for file: ";
        cin >> namef;
        file.open(namef, ios::binary | ios::out);
    }
    else {
        cout << "Enter file name: ";
        cin >> namef;
        file.open(namef, ios::binary | ios::in);
        file.seekg(0, ios::end);
        int size = file.tellg();
        int k = sizeof(Group);
        count_group = (size / k);
        ++count_group;
    }

    if (!file.is_open())
    {
        cout << "Files can not be open\n";
        return 0;
    }
    else {
        file.close();
        while (true) {
            int n;
            Menu();
            cin >> n;
            switch (n)
            {
            case 1:
            {
                file.open(namef, ios::binary | ios::app);

                cout << "/////////////////////////////////////////////////" << endl << endl;
                cout << "\t\tВвод информации о группе" << endl << endl;

                cout << "Введите номер группы: ";
                cin >> group[count_group].Groups;
                file.write((char*)&group[count_group].Groups, sizeof(group[count_group].Groups));

                cout << "Введите ФИО куратора: ";
                cin >> group[count_group].Surname;
                file.write((char*)&group[count_group].Surname, sizeof(group[count_group].Surname));
                cin >> group[count_group].Name;
                file.write((char*)&group[count_group].Name, sizeof(group[count_group].Name));
                cin >> group[count_group].Otch;
                file.write((char*)&group[count_group].Otch, sizeof(group[count_group].Otch));

                cout << "Введите специальность: ";
                cin >> group[count_group].Spec;
                file.write((char*)&group[count_group].Spec, sizeof(group[count_group].Spec));

                cout << "Введите средний балл группы: ";
                cin >> group[count_group].Medmark;
                file.write((char*)&group[count_group].Medmark, sizeof(group[count_group].Medmark));

                count_group++;
                file.close();

                cout << "/////////////////////////////////////////////////" << endl << endl;
                cout << "Введите 0, чтобы вернуться к меню, или 1, чтобы закончить: ";
                cin >> back;
                if (back == 0) {
                    continue;
                }
                else {
                    return 0;
                }
            }
            case 2:
            {
                file.open(namef, ios::binary | ios::in);

                cout << "/////////////////////////////////////////////////" << endl << endl;
                cout << "\t\tПросмотр содержания файла" << endl << endl;

                for (size_t i = 0; i < count_group; i++)
                {
                    file.read((char*)&group[i].Groups, sizeof(group[i].Groups));
                    file.read((char*)&group[i].Surname, sizeof(group[i].Surname));
                    file.read((char*)&group[i].Name, sizeof(group[i].Name));
                    file.read((char*)&group[i].Otch, sizeof(group[i].Otch));
                    file.read((char*)&group[i].Spec, sizeof(group[i].Spec));
                    file.read((char*)&group[i].Medmark, sizeof(group[i].Medmark));
                    cout << "Группа: " << group[i].Groups << " ФИО куратора: " << group[i].Surname << ' ' << group[i].Name << ' ' << group[i].Otch << " Cпециальность: " << group[i].Spec << " Срдний балл по группе: " << group[i].Medmark << endl;

                }
                file.close();
                cout << "/////////////////////////////////////////////////" << endl << endl;
                cout << "Введите 0, чтобы вернуться к меню, или 1, чтобы закончить: ";
                cin >> back;
                if (back == 0) {
                    continue;
                }
                else {
                    return 0;
                }
            }
            case 3:
            {
                cout << "/////////////////////////////////////////////////" << endl << endl;
                cout << "\t\tинформация о группе по введёной фамилии куратора" << endl << endl;
                file.open(namef, ios::binary | ios::in);
                char surname[20];
                bool flag = true;
                cout << "Введите фамилию куратора: ";
                cin >> surname;
                for (size_t i = 0; i < count_group; i++)
                {
                    file.read((char*)&group[i].Groups, sizeof(group[i].Groups));
                    file.read((char*)&group[i].Surname, sizeof(group[i].Surname));
                    file.read((char*)&group[i].Name, sizeof(group[i].Name));
                    file.read((char*)&group[i].Otch, sizeof(group[i].Otch));
                    file.read((char*)&group[i].Spec, sizeof(group[i].Spec));
                    file.read((char*)&group[i].Medmark, sizeof(group[i].Medmark));
                    if (strcmp(group[i].Surname, surname) == 0) {
                        cout << "Группа: " << group[i].Groups << " ФИО куратора: " << group[i].Surname[i] << ' ' << group[i].Name << ' ' << group[i].Otch << " Cпециальность: " << group[i].Spec << " Срдний балл по группе: " << group[i].Medmark << endl;
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    cout << "По введённой фамилии никого не найдено" << endl;
                }
                file.close();
                cout << "/////////////////////////////////////////////////" << endl << endl;
                cout << "Введите 0, чтобы вернуться к меню, или 1, чтобы закончить: ";
                cin >> back;
                if (back == 0) {
                    continue;
                }
                else {
                    return 0;
                }
            }
            case 4:
            {
                cout << "/////////////////////////////////////////////////" << endl << endl;
                cout << "Вывод информации обо всех группах со средним баллом ниже 7: " << endl;

                file.open(namef, ios::binary | ios::in);
                bool flag1 = true;
                for (size_t i = 0; i < count_group; i++)
                {
                    file.read((char*)&group[i].Groups, sizeof(group[i].Groups));
                    file.read((char*)&group[i].Surname, sizeof(group[i].Surname));
                    file.read((char*)&group[i].Name, sizeof(group[i].Name));
                    file.read((char*)&group[i].Otch, sizeof(group[i].Otch));
                    file.read((char*)&group[i].Spec, sizeof(group[i].Spec));
                    file.read((char*)&group[i].Medmark, sizeof(group[i].Medmark));
                    if (group[i].Medmark < 7.0) {
                        cout << "Группа: " << group[i].Groups << " ФИО куратора: " << group[i].Surname << ' ' << group[i].Name << ' ' << group[i].Otch << " Cпециальность: " << group[i].Spec << " Срдний балл по группе: " << group[i].Medmark << endl;
                        flag1 = false;
                    }
                }
                if (flag1) {
                    cout << "Нет групп с баллом ниже 7" << endl;
                }
                file.close();

                cout << "/////////////////////////////////////////////////" << endl << endl;
                cout << "Введите 0, чтобы вернуться к меню, или 1, чтобы закончить: ";
                cin >> back;
                if (back == 0) {
                    continue;
                }
                else {
                    return 0;
                }
            }
            case 5:
            {
                cout << "/////////////////////////////////////////////////" << endl << endl;
                cout << "Удаление информации из выбранного бинарного файла о группе с выбранным номером: " << endl;


                file.open(namef, ios::binary | ios::in);

                for (size_t i = 0; i < count_group; i++)
                {
                    file.read((char*)&group[i].Groups, sizeof(group[i].Groups));
                    file.read((char*)&group[i].Surname, sizeof(group[i].Surname));
                    file.read((char*)&group[i].Name, sizeof(group[i].Name));
                    file.read((char*)&group[i].Otch, sizeof(group[i].Otch));
                    file.read((char*)&group[i].Spec, sizeof(group[i].Spec));
                    file.read((char*)&group[i].Medmark, sizeof(group[i].Medmark));
                }
                file.close();

                file.open(namef, ios::binary | ios::out | ios::trunc);

                char numgr[20];
                cout << "Введите номер группы: ";
                cin >> numgr;
                bool flag = false;

                for (size_t i = 0; i < count_group; i++)
                {
                    if (strcmp(group[i].Groups, numgr) != 0) {
                        file.write((char*)&group[i].Groups, sizeof(group[i].Groups));
                        file.write((char*)&group[i].Surname, sizeof(group[i].Surname));
                        file.write((char*)&group[i].Name, sizeof(group[i].Name));
                        file.write((char*)&group[i].Otch, sizeof(group[i].Otch));
                        file.write((char*)&group[i].Spec, sizeof(group[i].Spec));
                        file.write((char*)&group[i].Medmark, sizeof(group[i].Medmark));
                    }
                    else {
                        continue;
                        flag == true;
                    }

                }
                if(flag){ --count_group; }

                file.close();



                cout << endl << "/////////////////////////////////////////////////" << endl << endl;
                cout << "Введите 0, чтобы вернуться к меню, или 1, чтобы закончить: ";
                cin >> back;
                if (back == 0) {
                    continue;
                }
                else {
                    return 0;
                }

            }
            case 6:
            {
                cout << "/////////////////////////////////////////////////" << endl << endl;
                cout << "Изменение информации о ФИО куратора для всех групп из выбранного файла, имеющих средний балл меньше, чем вводит пользователь: " << endl;
                double mark;
                cout << "Введите средний балл: ";
                cin >> mark;

                file.open(namef, ios::binary | ios::in);

                for (size_t i = 0; i < count_group; i++)
                {
                    file.read((char*)&group[i].Groups, sizeof(group[i].Groups));
                    file.read((char*)&group[i].Surname, sizeof(group[i].Surname));
                    file.read((char*)&group[i].Name, sizeof(group[i].Name));
                    file.read((char*)&group[i].Otch, sizeof(group[i].Otch));
                    file.read((char*)&group[i].Spec, sizeof(group[i].Spec));
                    file.read((char*)&group[i].Medmark, sizeof(group[i].Medmark));
                }
                file.close();

                file.open(namef, ios::binary | ios::out | ios::trunc);

                for (size_t i = 0; i < count_group; i++)
                {
                    if (group[i].Medmark < mark) {

                        cout << "Введите новое ФИО куратора: ";
                        cin >> group[i].Surname;
                        cin >> group[i].Name;
                        cin >> group[i].Otch;

                    }
                }


                for (size_t i = 0; i < count_group; i++)
                {
                    file.write((char*)&group[i].Groups, sizeof(group[i].Groups));
                    file.write((char*)&group[i].Surname, sizeof(group[i].Surname));
                    file.write((char*)&group[i].Name, sizeof(group[i].Name));
                    file.write((char*)&group[i].Otch, sizeof(group[i].Otch));
                    file.write((char*)&group[i].Spec, sizeof(group[i].Spec));
                    file.write((char*)&group[i].Medmark, sizeof(group[i].Medmark));

                }


                file.close();

                cout << endl << "/////////////////////////////////////////////////" << endl << endl;
                cout << "Введите 0, чтобы вернуться к меню, или 1, чтобы закончить: ";
                cin >> back;
                if (back == 0) {
                    continue;
                }
                else {
                    return 0;
                }

            }
            case 7:
            {
                cout << "/////////////////////////////////////////////////" << endl << endl;
                cout << "Вывод названий специальностей с максимальным средним баллом из выбранного файла: " << endl;

                file.open(namef, ios::binary | ios::in);

                for (size_t i = 0; i < count_group; i++)
                {
                    file.read((char*)&group[i].Groups, sizeof(group[i].Groups));
                    file.read((char*)&group[i].Surname, sizeof(group[i].Surname));
                    file.read((char*)&group[i].Name, sizeof(group[i].Name));
                    file.read((char*)&group[i].Otch, sizeof(group[i].Otch));
                    file.read((char*)&group[i].Spec, sizeof(group[i].Spec));
                    file.read((char*)&group[i].Medmark, sizeof(group[i].Medmark));
                }
                file.close();

                for (size_t i = 0; i < count_group; i++)
                {
                    if (MaxMark(group, count_group) == group[i].Medmark) {
                        cout << "Название специальности: " << group[i].Spec << '\t';
                    }
                }

                cout << endl << "/////////////////////////////////////////////////" << endl << endl;
                cout << "Введите 0, чтобы вернуться к меню, или 1, чтобы закончить: ";
                cin >> back;
                if (back == 0) {
                    continue;
                }
                else {
                    return 0;
                }
            }
            case 8:
            {
                cout << "/////////////////////////////////////////////////" << endl << endl;
                cout << "Изменение информации о ФИО куратора по введенному номеру группы. Файл вводит пользователь: " << endl;

                char numgr[20];
                cout << "Введите номер группы: ";
                cin >> numgr;

                file.open(namef, ios::binary | ios::in);

                for (size_t i = 0; i < count_group; i++)
                {
                    file.read((char*)&group[i].Groups, sizeof(group[i].Groups));
                    file.read((char*)&group[i].Surname, sizeof(group[i].Surname));
                    file.read((char*)&group[i].Name, sizeof(group[i].Name));
                    file.read((char*)&group[i].Otch, sizeof(group[i].Otch));
                    file.read((char*)&group[i].Spec, sizeof(group[i].Spec));
                    file.read((char*)&group[i].Medmark, sizeof(group[i].Medmark));
                }

                file.close();

                file.open(namef, ios::binary | ios::out | ios::trunc);

                for (size_t i = 0; i < count_group; i++)
                {
                    if (strcmp(group[i].Groups, numgr) == 0) {
                        cout << "Введите новое ФИО куратора: ";
                        cin >> group[i].Surname;
                        cin >> group[i].Name;
                        cin >> group[i].Otch;
                    }
                }

                for (size_t i = 0; i < count_group; i++)
                {
                    file.write((char*)&group[i].Groups, sizeof(group[i].Groups));
                    file.write((char*)&group[i].Surname, sizeof(group[i].Surname));
                    file.write((char*)&group[i].Name, sizeof(group[i].Name));
                    file.write((char*)&group[i].Otch, sizeof(group[i].Otch));
                    file.write((char*)&group[i].Spec, sizeof(group[i].Spec));
                    file.write((char*)&group[i].Medmark, sizeof(group[i].Medmark));

                }

                file.close();

                cout << endl << "/////////////////////////////////////////////////" << endl << endl;
                cout << "Введите 0, чтобы вернуться к меню, или 1, чтобы закончить: ";
                cin >> back;
                if (back == 0) {
                    continue;
                }
                else {
                    return 0;
                }
            }
            }



        }
    }

}
