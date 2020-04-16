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
    cin >> capacity;
    while (capacity > 10) {
        cout << "Мощность представлена натуральными числами от 0 до 10.\n" << "Введите мощность множества А заново: " << endl;
        cin >> capacity;
    }
    cout << "Введите элементы множества А:" << endl;
    for (int i = 0; i < capacity; ++i) {
        cin >> input;
        while (input > 30) {
            cout << "Элементы множества принадлежат диапозону натуральных чисел от 1 до 30.\n" << "Введите элементы множества А заново: " << endl;
            cin >> input;
        }
        a.push_back(input);
    }
    cout << "Введите мощность множества В:" << endl;
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
            if (a[j] == b[i]) {
                cache_a.push_back(j);
                cache_b.push_back(i);
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
        cin >> menu_item;
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

void intersection (vector<int>& a, vector<int>& cache_a, bool& intersection_exists) {
    if (intersection_exists) {
        vector<int> r;
        r.reserve(cache_a.size());   //preallocate memory
        for (int i : cache_a) {  //for (int i = 0; i < cache_a.size(); ++i)
            r.push_back(a[i]);
        }
        cout << "Пересечение множеств: {";
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

void _union (vector<int>& a, vector<int>& b, vector<int>& cache_a, bool& intersection_exists) {
    vector<int> r;
    r = a;
    if (intersection_exists) {
        for (int i = cache_a.size(); i > 0; --i) {   //for (int i = 0; i < cache_a.size(); ++i)
            r.erase(r.begin() + (cache_a[i - 1]));
        }
    }
    r.insert(r.end(), b.begin(), b.end());
    cout << "Объединение множеств: {";
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

void set_difference (vector<int>& a, vector<int>& b, vector<int>& cache_a, vector<int>& cache_b, bool& intersection_exists) {
    vector<int> r;
    r = a;
    if (intersection_exists) {
        for (int i = cache_a.size(); i > 0; --i) {   //for (int i = 0; i < cache_a.size(); ++i)
            r.erase(r.begin() + (cache_a[i - 1]));
        }
    }
    cout << "Разность множеств\n";
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
    r = b;
    if (intersection_exists) {
        for (int i = cache_b.size(); i > 0; --i) {   //for (int i = 0; i < cache_a.size(); ++i)
            r.erase(r.begin() + (cache_b[i - 1]));
        }
    }
    cout << "B\\A:";
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

void symmetric_difference (vector<int>& a, vector<int>& b, vector<int>& cache_a, vector<int>& cache_b, bool& intersection_exists)
{
    vector<int> ra;
    ra = a;
    if (intersection_exists) {
        for (int i = cache_a.size(); i > 0; --i) {   //for (int i = 0; i < cache_a.size(); ++i)
            ra.erase(ra.begin() + (cache_a[i - 1]));
        }
    }
    vector<int> rb;
    rb = b;

    if (intersection_exists) {
        for (int i = cache_b.size(); i > 0; --i) {   //for (int i = 0; i < cache_a.size(); ++i)
            rb.erase(rb.begin() + (cache_b[i - 1]));
        }
    }

    cout << "Симметрическая разность: {";
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
    vector<vector<vector<int>>> r(a.size(), vector<vector<int>>(b.size(), vector<int> (2)));

    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b.size(); ++j) {
            r[i][j][0] = a[j];
            r[i][j][1] = b[i];
        }
    }
    //TODO: добавьте здесь сообщение о том, что это декартово произведение
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b.size(); ++j) {
            cout << "{" << r[i][j][0] << "," << r[i][j][1] << "}" << " ";
        }
        cout << endl;
    }
}
