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
    if (argv[1]==nullptr)
    {
        cout << "Не был передан аргумент(имя файла)"<<endl;
        cout << "Введите имя файла с расширением, в котором есть матрица(Например 'test.txt')" << endl;
        cin >> file_name;
    }
    else
        file_name = argv[1];
    //Чтение файла с матрицей
    int r = 0;
    int c = 0;
    int l = 0;
    fstream f3;
    f3.open(file_name);
    while(true){
        open_hui(file_name);//проверка файла на его существование и содержимое
        while(f3.is_open()){
            //подсчет количества строк
            ifstream fa;
            fa.open(file_name);
            while (fa.ignore(numeric_limits<streamsize>::max(), '\n'))
            {
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
            while (out[i] != '\0')
            {
                if (out[i] != ' ' && chislo == 0)
                {
                    chislo = 1;
                    c++;
                }
                else if (out[i] == ' ')
                    chislo = 0;
                i++;
            }
            cout << "Количество столбцов = " << c << endl;
            int row = r + 1;
            int column = c;
            //создание матрицы
            int **array = (int **)malloc(row * sizeof(int)); //создание матрицы
            for (int i = 0; i < row; i++)
            {
                array[i] = (int *)malloc(column * sizeof(int));
            }
            int ch=0;
            ifstream f1(file_name);
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < column; j++)
                {
                    f1 >> array[i][j];
                    ch++;
                    if (ch>((column-1)*row)) {
                        cout << "Элементов должно быть " <<(column-1)*row<<endl;
                        f1.close();
                        cout << "Неправильная матрица(во всех строках должно быть одинаковое количество цифр)"<<endl;
                        cout << "Введите имя файла, в котором есть правильная матрица: "<<endl;
                        cin >> file_name;
                        open_hui(file_name);
                        break;
                    }
                }
            }
            f1.close();
            //вывод массива на экран
            cout << "\n\nПолученный массив из файла:\n";
            printArray(array, row, column);
            //копирование массива в другой массив
            int **array1 = (int **)malloc(row * sizeof(int *));
            for (int i = 0; i < row; i++)
            {
                array1[i] = (int *)malloc(column * sizeof(int));
            }
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < column; j++)
                {
                    array1[i][j] = array[i][j];
                }
            }
            choise(row, column, array1, array);
            system("pause");
        }

        if(f3.is_open() && f3.eof()){
            f3.close();
            break;
        }
    }
    return 0;
}