#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;
//сортировка пузырьком
int* bubble(int* string_2, int row) {
    int temp = 0;
    for (int i = 0; i < row - 1; i++) {
        for (int j = 0; j < row - i - 1; j++) {
            if (string_2[j] > string_2[j + 1]) {
                // меняем элементы местами
                temp = string_2[j];
                string_2[j] = string_2[j + 1];
                string_2[j + 1] = temp;
            }
        }
    }
    return string_2;
}
//вывод массива на экран
void printArray(int **array, const int row, const int column) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++)
            cout << setw(4) << array[i][j];
        cout << endl;
    }
}
//Подсчет минимальных путей в матрице
int minim_road(int row, int column, int **array ) {
    int min_cell_right = 0;
    int min_cell_bot = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {//перебор всех ячеек
            if (i == 0 || j == 0) {
                if (i == 0)  array[i][j] = array[i][j] + array[i][j - 1];//если индекс строки 0, то двигаться только вправо по матрице
                else array[i][j] = array[i][j] + array[i - 1][j];//если индекс столбца 0, то двигаться только вниз по матрице
            }
            else {//если индекс не равен 0, то двигаться можно и вниз и вправо по матрице
                min_cell_right = array[i][j] + array[i][j - 1];
                min_cell_bot = array[i][j] + array[i - 1][j];
                if (min_cell_right < min_cell_bot)  array[i][j] = min_cell_right;
                else array[i][j] = min_cell_bot;
            }
            if (i == 0 && j == 0) array[i][j] = 9;
            min_cell_right = 0;
            min_cell_bot = 0;
        }
    }
    cout << "Массив с минимальными путями: " << endl;
    printArray(array, row, column);
    return array[row - 1][column - 1];
}

int* replay_string(int k, int **array1, int c){
    int* string = new int[k];
    for (int i = 0;i < k; i++) {
        string[i] = { array1[c][i] };
    }
    return string;
}

void clear_scr() {//очистка консоли
  cout << "\e[1;1H\e[2J";
}

void запись_массива(int p, int * хуйня, int** массив){//для сортировки строки и столбца
  for (int i = 0; i < p; i++) {
        массив[i][i] = хуйня[i];
    }
}

void перезапись_массива(int column, int* string_column, int** array1, int k){//формирование массива со строкой и столбцом
    for (int i = 0; i < column; i++) {
        array1[k][i] = string_column[i];
    }
}

void запись_массива_диагонали_1(int p, int *хуйня, int **массив, int k){
    for (int i = 0; i < p; i++,k++)
    {
        массив[k][i] = хуйня[i];
    }
}

void запись_массива_диагонали_2(int p, int *хуйня, int **массив, int row)
{
    for (int i = 0; i < p; i++)
    {
        массив[row-1-i][i] = хуйня[i];
    }
}