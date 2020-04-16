#include <iostream>
#include <vector>

//TODO: translate all the text to the Russian language

using namespace std;

void assignment(vector<int>& a, vector<int>& b);

void preprocessing (vector<int>& a, vector<int>& b, vector<int>& cash_a, vector<int>& cash_b, bool& intersection_exists);

int menu (vector<int>& a, vector<int>& b, vector<int>& cash_a, vector<int>& cash_b, bool& intersection_exists);

void intersection (vector<int>& a, vector<int>& cash_a, bool& intersection_exists);

void _union (vector<int>& a, vector<int>& b, vector<int>& cash_a, bool& intersection_exists);

void set_difference (vector<int>& a, vector<int>& b, vector<int>& cash_a, vector<int>& cash_b, bool& intersection_exists);

int main() {
    vector<int> cash_a, cash_b, a, b;
    bool intersection_exists = false;
    assignment(a, b);
    preprocessing (a, b, cash_a, cash_b, intersection_exists);
    menu(a, b, cash_a, cash_b, intersection_exists);
}

void assignment (vector<int>& a, vector<int>& b) {
    int capacity, input;
    cout << "Enter capacity of the set A:" << endl;
    cin >> capacity;
    while (capacity > 10) {
        cout << "Capacity supposed to be in the range of numbers from 1 to 10\n" << "Please, re-enter capacity of the set A:" << endl;
        cin >> capacity;
    }
    cout << "Enter elements of the set A:" << endl;
    for (int i = 0; i < capacity; ++i) {
        cin >> input;
        while (input > 30) {
            cout << "Elements supposed to be in the range of numbers from 1 to 30\n" << "Please, re-enter element of the set A:" << endl;
            cin >> input;
        }
        a.push_back(input);
    }
    cout << "Enter capacity of the set B:" << endl;
    cin >> capacity;
    while (capacity > 10) {
        cout << "Capacity supposed to be in the range of numbers from 1 to 10\n" << "Please, re-enter capacity of the set A:" << endl;
        cin >> capacity;
    }
    cout << "Enter elements of the set B:" << endl;
    for (int i = 0; i < capacity; ++i) {
        cin >> input;
        while (input > 30) {
            cout << "Elements supposed to be in the range of numbers from 1 to 30\n" << "Please, re-enter element of the set A:" << endl;
            cin >> input;
        }
        b.push_back(input);
    }
}

void preprocessing (vector<int>& a, vector<int>& b, vector<int>& cash_a, vector<int>& cash_b, bool& intersection_exists) {
    for (int j = 0; j < a.size(); ++j) {
        for (int i = 0; i < b.size(); ++i) {
            if (a[j] == b[i]) {
                cash_a.push_back(j);
                cash_b.push_back(i);
                intersection_exists = true;
            }
        }
    }
}

int menu (vector<int>& a, vector<int>& b, vector<int>& cash_a, vector<int>& cash_b, bool& intersection_exists) {
    int menu_item;
    cout << "Enter a number to choose menu item" << "\n1 - Intersection" << "\n2 - Union" << "\n3 - Set difference"
         << "\n4 - Exit" << endl;
    while (true) {
        cin >> menu_item;
        switch (menu_item) {
            case 1: {
                intersection(a, cash_a, intersection_exists);
                break;
            }
            case 2: {
                _union(a, b, cash_a, intersection_exists);
                break;
            }
            case 3: {
                set_difference(a, b, cash_a, cash_b, intersection_exists);
                break;
            }
            default: {
                return 0;
            }
        }
    }
}

void intersection (vector<int>& a, vector<int>& cash_a, bool& intersection_exists) {
    if (intersection_exists) {
        vector<int> r;
        r = a;
        for (int i = 0; i < r.size(); ++i) {
            if (i == cash_a[i]) {
                continue;
            }
            r.erase(r.begin() + i);
        }
        cout << "Intersection of the sets: {";
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
        cout << "There are no similar numbers in sets" << endl;
    }
}

void _union (vector<int>& a, vector<int>& b, vector<int>& cash_a, bool& intersection_exists){
    vector<int> r;
    r = a;
    if (intersection_exists) {
        for (int i : cash_a) {      //for (int i = 0; i < cash_a.size(); ++i)
            r.erase(r.begin() + i);
        }
    }
    r.insert(r.end(), b.begin(), b.end());
    cout << "Union of the sets: {";
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

void set_difference (vector<int>& a, vector<int>& b, vector<int>& cash_a, vector<int>& cash_b, bool& intersection_exists) {
    vector<int> r;
    r = a;
    if (intersection_exists) {
        for (int i : cash_a) {      //for (int i = 0; i < cash_a.size(); ++i)
            r.erase(r.begin() + i);
        }
    }
    cout << "Set difference\n";
    cout << "A\\B:";
    if (r.empty()) {
        cout << " empty set" << endl;
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
        for (int i : cash_b) {      //for (int i = 0; i < cash_b.size(); ++i)
            r.erase(r.begin() + i);
        }
    }
    cout << "B\\A:";
    if (r.empty()) {
        cout << " empty set" << endl;
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