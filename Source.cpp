#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>
#include "functions.h"
#include <cstdlib>

using namespace std;

//char *file_name[];

int main(int argc, char *argv[]){
    clear_scr();
    
    system("chcp 65001");
    //Чтение файла с матрицей
    //string file_name="array.txt";
    string file_name = argv[1];
    fstream f;
    f.open(file_name);
    //ifstream inp(file_name);
    int r = 0;
    int c = 0;
    while (!(f.is_open()))
    {
        cout << "Ошибка открытия файла" << file_name << endl;
        cout << "Введите имя файла с расширением, в котором есть матрица(Например 'test.txt')" << endl;
        cin >> file_name;
        f.open(file_name);
    }
    while (f.ignore(numeric_limits<streamsize>::max(), '\n')){
        if (!f.eof()) // если в конце последней строки '\n', иначе не нужно
            r++;
    }

    f.close();
    cout << "Количество строк в файле равно " << r + 1 << endl;
    ifstream inp1(file_name);
    string out;
    getline(inp1, out);
    inp1.close();
    int i = 0;
    while (out[i] == ' ' && out[i] != '\0')
        i++;
    int chislo = 0;
    while (out[i] != '\0') {
        if (out[i] != ' ' && chislo == 0){
           chislo = 1;
            c++;
        }
        else if (out[i] == ' ')
            chislo = 0;
        i++;
    }
    cout << "Количество столбцов = " << c << endl;
    int row=r+1;
    int column=c;
    //создание матрицы
    int** array = (int**)malloc(row * sizeof(int));//создание матрицы
    for (int i = 0; i < row; i++) {
        array[i] = (int*)malloc(column * sizeof(int));
    }

    ifstream f1(file_name);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            f1 >> array[i][j];
        }
    }
    f1.close();
    //вывод массива на экран
    cout << "\n\nПолученный массив из файла:\n";
    printArray(array, row, column);
    //копирование массива в другой массив
    int** array1 = (int**)malloc(row * sizeof(int*));
    for (int i = 0; i < row; i++) {
        array1[i] = (int*)malloc(column * sizeof(int));
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            array1[i][j] = array[i][j];
        }
    }
    ///////////////////////////////////////////сортировка 1 строки///////////////////////////////////////////
    int* string_column = replay_string(column,array1,0);//копирование нужной строки из массива
    string_column = bubble(string_column, column);//сортировка строки
    перезапись_массива(column, string_column, array1,0);//формирование отсортированного массива
    cout << "\n\nПолученный массив после сортировки 1 строки:\n";
    printArray(array1, row, column);
    delete[] string_column;
    ///////////////////////////////////////////сортировка 1 столбца///////////////////////////////////////////
    int* string_row = replay_string(0,array1, row);//копирование нужной строки из массива
    string_row = bubble(string_row, row);//сортировка строки
    перезапись_массива(0, string_row, array1, row);//формирование отсортированного массива
    cout << "\n\nПолученный массив после сортировки 1 колонки:\n";
    printArray(array1, row, column);
    ///////////////////////////////////////////сортировка диагонали справа сверху в право низ///////////////////////////////////////////
    int p = 0;
    if (column > row) p = row;
    else p = column;
    int* string_1 = replay_string(p, array1,0);
    // Сортировка массива пузырьком
    string_1 = bubble(string_1, row);
    запись_массива_диагонали_1(p,string_1,array1,0);
    cout << "\n\nПолученный массив после сортировки диагонали(с левого верхнего в правый нижний угол)\n";
    printArray(array1, row, column);
    ///////////////////////////////////////////сортировка лиагонали с левого низа в правый верх///////////////////////////////////////////
    int* string_2 = replay_string(p,array1,0);
    // Сортировка массива пузырьком
    string_2 = bubble(string_2, row);
    запись_массива_диагонали_2(p,string_2,array1, row);
    /*for (int i = 0; i < p; i++) {
        array1[row - 1 - i][i] = string_2[i];
    }*/
    cout << "\n\nПолученный массив после сортировки диагонали(с левого нижнего в правый верхний угол)\n";
    printArray(array1, row, column);
    /////////////////////////////////////////нахождение минимального пути/////////////////////////////////////////////////////////////
    //вывод первоначального массива на экран
    cout << "-------------------------------" << endl;
    cout << "Вывод массива, по которому будет искаться минимальный путь: " << endl;
    printArray(array, row, column);
    //минимальный путь
    int max_roads = row * column;
    cout << "Максимальное количество путей =" << max_roads << endl;
    cout << "-------------------------------" << endl;
    int min = minim_road(row,column,array);
    cout << "Минимальный путь из левого верхнего угла в нижний правый = " << min << endl;
    system("pause");
    return 0;
}