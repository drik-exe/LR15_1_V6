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

using namespace std;

struct Group
{
    string Groups[20];
    string Name[20];
    string Surname[20];
    string Otch[20];
    string Spec[20];
    double Medmark[20];

    double Average(int arr[], double size) {
        double sum = 0;
        for (size_t i = 0; i < size; i++)
        {
            sum += arr[i];
        }
        return (sum / size);
    }



    void Menu() {

        cout << "/////////////////////////////////////////////////" << endl << endl;
        cout << "\t\tМЕНЮ" << endl;
        cout << "\n 1 - Ввод информации о группе: ";
        cout << "\n 2 - Просмотр содержания файла: ";
        cout << "\n 3 - Вывести информация о группе по введёной фамилии куратора: ";
        cout << "\n 4 - Вывод информации обо всех группах со средним баллом ниже 7: ";
        cout << endl << "/////////////////////////////////////////////////" << endl << endl;

    }
};

int main()
{
    setlocale(0, "");
    string namef;
    int count_group = 0;
    int back;
    cout << "Enter name for file: ";
    cin >> namef;
    fstream file(namef, ios::binary | ios::out);


    Group group;
    if (!file.is_open())
    {
        cout << "Files can not be open\n";
        return 0;
    }
    else{
        file.close();
        while (true) {
            int n;
            group.Menu();
            cin >> n;
            switch (n) 
            {
            case 1:
            {
                file.open(namef, ios::binary | ios::app);

                cout << "/////////////////////////////////////////////////" << endl << endl;
                cout << "\t\tВвод информации о группе" << endl << endl;

                cout << "Введите номер группы: ";
                cin >> group.Groups[count_group];
                file.write((char*)&group.Groups[count_group], sizeof(group.Groups[count_group]));

                cout << "Введите ФИО куратора: ";
                cin >> group.Surname[count_group];
                file.write((char*)&group.Surname[count_group], sizeof(group.Surname[count_group]));
                cin >> group.Name[count_group];
                file.write((char*)&group.Name[count_group], sizeof(group.Name[count_group]));
                cin >> group.Otch[count_group];
                file.write((char*)&group.Otch[count_group], sizeof(group.Otch[count_group]));

                cout << "Введите специальность: ";
                cin >> group.Spec[count_group];
                file.write((char*)&group.Spec[count_group], sizeof(group.Spec[count_group]));

                cout << "Введите средний балл группы: ";
                cin >> group.Medmark[count_group];
                file.write((char*)&group.Medmark[count_group], sizeof(group.Medmark[count_group]));

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
                file.open(namef, ios::binary, ios::in);

                cout << "/////////////////////////////////////////////////" << endl << endl;
                cout << "\t\tПросмотр содержания файла" << endl << endl;

                for (size_t i = 0; i < count_group; i++)
                {
                    file.read((char*)&group.Groups[i], sizeof(group.Groups[i]));
                    file.read((char*)&group.Surname[i], sizeof(group.Surname[i]));
                    file.read((char*)&group.Name[i], sizeof(group.Name[i]));
                    file.read((char*)&group.Otch[i], sizeof(group.Otch[i]));
                    file.read((char*)&group.Spec[i], sizeof(group.Spec[i]));
                    file.read((char*)&group.Medmark[i], sizeof(group.Medmark[i]));
                    cout << "Группа: " << group.Groups[i] << " ФИО куратора: " << group.Surname[i] << ' ' << group.Name[i] << ' ' << group.Otch[i] << " Cпециальность: " << group.Spec[i] << " Срдний балл по группе: " << group.Medmark[i] << endl;

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
                file.open(namef, ios::binary, ios::in);
                string surname;
                bool flag = true;
                cout << "Введите фамилию куратора: ";
                cin >> surname;
                for (size_t i = 0; i < count_group; i++)
                {
                    file.read((char*)&group.Surname[i], sizeof(group.Surname[i]));
                    if (group.Surname[i] == surname) {
                        cout << "Группа: " << group.Groups[i] << " ФИО куратора: " << group.Surname[i] << ' ' << group.Name[i] << ' ' << group.Otch[i] << " Cпециальность: " << group.Spec[i] << " Срдний балл по группе: " << group.Medmark[i] << endl;
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

                file.open(namef, ios::binary, ios::in);
                bool flag1 = true;
                for (size_t i = 0; i < count_group; i++)
                {
                    file.read((char*)&group.Medmark[i], sizeof(group.Surname[i]));
                    if (group.Medmark[i] < 7.0) {
                        cout << "Группа: " << group.Groups[i] << " ФИО куратора: " << group.Surname[i] << ' ' << group.Name[i] << ' ' << group.Otch[i] << " Cпециальность: " << group.Spec[i] << " Срдний балл по группе: " << group.Medmark[i] << endl;
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
            }



        }
    }

}

