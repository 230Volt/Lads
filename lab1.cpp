#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;

// Допоміжні функції виведення
void print_set(const set<int>& s, const string& name) {
    cout << name << " = { ";
    for (auto it = s.begin(); it != s.end(); ++it) {
        cout << *it << (next(it) == s.end() ? "" : ", ");
    }
    cout << " }\n";
}

void print_empty_check(const set<int>& s, const string& name) {
    if (s.empty()) cout << name << " = { \u2205 } (Порожня множина)\n";
    else print_set(s, name);
}

// Реалізація операцій над множинами
set<int> set_union(const set<int>& a, const set<int>& b) {
    set<int> res;
    set_union(a.begin(), a.end(), b.begin(), b.end(), inserter(res, res.begin()));
    return res;
}

set<int> set_intersection(const set<int>& a, const set<int>& b) {
    set<int> res;
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(res, res.begin()));
    return res;
}

set<int> set_difference(const set<int>& a, const set<int>& b) {
    set<int> res;
    set_difference(a.begin(), a.end(), b.begin(), b.end(), inserter(res, res.begin()));
    return res;
}

set<int> set_sym_diff(const set<int>& a, const set<int>& b) {
    set<int> res;
    set_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(), inserter(res, res.begin()));
    return res;
}

set<int> set_complement(const set<int>& a, const set<int>& u) {
    return set_difference(u, a);
}

bool is_subset(const set<int>& a, const set<int>& b) {
    return includes(b.begin(), b.end(), a.begin(), a.end());
}

void print_power_set(const set<int>& s) {
    vector<int> elements(s.begin(), s.end());
    int n = elements.size();
    long long power_set_size = pow(2, n);
    
    cout << "Потужність булеана: 2^" << n << " = " << power_set_size << "\n";
    cout << "Булеан множини (скорочено для виводу): \n{ ";
    for (int i = 0; i < power_set_size; i++) {
        if (i > 10 && i < power_set_size - 2) {
            if (i == 11) cout << "..., ";
            continue;
        }
        cout << "{";
        bool first = true;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                if (!first) cout << ", ";
                cout << elements[j];
                first = false;
            }
        }
        cout << "}";
        if (i < power_set_size - 1) cout << ", ";
    }
    cout << " }\n";
}

int main() {
    setlocale(LC_ALL, "uk_UA.UTF-8");

    set<int> A = {1, 4, 7, 10};
    set<int> B = {2, 5, 8, 11};
    set<int> C = {1, 2, 3, 4, 5};
    set<int> U = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    cout << "=== ВИХІДНІ МНОЖИНИ ВАРІАНТУ 8 ===\n";
    print_set(A, "A");
    print_set(B, "B");
    print_set(C, "C");
    print_set(U, "U");

    // Завдання 1
    cout << "\n=== ЗАВДАННЯ 1 ===\n";
    set<int> B_comp = set_complement(B, U);
    set<int> task1a = set_intersection(set_union(A, B_comp), C);
    print_set(task1a, "a) (A U B') \xE2\x88\xA9 C");

    set<int> A_comp = set_complement(A, U);
    set<int> task1b = set_sym_diff(B, set_complement(set_difference(A_comp, C), U));
    print_set(task1b, "б) B \xCE\x94 (A' \\ C)'");

    // Завдання 2
    cout << "\n=== ЗАВДАННЯ 2 ===\n";
    set<int> task2_set = set_union(set_difference(A, set_complement(C, U)), B);
    print_set(task2_set, "Множина D = (A \\ C') U B");
    print_power_set(task2_set);

    // Завдання 4
    cout << "\n=== ЗАВДАННЯ 4 ===\n";
    set<int> task4_LHS = set_intersection(A, B);
    set<int> task4_RHS = set_difference(A, set_difference(A, B));
    print_empty_check(task4_LHS, "LHS (A \xE2\x88\xA9 B)");
    print_empty_check(task4_RHS, "RHS (A \\ (A \\ B))");
    cout << "Результат: " << (task4_LHS == task4_RHS ? "Тотожність істинна" : "Хибно") << "\n";

    // Завдання 7
    cout << "\n=== ЗАВДАННЯ 7 ===\n";
    set<int> empty_set;
    set<int> task7_set = set_sym_diff(A, empty_set);
    print_set(task7_set, "A \xCE\x94 \u2205");
    cout << "Перевірка: " << (task7_set == A ? "Спрощено вірно (дорівнює A)" : "Помилка") << "\n";

    return 0;
}