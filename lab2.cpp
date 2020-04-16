
#include <iostream>
#include <vector>

//TODO:

using namespace std;

void assignment (vector<int>& a, vector<int>& b);

void preprocess (vector<int>& a, vector<int>& b, vector<int>& cache_a, vector<int>& cache_b, bool& intersection_exists);

int menu (vector<int>& a, vector<int>& b, vector<int>& cache_a, vector<int>& cache_b, bool& intersection_exists);

void intersection (vector<int>& a, vector<int>& cache_a, bool& intersection_exists);

void _union (vector<int>& a, vector<int>& b, vector<int>& cache_a, bool& intersection_exists);

void set_difference (vector<int>& a, vector<int>& b, vector<int>& cache_a, vector<int>& cache_b, bool& intersection_exists);

void symmetric_difference ();

void cartesian_product (vector<int>& a, vector<int>& b);

int main() {

    setlocale(LC_ALL, "ru");

    vector<int> cash_a, cash_b, a, b;
    bool intersection_exists = false;
    assignment(a, b);
    preprocess(a, b, cash_a, cash_b, intersection_exists);
    menu(a, b, cash_a, cash_b, intersection_exists);
}

void assignment (vector<int>& a, vector<int>& b) {
    int capacity, input;
    cout << "Введите мощность множества А:" << endl;
    cin >> capacity; //Принять от пользователя мощность первого множества
    while (capacity > 10) {
        cout << "Мощность представлена натуральными числами от 0 до 10.\n" << "Введите мощность множества А заново: " << endl;
        cin >> capacity; //В случае несоответствия, принять новую мощность множества
    }
    cout << "Введите элементы множества А:" << endl;
    for (int i = 0; i < capacity; ++i) {
        cin >> input; //Принять от пользователя элементы множества, количество которых соответствует мощности множества
        while (input > 30) {
            cout << "Элементы множества принадлежат диапозону натуральных чисел от 1 до 30.\n" << "Введите элементы множества А заново: " << endl;
            cin >> input; //В случае несоответсятвия элемента диапазону, принять новые элементы
        }
        a.push_back(input); //Функция вставки элементов в вектор с конца
    }
    cout << "Введите мощность множества В:" << endl;
    cin >> capacity;
    while (capacity > 10) {
        cout << "Мощность представлена натуральными числами от 0 до 10.\n" << "Введите мощность множества В заново: " << endl;
        cin >> capacity;
    }
    cout << "Введите элементы множества B:" << endl;
    for (int i = 0; i < capacity; ++i) {
        cin >> input;
        while (input > 30) {
            cout << "Элементы множества принадлежат диапозону натуральных чисел от 1 до 30.\n" << "Введите элементы множества В заново: " << endl;
            cin >> input;
        }
        b.push_back(input); //Аналогично множеству А
    }
} 

void preprocess (vector<int>& a, vector<int>& b, vector<int>& cache_a, vector<int>& cache_b, bool& intersection_exists) { //функция предпросчета
    for (int j = 0; j < a.size(); ++j) { //Выбрать 1, 2,...,р1 элемент множества А
        for (int i = 0; i < b.size(); ++i) { //Выбрать 1, 2,...,р2 элемент множества B
            if (a[j] == b[i]) {
                cache_a.push_back(j); //Вставка элементов множества А в кэш-вектор с конца
                cache_b.push_back(i); //Вставка элементов множества В в кэш-вектор с конца
                intersection_exists = true;
            }
        }
    }
}

int menu (vector<int>& a, vector<int>& b, vector<int>& cache_a, vector<int>& cache_b, bool& intersection_exists) {
    int menu_item;
    cout << "Введите номер операции:" << "\n1 - Пересечение" << "\n2 - Объединение" << "\n3 - Разность множеств"
         << "\n4 - Декартово произведение" << "\n5 - Выход" << endl;
    while (true) {
        cin >> menu_item; //Принять номер операции, выбранный пользователем
        switch (menu_item) {
            case 1: {
                intersection(a, cache_a, intersection_exists);
                break;
            }
            case 2: {
                _union(a, b, cache_a, intersection_exists);
                break;
            }
            case 3: {
                set_difference(a, b, cache_a, cache_b, intersection_exists);
                break;
            }

            case 4: {
                cartesian_product(a, b);
                break;
            }
            default: {
                return 0;
            }
        }
    }
}

void intersection (vector<int>& a, vector<int>& cache_a, bool& intersection_exists) { //функция пересечения
    if (intersection_exists) {
        vector<int> r;
        r = a;
        for (int i = 0; i < r.size(); ++i) { //Выбрать 1, 2, ..., р1 элемент А
            if (i == cache_a[i]) { //Если элементы совпали, продолжить
                continue;
            }
            r.erase(r.begin() + i); //Удалить несоответствующие элементы из вектора
        }
        cout << "Пересечение множеств: {"; //Вывести результат выполненной операции на экран
        for (int i = 0; i < r.size(); ++i) {
            cout << r[i];
            if (i != r.size() - 1) {
                cout << "," << " ";
            } else {
                cout << "}" << endl;
            }
        }
    }
    else {
        cout << "Множества не имеют пересечения." << endl;
    }
}

void _union (vector<int>& a, vector<int>& b, vector<int>& cache_a, bool& intersection_exists){ //функция объединения
    vector<int> r;
    r = a;
    if (intersection_exists) {
        for (int i : cache_a) {      //for (int i = 0; i < cash_a.size(); ++i)
            r.erase(r.begin() + i);  //Удалить несоответствующие элементы из вектора
        }
    }
    r.insert(r.end(), b.begin(), b.end());
    cout << "Объединение множеств: {"; //Вывести результат выполненной операции на экран
    for (int i = 0; i < r.size(); ++i) {
        cout << r[i];
        if (i != r.size() - 1) {
            cout << ",";
        }
        else {
            cout << "}" << endl;
        }
    }
}

void set_difference (vector<int>& a, vector<int>& b, vector<int>& cache_a, vector<int>& cache_b, bool& intersection_exists) { //функция разности множеств
    vector<int> r;
    r = a;
    if (intersection_exists) {
        for (int i : cache_a) {      //for (int i = 0; i < cash_a.size(); ++i) //??
            r.erase(r.begin() + i); //Удалить несоответствующие элементы из вектора
        }
    }
    cout << "Разность множеств\n"; //Вывести результат выполненной операции на экран
    cout << "A\\B:";
    if (r.empty()) {  //Случай для пустого множества
        cout << " пустое множество" << endl;
    }
    else {
        cout << " {";
        for (int i = 0; i < r.size(); ++i) {
            cout << r[i];
            if (i != r.size() - 1) {
                cout << ",";
            } else {
                cout << "}" << endl;
            }
        }
    }
    r = b;
    if (intersection_exists) { //Случай для существующего пересечения
        for (int i : cache_b) {      //for (int i = 0; i < cash_b.size(); ++i)
            r.erase(r.begin() + i); //Удалить несоответствующие элементы из вектора
        }
    }
    cout << "B\\A:"; //Вывести результат выполненной операции на экран
    if (r.empty()) {
        cout << " пустое множество" << endl;
    }
    else {
        cout << " {";
        for (int i = 0; i < r.size(); ++i) {
            cout << r[i];
            if (i != r.size() - 1) {
                cout << ",";
            } else {
                cout << "}" << endl;
            }
        }
    }
}

void symmetric_difference ()
{

}

void cartesian_product (vector<int>& a, vector<int>& b) // Декартово произведение
{
    for (int i = 0; i < a.size(); i++) { //Выбрать 1, 2,...,р1 элемент множества А
        for (int j = 0; j < b.size(); j++) { //Выбрать 1, 2,...,р2 элемент множества В
            if ( (i == a.size()-1) && (j == b.size() - 1)){
                cout << "(" << a[i] << "," << b[j] << ")"; break;
            }
            cout << "(" << a[i] << "," << b[j] << "), ";

        }
    }
}
