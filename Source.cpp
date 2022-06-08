#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>
#include "functions.h"
#include <cstdlib>
#include <cctype>
#include "choise.h"

using namespace std;


int main(int argc, char *argv[]){
    system("chcp 65001");
    string file_name;
    if (argc == 0 || argv == nullptr || argv[1]==nullptr)
    {
        cout << "Не был передан аргумент(имя файла)"<<endl;
        cout << "Введите имя файла с расширением, в котором есть матрица(Например 'test.txt')" << endl;
        cin >> file_name;
    }
    else
        file_name = argv[1];
    clear_scr();
    //Чтение файла с матрицей
    int r = 0;
    int c = 0;
    fstream f3;
    f3.open(file_name);
    while(true){
        while (!(f3.is_open()))
        {
        cout << "Ошибка открытия файла " << file_name << endl;
        cout << "Введите имя файла с расширением, в котором есть матрица(Например 'test.txt')" << endl;
        cin >> file_name;
        f3.open(file_name);
        }
        char sim;
        while (f3.is_open() && !f3.eof())
        {
        f3 >> sim;
            if (isalpha(sim) || ispunct(sim))
            {
            f3.close();
            cout << "Ошибка открытия файла " << file_name << endl;
            cout << "В файле должны содержаться только цифры и пробелы" << endl;
            cout << "Измените содержимое файла и снова введите его имя" << endl;
            cin >> file_name;
            f3.open(file_name);
            }   
        }
        if(f3.is_open() && f3.eof()){
            break;
        }
    }
    f3.close();
    //подсчет количества строк
    ifstream fa;
    fa.open(file_name);
    while (fa.ignore(numeric_limits<streamsize>::max(), '\n')){
        if (!fa.eof()) // если в конце последней строки '\n', иначе не нужно
            r++;
    }
    fa.close();
    cout << "Количество строк в файле равно " << r + 1 << endl;
    //подсчет количества столбцов
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
    choise(row,column,array1,array);
    system("pause");
    return 0;
}