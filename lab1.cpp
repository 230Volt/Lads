#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;

// --- Допоміжні функції для роботи з множинами ---

void print_set(const set<int>& s, const string& name) {
    cout << name << " = { ";
    if (s.empty()) {
        cout << "порожня множина (∅)";
    } else {
        for (auto it = s.begin(); it != s.end(); ++it) {
            cout << *it << (next(it) == s.end() ? "" : ", ");
        }
    }
    cout << " }\n";
}

void print_set_str(const set<string>& s, const string& name) {
    cout << name << " = { ";
    if (s.empty()) {
        cout << "∅";
    } else {
        for (auto it = s.begin(); it != s.end(); ++it) {
            cout << *it << (next(it) == s.end() ? "" : ", ");
        }
    }
    cout << " }\n";
}

// Об'єднання: A ∪ B
template<typename T>
set<T> set_union_op(const set<T>& a, const set<T>& b) {
    set<T> res;
    set_union(a.begin(), a.end(), b.begin(), b.end(), inserter(res, res.begin()));
    return res;
}

// Перетин: A ∩ B
template<typename T>
set<T> set_intersection_op(const set<T>& a, const set<T>& b) {
    set<T> res;
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(res, res.begin()));
    return res;
}

// Різниця: A \ B
template<typename T>
set<T> set_difference_op(const set<T>& a, const set<T>& b) {
    set<T> res;
    set_difference(a.begin(), a.end(), b.begin(), b.end(), inserter(res, res.begin()));
    return res;
}

// Симетрична різниця: A Δ B
template<typename T>
set<T> set_sym_diff_op(const set<T>& a, const set<T>& b) {
    set<T> res;
    set_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(), inserter(res, res.begin()));
    return res;
}

// Доповнення: A' = U \ A
template<typename T>
set<T> set_complement_op(const set<T>& a, const set<T>& u) {
    return set_difference_op(u, a);
}

// Перевірка включення: A ⊆ B
template<typename T>
bool is_subset_of(const set<T>& a, const set<T>& b) {
    return includes(b.begin(), b.end(), a.begin(), a.end());
}

// Генерація та виведення булеана
void generate_power_set(const set<int>& s) {
    vector<int> elements(s.begin(), s.end());
    int n = elements.size();
    long long total_subsets = 1LL << n; // 2^n

    cout << "Потужність множини |D| = " << n << "\n";
    cout << "Потужність булеана: 2^" << n << " = " << total_subsets << "\n";
    cout << "Булеан множини P(D):\n{ ";

    for (long long i = 0; i < total_subsets; ++i) {
        cout << "{";
        bool first = true;
        for (int j = 0; j < n; ++j) {
            if (i & (1LL << j)) {
                if (!first) cout << ", ";
                cout << elements[j];
                first = false;
            }
        }
        cout << "}";
        if (i < total_subsets - 1) cout << ", ";
        if ((i + 1) % 8 == 0 && i < total_subsets - 1) cout << "\n  ";
    }
    cout << " }\n";
}

int main() {
    setlocale(LC_ALL, "uk_UA.UTF-8");

    // Вихідні дані Варіанту 8
    set<int> A = {1, 4, 7, 10};
    set<int> B = {2, 5, 8, 11};
    set<int> C = {1, 2, 3, 4, 5};
    set<int> U = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    cout << "========================================================\n";
    cout << " ЛАБОРАТОРНА РОБОТА №1. ТЕОРІЯ МНОЖИН (ВАРІАНТ 8)\n";
    cout << " Студент: Талько Іван, Група: Кік-26-1_8\n";
    cout << "========================================================\n\n";

    cout << "--- ВИХІДНІ МНОЖИНИ ---\n";
    print_set(A, "A");
    print_set(B, "B");
    print_set(C, "C");
    print_set(U, "U");
    cout << "\n";

    // ----------------------------------------------------
    // ЗАВДАННЯ 1: Операції з множинами
    // ----------------------------------------------------
    cout << "================ ЗАВДАННЯ 1 ================\n";
    // а) (A ∪ B') ∩ C
    set<int> B_prime = set_complement_op(B, U);
    set<int> A_union_B_prime = set_union_op(A, B_prime);
    set<int> task1_a = set_intersection_op(A_union_B_prime, C);

    cout << "а) Знайти (A U B') ∩ C:\n";
    print_set(B_prime, "   B' = U \\ B");
    print_set(A_union_B_prime, "   A U B'");
    print_set(task1_a, "   Результат (A U B') ∩ C");

    // б) B Δ (A' \ C)'
    set<int> A_prime = set_complement_op(A, U);
    set<int> A_prime_diff_C = set_difference_op(A_prime, C);
    set<int> comp_diff = set_complement_op(A_prime_diff_C, U);
    set<int> task1_b = set_sym_diff_op(B, comp_diff);

    cout << "\nб) Знайти B Δ (A' \\ C)':\n";
    print_set(A_prime, "   A' = U \\ A");
    print_set(A_prime_diff_C, "   A' \\ C");
    print_set(comp_diff, "   (A' \\ C)' = U \\ (A' \\ C)");
    print_set(task1_b, "   Результат B Δ (A' \\ C)'");
    cout << "\n";

    // ----------------------------------------------------
    // ЗАВДАННЯ 2: Побудова множини та булеана
    // Варіант 8: (A \ C') ∪ B
    // ----------------------------------------------------
    cout << "================ ЗАВДАННЯ 2 ================\n";
    set<int> C_prime = set_complement_op(C, U);
    set<int> A_diff_C_prime = set_difference_op(A, C_prime);
    set<int> D = set_union_op(A_diff_C_prime, B);

    cout << "Вираз: D = (A \\ C') U B\n";
    print_set(C_prime, "C'");
    print_set(A_diff_C_prime, "A \\ C'");
    print_set(D, "Множина D");
    cout << "\n";
    generate_power_set(D);
    cout << "\n";

    // ----------------------------------------------------
    // ЗАВДАННЯ 3: Перевірка вірності тверджень
    // Варіант 8
    // ----------------------------------------------------
    cout << "================ ЗАВДАННЯ 3 ================\n";
    cout << "Перевірка тверджень Варіанту 8:\n";

    // а) {5} ∈ {1, 2, 3, 4, 5}
    // {5} є підмножиною, а не елементом множини простих чисел
    cout << "а) {5} ∈ {1, 2, 3, 4, 5} -> ХИБНО (False).\n";
    cout << "   Пояснення: {5} є підмножиною ( {5} ⊂ {1,2,3,4,5} ), а не елементом.\n";

    // б) Q ∩ R = Q
    cout << "б) Q ∩ R = Q -> ІСТИННО (True).\n";
    cout << "   Пояснення: Оскільки множина раціональних чисел Q є підмножиною дійсних R (Q ⊂ R).\n";

    // в) A ∪ (B \ A) = A ∪ B
    set<int> B_diff_A = set_difference_op(B, A);
    set<int> lhs_3c = set_union_op(A, B_diff_A);
    set<int> rhs_3c = set_union_op(A, B);
    cout << "в) A ∪ (B \\ A) = A ∪ B -> " << (lhs_3c == rhs_3c ? "ІСТИННО (True)" : "ХИБНО (False)") << "\n";

    // г) A Δ B = (A ∪ B) \ (A ∩ B)
    set<int> sym_diff_direct = set_sym_diff_op(A, B);
    set<int> sym_diff_def = set_difference_op(set_union_op(A, B), set_intersection_op(A, B));
    cout << "г) A Δ B = (A ∪ B) \\ (A ∩ B) -> " << (sym_diff_direct == sym_diff_def ? "ІСТИННО (True)" : "ХИБНО (False)") << "\n";

    // д) якщо A ⊆ B, то A ∩ C ⊆ B ∩ C
    // Створюємо перевірочний випадок A_sub ⊆ B_sup
    set<int> A_sub = {1, 4};
    set<int> B_sup = {1, 4, 7, 10}; // A_sub ⊆ B_sup
    set<int> A_cap_C = set_intersection_op(A_sub, C);
    set<int> B_cap_C = set_intersection_op(B_sup, C);
    bool statement_3d = is_subset_of(A_cap_C, B_cap_C);
    cout << "д) Якщо A ⊆ B, то A ∩ C ⊆ B ∩ C -> " << (statement_3d ? "ІСТИННО (True)" : "ХИБНО (False)") << "\n\n";

    // ----------------------------------------------------
    // ЗАВДАННЯ 4: Логічне доведення тотожності
    // Варіант 8: A ∩ B = A \ (A \ B)
    // ----------------------------------------------------
    cout << "================ ЗАВДАННЯ 4 ================\n";
    cout << "Довести тотожність: A ∩ B = A \\ (A \\ B)\n";

    set<int> task4_LHS = set_intersection_op(A, B);
    set<int> A_diff_B = set_difference_op(A, B);
    set<int> task4_RHS = set_difference_op(A, A_diff_B);

    print_set(task4_LHS, "LHS (A ∩ B)");
    print_set(A_diff_B, "A \\ B");
    print_set(task4_RHS, "RHS (A \\ (A \\ B))");

    cout << "Програмна перевірка: тотожність " << (task4_LHS == task4_RHS ? "ДОВЕДЕНА (LHS == RHS)" : "ХИБНА") << "\n";
    cout << "Логічний висновок: x ∈ A \\ (A \\ B) ⟺ (x ∈ A) ∧ ¬(x ∈ A ∧ x ∉ B)\n";
    cout << "                  ⟺ (x ∈ A) ∧ (x ∉ A ∨ x ∈ B) ⟺ (x ∈ A ∧ x ∈ B) ⟺ x ∈ A ∩ B.\n\n";

    // ----------------------------------------------------
    // ЗАВДАННЯ 5: Розрахунок множини для діаграми Ейлера-Венна
    // Варіант 8: B ∩ (A Δ C)
    // ----------------------------------------------------
    cout << "================ ЗАВДАННЯ 5 ================\n";
    cout << "Розрахунок виразу для діаграми Венна: B ∩ (A Δ C)\n";
    set<int> A_sym_C = set_sym_diff_op(A, C);
    set<int> task5_res = set_intersection_op(B, A_sym_C);

    print_set(A_sym_C, "A Δ C");
    print_set(task5_res, "Результат B ∩ (A Δ C)");
    cout << "Область штрихування на діаграмі відповідає частинам множини B,\n";
    cout << "які належать або тільки A, або тільки C (без їх спільного перетину).\n\n";

    // ----------------------------------------------------
    // ЗАВДАННЯ 6: Моделювання аналітичного виразу для 6 множин
    // Діаграма 8: заштриховані спільні сектори кіл (Д, Е) з (А, Б)
    // Аналітичний вираз: ((Д ∪ Е) ∩ (А ∪ Б)) \ (Д ∩ Е)
    // ----------------------------------------------------
    cout << "================ ЗАВДАННЯ 6 ================\n";
    cout << "Аналітичний вираз для заштрихованої області рисунка 8:\n";
    cout << "Вираз: ((Д ∪ Е) ∩ (А ∪ Б)) \\ (Д ∩ Е)\n";
    cout << "   або: (А ∩ (Д Δ Е)) ∪ (Б ∩ (Д Δ Е))\n";

    // Моделювання дискретними зонами для верифікації формули
    set<string> reg_A = {"reg_A_top", "reg_A_D", "reg_A_E"};
    set<string> reg_B = {"reg_B_bottom", "reg_B_D", "reg_B_E"};
    set<string> reg_D = {"reg_A_D", "reg_B_D", "reg_center"};
    set<string> reg_E = {"reg_A_E", "reg_B_E", "reg_center"};

    set<string> D_union_E = set_union_op(reg_D, reg_E);
    set<string> A_union_B = set_union_op(reg_A, reg_B);
    set<string> inter_all = set_intersection_op(D_union_E, A_union_B);
    set<string> D_inter_E = set_intersection_op(reg_D, reg_E);
    set<string> shaded_area = set_difference_op(inter_all, D_inter_E);

    print_set_str(shaded_area, "Заштриховані сектори");
    cout << "\n";

    // ----------------------------------------------------
    // ЗАВДАННЯ 7: Спрощення виразу
    // Варіант 8: A Δ ∅
    // ----------------------------------------------------
    cout << "================ ЗАВДАННЯ 7 ================\n";
    cout << "Спростити вираз за законами алгебри множин: A Δ ∅\n";
    set<int> empty_set;
    set<int> task7_res = set_sym_diff_op(A, empty_set);

    print_set(task7_res, "A Δ ∅");
    cout << "Аналітичне спрощення: A Δ ∅ = (A \\ ∅) ∪ (∅ \\ A) = A ∪ ∅ = A.\n";
    cout << "Перевірка тотожності (task7_res == A): " << (task7_res == A ? "ВІРНО" : "ПОМИЛКА") << "\n";
    cout << "========================================================\n";

    return 0;
}