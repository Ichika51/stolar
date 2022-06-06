#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int* bubble(int* string_2, int row) {
    int temp = 0;
    for (int i = 0; i < row - 1; i++) {
        for (int j = 0; j < row - i - 1; j++) {
            if (string_2[j] > string_2[j + 1]) {
                // ������ �������� �������
                temp = string_2[j];
                string_2[j] = string_2[j + 1];
                string_2[j + 1] = temp;
            }
        }
    }
    return string_2;
}

void printArray(int **array, const int row, const int column) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++)
            cout << setw(4) << array[i][j];
        cout << endl;
    }
}

int minim_road(int row, int column, int **array ) {
    int min_cell_right = 0;
    int min_cell_bot = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {//������� ���� �����
            if (i == 0 || j == 0) {
                if (i == 0)  array[i][j] = array[i][j] + array[i][j - 1];//���� ������ ������ 0, �� ��������� ������ ������ �� �������
                else array[i][j] = array[i][j] + array[i - 1][j];//���� ������ ������� 0, �� ��������� ������ ���� �� �������
            }
            else {//���� ������ �� ����� 0, �� ��������� ����� � ���� � ������ �� �������
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
    cout << "������ � ������������ ������: " << endl;
    printArray(array, row, column);
    return array[row - 1][column - 1];
}

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    //���� ���������� ����� � �������� � �������
    ifstream inp("array.txt");
    int r = 0;
    int c = 0;
    if (!inp)
        cout << "������ �������� �����" << endl;
    else{
        while (inp.ignore(numeric_limits<streamsize>::max(), '\n')){
            if (!inp.eof()) // ���� � ����� ��������� ������ '\n', ����� �� �����
                r++;
        }
    }
    inp.close();
    cout << "���������� ����� � ����� ����� " << r + 1 << endl;
    ifstream inp1("array.txt");
    string out;
    getline(inp1, out);
    inp1.close();
    int i = 0;
    while (out[i] == ' ' && out[i] != '\0')
        i++;
    int chislo = 0;
    while (out[i] != '\0') {
        if (out[i] != ' ' && chislo == 0)
        {
           chislo = 1;
            c++;
        }
        else if (out[i] == ' ')
            chislo = 0;
        i++;
    }
    cout << "���������� �������� = " << c << endl;
    int row=r+1;
    int column=c;
    //�������� �������
    int** array = (int**)malloc(row * sizeof(int));//�������� �������
    for (int i = 0; i < row; i++) {
        array[i] = (int*)malloc(column * sizeof(int));
    }

    ifstream f("array.txt");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            f >> array[i][j];
        }
    }
    f.close();
    //����� ������� �� �����
    cout << "\n\n���������� ������ �� �����:\n";
    printArray(array, row, column);
    //����������� ������� � ������ ������
    int** array1 = (int**)malloc(row * sizeof(int*));
    for (int i = 0; i < row; i++) {
        array1[i] = (int*)malloc(column * sizeof(int));
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            array1[i][j] = array[i][j];
        }
    }
    ///////////////////////////////////////////���������� 1 ������///////////////////////////////////////////
    int* string = new int[column];
    for (int i = 0;i < column; i++) {
        string[i] = { array1[0][i] };
    }
    string = bubble(string, column);
    for (int i = 0; i < column; i++) {
        array1[0][i] = string[i];
    }
    cout << "\n\n���������� ������ ����� ���������� 1 ������:\n";
    printArray(array1, row, column);
    delete[] string;
    ///////////////////////////////////////////���������� 1 �������///////////////////////////////////////////
    int* string_row = new int[row];
    for (int i = 0;i < row; i++) {
        string_row[i] = { array1[i][0] };
    }
    string_row = bubble(string_row, row);
    for (int i = 0; i < row; i++) {
        array1[i][0] = string_row[i];
    }
    cout << "\n\n���������� ������ ����� ���������� 1 �������:\n";
    printArray(array1, row, column);
    ///////////////////////////////////////////���������� ��������� ������ ������ � ����� ���///////////////////////////////////////////
    int p = 0;
    if (column > row) p = row;
    else p = column;
    int* string_1 = new int[p];
    for (int i = 0;i < p; i++) {
        string_1[i] = { array1[i][i] };
    }
    // ���������� ������� ���������
    string_1 = bubble(string_1, row);
    for (int i = 0; i < p; i++) {
        array1[i][i] = string_1[i];
    }
    cout << "\n\n���������� ������ ����� ���������� ���������(� ������ �������� � ������ ������ ����)\n";
    printArray(array1, row, column);
    ///////////////////////////////////////////���������� ��������� � ������ ���� � ������ ����///////////////////////////////////////////
    int* string_2 = new int[p];
    for (int i = 0;i < p; i++) {
        string_2[i] = { array1[row - 1 - i][i] };
    }
    // ���������� ������� ���������
    string_2 = bubble(string_2, row);
    for (int i = 0; i < p; i++) {
        array1[row - 1 - i][i] = string_2[i];
    }
    cout << "\n\n���������� ������ ����� ���������� ���������(� ������ ������� � ������ ������� ����)\n";
    printArray(array1, row, column);
    /////////////////////////////////////////���������� ������������ ����/////////////////////////////////////////////////////////////
    //����� ��������������� ������� �� �����
    cout << "-------------------------------" << endl;
    cout << "����� �������, �� �������� ����� �������� ����������� ����: " << endl;
    printArray(array, row, column);
    //����������� ����
    int max_roads = row * column;
    cout << "������������ ���������� ����� =" << max_roads << endl;
    cout << "-------------------------------" << endl;
    int min = minim_road(row,column,array);
    cout << "����������� ���� �� ������ �������� ���� � ������ ������ = " << min << endl;
    return 0;
}