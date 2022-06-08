#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>
#include <cstdlib>
#include <cctype>

using namespace std;

int checkNumber()
{ //проверка корректности целого числа
    int k;
    cin >> k;
    while (cin.fail() || k < 1 || k > 6)
    {
        cin.clear();
        cin.ignore(32767, '\n');
        cout << "Вы ввели неверное число(можно вводить числа 1-6)" << endl;
        cin >> k;
    }
    return k;
}

void choise(int row,int column,int **array1,int **array){
    cout << "Файл был успешно открыт." << endl;
    cout << "Какое действие нужно сделать с матрицей?" << endl;
    cout << "1-Сортировка 1 строки\n2-Сортировка 1 столбца\n3-Сортировка диагонали(справа сверху в левый низ)\n4-Сортировка диагонали(из левого низа в правый верх)" << endl;
    cout << "Или вы графист и любите минимальные пути? Тогда нажмите 5" << endl;
    while(true){
        int p = 0;
        if (column > row)
            p = row;
        else
            p = column;
        cout << "Чтобы выйти из этого ада нужно ввести 6"<<endl;
        int k = checkNumber();
        switch (k){
        case (1):{
            int *string_column = replay_string_1(column, array1, 0); //копирование нужной строки из массива
            string_column = bubble(string_column, column);         //сортировка строки
            перезапись_массива_1(column, string_column, array1, 0);  //формирование отсортированного массива
            cout << "\n\nПолученный массив после сортировки 1 строки:\n";
            printArray(array1, row, column);
            delete[] string_column;
        }
            break;
        case (2):{
            int *string_row = replay_string_2(row, array1, 0); //копирование нужной строки из массива
            string_row = bubble(string_row, row);            //сортировка строки
            перезапись_массива(row, string_row, array1, 0);  //формирование отсортированного массива
            cout << "\n\nПолученный массив после сортировки 1 столбца:\n";
            printArray(array1, row, column);
            delete[] string_row;
        }
            break;
        
        case (3):{
            int *string_1 = replay_string_1(p, array1, 0);
            // Сортировка массива пузырьком
            string_1 = bubble(string_1, row);
            запись_массива_диагонали_1(p, string_1, array1, 0);
            cout << "\n\nПолученный массив после сортировки диагонали(с левого верхнего в правый нижний угол)\n";
            printArray(array1, row, column);
        }
            break;

        case (4):{
            int *string_2 = replay_string_1(p, array1, 0);
            // Сортировка массива пузырьком
            string_2 = bubble(string_2, row);
            запись_массива_диагонали_2(p, string_2, array1, row);
            /*for (int i = 0; i < p; i++) {
                array1[row - 1 - i][i] = string_2[i];
            }*/
            cout << "\n\nПолученный массив после сортировки диагонали(с левого нижнего в правый верхний угол)\n";
            printArray(array1, row, column);
        }
            break;

        case (5):{
            cout << "Вывод массива, по которому будет искаться минимальный путь: " << endl;
            printArray(array, row, column);
            //минимальный путь
            int max_roads = row * column;
            cout << "Максимальное количество путей =" << max_roads << endl;
            cout << "-------------------------------" << endl;
            int min = minim_road(row, column, array);
            cout << "Минимальный путь из левого верхнего угла в нижний правый = " << min << endl;
        }
            break;

        case (6):{
            return;
        }
        break;
        }
    }
}