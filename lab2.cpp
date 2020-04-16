#include <iostream>
#include <vector>

//TODO: Сделать всё до полуночи)))

using namespace std;

void assignment (vector<int>& a, vector<int>& b);

void preprocessing (vector<int>& a, vector<int>& b, vector<int>& cache_a, vector<int>& cache_b, bool& intersection_exists);

int menu (vector<int>& a, vector<int>& b, vector<int>& cache_a, vector<int>& cache_b, bool& intersection_exists);

void intersection (vector<int>& a, vector<int>& cache_a, bool& intersection_exists);

void _union (vector<int>& a, vector<int>& b, vector<int>& cache_a, bool& intersection_exists);

void set_difference (vector<int>& a, vector<int>& b, vector<int>& cache_a, vector<int>& cache_b, bool& intersection_exists);

void symmetric_difference (vector<int>& a, vector<int>& b, vector<int>& cache_a, vector<int>& cache_b, bool& intersection_exists);

void cartesian_product (vector<int>& a, vector<int>& b);

int main() {

    setlocale(LC_ALL, "ru");

    vector<int> cash_a, cash_b, a, b;
    bool intersection_exists = false;
    assignment(a, b);
    preprocessing(a, b, cash_a, cash_b, intersection_exists);
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
    for (int i = 0; i < capacity; ++i) { //Если 1 ⩽ i ⩽ 30, то i становится элементом множества А
        cin >> input; //Принять от пользователя элементы множества, количество которых соответствует мощности множества
        while (input > 30) {
            cout << "Элементы множества принадлежат диапозону натуральных чисел от 1 до 30.\n" << "Введите элементы множества А заново: " << endl;
            cin >> input; //В случае несоответсятвия элемента диапазону, принять новые элементы
        }
        a.push_back(input); //Функция вставки элементов в вектор с конца
    }
    cout << "Введите мощность множества В:" << endl; //Операции, аналогичные проведенным с множеством А
    cin >> capacity;
    while (capacity > 10) {
        cout << "Мощность представлена натуральными числами от 0 до 10.\n" << "Введите мощность множества В заново: " << endl;
        cin >> capacity;
    }
    cout << "Введите элементы множества В:" << endl;
    for (int i = 0; i < capacity; ++i) {
        cin >> input;
        while (input > 30) {
            cout << "Элементы множества принадлежат диапозону натуральных чисел от 1 до 30.\n" << "Введите элементы множества В заново: " << endl;
            cin >> input;
        }
        b.push_back(input);
    }
}

void preprocessing (vector<int>& a, vector<int>& b, vector<int>& cache_a, vector<int>& cache_b, bool& intersection_exists) {
    for (int j = 0; j < a.size(); ++j) {
        for (int i = 0; i < b.size(); ++i) {
            if (a[j] == b[i]) { //Если j-ый элемент множества A равен i-тому элементу множества B
                cache_a.push_back(j); //Запись значения j элементов множества А в кэш-вектор с конца
                cache_b.push_back(i); //Запись значения i элементов множества В в кэш-вектор с конца
                intersection_exists = true;
            }
        }
    }
}

int menu (vector<int>& a, vector<int>& b, vector<int>& cache_a, vector<int>& cache_b, bool& intersection_exists) {
    int menu_item;
    cout << "Введите номер операции:" << "\n1 - Пересечение" << "\n2 - Объединение" << "\n3 - Разность множеств"
         << "\n4 - Декартово произведение" << "\n5 - Симметрическая разность" << "\n6 - Выход" << endl;
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

            case 5: {
                symmetric_difference(a, b, cache_a, cache_b, intersection_exists);
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
        vector<int> r; //Создать пустое множество r
        r.reserve(cache_a.size());   
        for (int i : cache_a) {  //for (int i = 0; i < cache_a.size(); ++i)
            r.push_back(a[i]); //Копировать элементы множества A во множество r
        }
        cout << "Пересечение множеств: {"; //Вывести результат выполненной операции на экран
        for (int i = 0; i < r.size(); ++i) {
            cout << r[i];
            if (i != r.size() - 1) {
                cout << ",";
            } else {
                cout << "}" << endl;
            }
        }
    }
    else {
        cout << "Множества не имеют пересечения." << endl;
    }
}

void _union (vector<int>& a, vector<int>& b, vector<int>& cache_a, bool& intersection_exists) { //функция объединения
    vector<int> r; //Создать пустое множество r
    r = a; //Копировать элементы множества A во множество r
    if (intersection_exists) {
        for (int i = cache_a.size(); i > 0; --i) {   
            r.erase(r.begin() + (cache_a[i - 1])); //Удалить несоответствующие элементы из вектора
        }
    }
    r.insert(r.end(), b.begin(), b.end()); //Копировать элементы множества B во множество r
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
    vector<int> r; //Создать пустое множество r
    r = a; //Копировать элементы множества A в множество r
    if (intersection_exists) {
        for (int i = cache_a.size(); i > 0; --i) {   //for (int i = 0; i < cache_a.size(); ++i)
            r.erase(r.begin() + (cache_a[i - 1])); //Во множестве r удаляем элементы с позициями, равными значению элементов множества A
        }
    }
    cout << "Разность множеств\n"; //Вывести результат выполненной операции на экран
    cout << "A\\B:";
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
    r = b; //Перезаписать элементы множества B во множество r
    if (intersection_exists) {
        for (int i = cache_b.size(); i > 0; --i) {   //for (int i = 0; i < cache_a.size(); ++i)
            r.erase(r.begin() + (cache_b[i - 1])); //Во множестве r удаляем элементы с позициями, равными значению элементов множества B
        }
    }
    cout << "B\\A:";
    if (r.empty()) {
        cout << " пустое множество" << endl;
    }
    else { //Вывести результат выполненной операции на экран
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

void symmetric_difference (vector<int>& a, vector<int>& b, vector<int>& cache_a, vector<int>& cache_b, bool& intersection_exists) //Cимметрическая разность множеств
{
    vector<int> ra; //Cоздаём пустoe множествo
    ra = a; //Копируем элементы множества A в множество r
    if (intersection_exists) {
        for (int i = cache_a.size(); i > 0; --i) {   //for (int i = 0; i < cache_a.size(); ++i)
            ra.erase(ra.begin() + (cache_a[i - 1]));
        }
    }
    vector<int> rb; //Cоздаём пустoe множествo
    rb = b; //Копируем элементы множества A в множество r

    if (intersection_exists) {
        for (int i = cache_b.size(); i > 0; --i) {   //for (int i = 0; i < cache_a.size(); ++i)
            rb.erase(rb.begin() + (cache_b[i - 1]));
        }
    }

    cout << "Симметрическая разность: {"; //Вывести результат выполненной операции на экран
    for (int i = 0; i < ra.size(); ++i) {
        cout << ra[i];
        cout << ",";
    }

    for (int i = 0; i < rb.size(); ++i) {
        cout << rb[i];
        if (i != rb.size() - 1) {
            cout << ",";
        }
        else {
            cout << "}" << endl;
        }
    }
}

void cartesian_product (vector<int>& a, vector<int>& b) // Декартово произведение
{
    vector<vector<vector<int>>> r(a.size(), vector<vector<int>>(b.size(), vector<int> (2))); //Создаём пустое множество r

    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b.size(); ++j) {
            r[i][j][0] = a[j]; //Копируем i-ый элемент множества A 
            r[i][j][1] = b[i]; //и j-ый элемент множества B в подмножество множества r
        }
    }
    //Вывести на экран результат выполнения операции прямого произведения
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b.size(); ++j) {
            cout << "{" << r[i][j][0] << "," << r[i][j][1] << "}" << " ";
        }
        cout << endl;
    }
}
