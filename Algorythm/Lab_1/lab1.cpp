#include "lab1.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <random>
#include <sstream>
#include <utility>

const int N = 10000000;

int linear_search(const std::vector<int>& arr, int key, Comparisons* comp) {
    size_t n = arr.size();
    for (size_t i = 0; i < n; ++i) {
        if (comp) comp->total++;
        if (comp) comp->total++;
        if (comp) comp->element++;
        if (arr[i] == key) return static_cast<int>(i);
    }
    if (comp) comp->total++;
    return -1;
}

int linear_search_barrier(const std::vector<int>& arr, int key, Comparisons* comp) {
    std::vector<int> arr_copy = arr;
    arr_copy.push_back(key);
    size_t i = 0;
    while (true) {
        if (comp) comp->total++;
        if (comp) comp->element++;
        if (arr_copy[i] == key) break;
        ++i;
    }
    if (i == arr.size()) return -1;
    return static_cast<int>(i);
}

int binary_search_iter(const std::vector<int>& arr, int key, Comparisons* comp) {
    int left = 0, right = static_cast<int>(arr.size()) - 1;
    while (left <= right) {
        if (comp) comp->total++;
        int mid = left + (right - left) / 2;
        if (comp) comp->total++;
        if (comp) comp->element++;
        if (arr[mid] == key) return mid;
        if (comp) comp->total++;
        if (arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    if (comp) comp->total++;
    return -1;
}

int binary_search_recursive(const std::vector<int>& arr, int left, int right, int key, Comparisons* comp) {
    if (comp) comp->total++;
    if (left > right) return -1;
    int mid = left + (right - left) / 2;
    if (comp) comp->total++;
    if (comp) comp->element++;
    if (arr[mid] == key) return mid;
    if (comp) comp->total++;
    if (arr[mid] < key)
        return binary_search_recursive(arr, mid + 1, right, key, comp);
    else
        return binary_search_recursive(arr, left, mid - 1, key, comp);
}

int binary_search_rec(const std::vector<int>& arr, int key, Comparisons* comp) {
    return binary_search_recursive(arr, 0, static_cast<int>(arr.size()) - 1, key, comp);
}

template<typename Func>
double measure_time(Func func, const std::vector<int>& arr, int key) {
    auto start = std::chrono::high_resolution_clock::now();
    func(arr, key, nullptr);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count();
}

void task1() {
    std::cout << "Задача 1\n";
    std::cout << "Генерация массивов...\n";

    std::vector<int> arr_linear(N);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, N - 1);
    for (int i = 0; i < N; ++i) arr_linear[i] = dist(gen);

    std::vector<int> arr_binary(N);
    for (int i = 0; i < N; ++i) arr_binary[i] = i;

    enum Case { FIRST, LAST, MIDDLE, NONE };
    std::vector<Case> cases = { FIRST, LAST, MIDDLE, NONE };
    std::vector<std::string> case_names = { "первым", "последним", "в середине", "нет" };

    std::vector<std::vector<std::tuple<long long, long long, double>>> results(4, std::vector<std::tuple<long long, long long, double>>(4));

    for (size_t c = 0; c < cases.size(); ++c) {
        int key;
        switch (cases[c]) {
        case FIRST: key = 0; break;
        case LAST:  key = N - 1; break;
        case MIDDLE: key = N / 2; break;
        case NONE:   key = -1; break;
        }

        std::vector<int> arr_lin = arr_linear;
        if (cases[c] == FIRST) arr_lin[0] = key;
        else if (cases[c] == LAST) arr_lin[N - 1] = key;
        else if (cases[c] == MIDDLE) arr_lin[N / 2] = key;

        std::vector<int> arr_bin = arr_binary;
        if (cases[c] == FIRST) arr_bin[0] = key;
        else if (cases[c] == LAST) arr_bin[N - 1] = key;
        else if (cases[c] == MIDDLE) arr_bin[N / 2] = key;

        Comparisons comp;
        linear_search(arr_lin, key, &comp);
        double time = 0.0;
        for (int t = 0; t < 10; ++t) time += measure_time(linear_search, arr_lin, key);
        time /= 10.0;
        results[0][c] = { comp.total, comp.element, time };

        Comparisons comp2;
        linear_search_barrier(arr_lin, key, &comp2);
        double time2 = 0.0;
        for (int t = 0; t < 10; ++t) time2 += measure_time(linear_search_barrier, arr_lin, key);
        time2 /= 10.0;
        results[1][c] = { comp2.total, comp2.element, time2 };

        Comparisons comp3;
        binary_search_iter(arr_bin, key, &comp3);
        double time3 = 0.0;
        for (int t = 0; t < 10; ++t) time3 += measure_time(binary_search_iter, arr_bin, key);
        time3 /= 10.0;
        results[2][c] = { comp3.total, comp3.element, time3 };

        Comparisons comp4;
        binary_search_rec(arr_bin, key, &comp4);
        double time4 = 0.0;
        for (int t = 0; t < 10; ++t) time4 += measure_time(binary_search_rec, arr_bin, key);
        time4 /= 10.0;
        results[3][c] = { comp4.total, comp4.element, time4 };
    }

    const int col_width = 35;      // ширина каждой колонки с данными
    const int name_width = 30;     // ширина колонки с названием метода
    std::cout << "\nКоличество сравнений при выполнении алгоритмов поиска\n\n";

    std::cout << std::setw(name_width) << std::left << "Метод";
    for (const auto& name : case_names) {
        std::cout << std::setw(col_width) << std::left << name;
    }
    std::cout << "\n";
    std::cout << std::string(name_width + 4 * col_width, '-') << "\n";

    std::vector<std::string> methods = { "Линейный поиск", "Линейный поиск с барьером",
                               "Бинарный поиск (нерекурсивная)", "Бинарный поиск (рекурсивная)" };

    for (int m = 0; m < 4; ++m) {
        std::cout << std::setw(name_width) << std::left << methods[m];
        for (int c = 0; c < 4; ++c) {
            auto [tot, elem, tm] = results[m][c];
            std::ostringstream cell;
            cell << tot << "/" << elem << " " << std::fixed << std::setprecision(6) << tm << "s";
            std::cout << std::setw(col_width) << std::left << cell.str();
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

std::pair<int, int> linear_search_2d(const std::vector<std::vector<int>>& mat, int key, Comparisons* comp) {
    size_t rows = mat.size();
    size_t cols = mat[0].size();
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (comp) comp->total++;
            if (comp) comp->total++;
            if (comp) comp->total++;
            if (comp) comp->element++;
            if (mat[i][j] == key) return { static_cast<int>(i), static_cast<int>(j) };
        }
        if (comp) comp->total++;
    }
    if (comp) comp->total++;
    return { -1, -1 };
}

std::pair<int, int> linear_search_2d_barrier(const std::vector<std::vector<int>>& mat, int key, Comparisons* comp) {
    size_t rows = mat.size();
    size_t cols = mat[0].size();
    size_t total = rows * cols;
    std::vector<int> flat(total);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            flat[i * cols + j] = mat[i][j];
    flat.push_back(key);
    size_t i = 0;
    while (true) {
        if (comp) comp->total++;
        if (comp) comp->element++;
        if (flat[i] == key) break;
        ++i;
    }
    if (i == total) return { -1, -1 };
    return { static_cast<int>(i / cols), static_cast<int>(i % cols) };
}

void task2() {
    std::cout << "Задача 2\n";
    std::vector<std::vector<int>> mat = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    int key = 5;
    Comparisons comp;
    auto pos = linear_search_2d(mat, key, &comp);
    std::cout << "Линейный поиск: элемент " << key << " найден на позиции (" << pos.first << "," << pos.second << ")\n";
    std::cout << "Сравнений (общее/с элементом): " << comp.total << "/" << comp.element << "\n";

    Comparisons comp2;
    auto pos2 = linear_search_2d_barrier(mat, key, &comp2);
    std::cout << "Линейный поиск с барьером: элемент " << key << " найден на позиции (" << pos2.first << "," << pos2.second << ")\n";
    std::cout << "Сравнений (общее/с элементом): " << comp2.total << "/" << comp2.element << "\n\n";
}

bool search_sorted_matrix(const std::vector<std::vector<int>>& mat, int x) {
    int rows = static_cast<int>(mat.size());
    if (rows == 0) return false;
    int cols = static_cast<int>(mat[0].size());
    int i = 0, j = cols - 1;
    while (i < rows && j >= 0) {
        if (mat[i][j] == x) return true;
        if (mat[i][j] > x) --j;
        else ++i;
    }
    return false;
}

void task3() {
    std::cout << "Задача 3\n";
    std::vector<std::vector<int>> mat = {
        {1, 4, 7, 11},
        {2, 5, 8, 12},
        {3, 6, 9, 16},
        {10, 13, 14, 17}
    };
    int x = 5;
    bool found = search_sorted_matrix(mat, x);
    std::cout << "Элемент " << x << (found ? " найден" : " не найден") << "\n\n";
}

SeaBattle::SeaBattle() {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j) {
            field[i][j] = 0;
            hits[i][j] = 0;
        }
}

void SeaBattle::generate() {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            field[i][j] = 0;

    std::vector<std::pair<int, int>> ships = { {4,1}, {3,2}, {2,3}, {1,4} };
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dir_dist(0, 1);
    std::uniform_int_distribution<> pos_dist(0, SIZE - 1);

    for (auto& ship : ships) {
        int length = ship.first;
        int count = ship.second;
        for (int k = 0; k < count; ++k) {
            bool placed = false;
            while (!placed) {
                int dir = dir_dist(gen);
                int row, col;
                if (dir == 0) {
                    row = pos_dist(gen);
                    col = pos_dist(gen) % (SIZE - length + 1);
                }
                else {
                    row = pos_dist(gen) % (SIZE - length + 1);
                    col = pos_dist(gen);
                }
                bool ok = true;
                for (int i = 0; i < length; ++i) {
                    int r = (dir == 0) ? row : row + i;
                    int c = (dir == 0) ? col + i : col;
                    if (r < 0 || r >= SIZE || c < 0 || c >= SIZE || field[r][c] != 0) {
                        ok = false;
                        break;
                    }
                    for (int dr = -1; dr <= 1; ++dr) {
                        for (int dc = -1; dc <= 1; ++dc) {
                            if (dr == 0 && dc == 0) continue;
                            int nr = r + dr, nc = c + dc;
                            if (nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE && field[nr][nc] != 0) {
                                ok = false;
                                break;
                            }
                        }
                        if (!ok) break;
                    }
                    if (!ok) break;
                }
                if (ok) {
                    for (int i = 0; i < length; ++i) {
                        int r = (dir == 0) ? row : row + i;
                        int c = (dir == 0) ? col + i : col;
                        field[r][c] = 1;
                    }
                    placed = true;
                }
            }
        }
    }
}

void SeaBattle::saveToFile(const std::string& filename) {
    std::ofstream out(filename);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            out << field[i][j] << (j == SIZE - 1 ? "" : " ");
        }
        out << "\n";
    }
    out.close();
}

bool SeaBattle::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) return false;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            in >> field[i][j];
            if (field[i][j] != 0 && field[i][j] != 1) return false;
        }
    }
    in.close();
    return true;
}

bool SeaBattle::isValidStandard() {
    bool visited[SIZE][SIZE] = { false };
    std::vector<int> shipLengths;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (field[i][j] == 1 && !visited[i][j]) {
                int length = 1;
                bool horiz = false, vert = false;
                if (j + 1 < SIZE && field[i][j + 1] == 1) horiz = true;
                if (i + 1 < SIZE && field[i + 1][j] == 1) vert = true;
                if (horiz && vert) return false;
                if (!horiz && !vert) {
                    shipLengths.push_back(1);
                    visited[i][j] = true;
                    continue;
                }
                if (horiz) {
                    while (j + length < SIZE && field[i][j + length] == 1) ++length;
                    for (int k = 0; k < length; ++k) visited[i][j + k] = true;
                }
                else {
                    while (i + length < SIZE && field[i + length][j] == 1) ++length;
                    for (int k = 0; k < length; ++k) visited[i + k][j] = true;
                }
                shipLengths.push_back(length);
            }
        }
    }
    int count4 = static_cast<int>(std::count(shipLengths.begin(), shipLengths.end(), 4));
    int count3 = static_cast<int>(std::count(shipLengths.begin(), shipLengths.end(), 3));
    int count2 = static_cast<int>(std::count(shipLengths.begin(), shipLengths.end(), 2));
    int count1 = static_cast<int>(std::count(shipLengths.begin(), shipLengths.end(), 1));
    if (count4 != 1 || count3 != 2 || count2 != 3 || count1 != 4) return false;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (field[i][j] == 1) {
                for (int di = -1; di <= 1; ++di) {
                    for (int dj = -1; dj <= 1; ++dj) {
                        if (di == 0 && dj == 0) continue;
                        int ni = i + di, nj = j + dj;
                        if (ni >= 0 && ni < SIZE && nj >= 0 && nj < SIZE && field[ni][nj] == 1) {
                            if (di != 0 && dj != 0) return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

void SeaBattle::shoot(int row, int col) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
        std::cout << "Неверные координаты!\n";
        return;
    }
    if (hits[row][col] == 1) {
        std::cout << "Уже стреляли сюда!\n";
        return;
    }
    if (field[row][col] == 0) {
        std::cout << "Промазал!\n";
        hits[row][col] = 1;
        return;
    }
    hits[row][col] = 1;

    int length = 1;
    int r = row, c = col;
    while (c - 1 >= 0 && field[r][c - 1] == 1) { --c; ++length; }
    c = col;
    while (c + 1 < SIZE && field[r][c + 1] == 1) { ++c; ++length; }
    if (length == 1) {
        r = row; c = col;
        while (r - 1 >= 0 && field[r - 1][c] == 1) { --r; ++length; }
        r = row;
        while (r + 1 < SIZE && field[r + 1][c] == 1) { ++r; ++length; }
    }
    std::cout << "Попал! Тип корабля: " << length << "-палубный. ";

    std::vector<std::pair<int, int>> cells;
    int start_i = row, start_j = col;
    while (start_i - 1 >= 0 && field[start_i - 1][start_j] == 1) --start_i;
    while (start_j - 1 >= 0 && field[start_i][start_j - 1] == 1) --start_j;
    int i = start_i, j = start_j;
    bool horiz = false;
    if (j + 1 < SIZE && field[i][j + 1] == 1) horiz = true;
    if (i + 1 < SIZE && field[i + 1][j] == 1) horiz = false;
    if (!horiz && (i + 1 >= SIZE || field[i + 1][j] == 0)) {
        cells.push_back({ i, j });
    }
    else if (horiz) {
        while (j < SIZE && field[i][j] == 1) {
            cells.push_back({ i, j });
            ++j;
        }
    }
    else {
        while (i < SIZE && field[i][j] == 1) {
            cells.push_back({ i, j });
            ++i;
        }
    }
    bool sunk = true;
    for (auto& cell : cells) {
        if (hits[cell.first][cell.second] == 0) {
            sunk = false;
            break;
        }
    }
    if (sunk) std::cout << "Корабль потоплен!\n";
    else std::cout << "Корабль ранен.\n";
}

void SeaBattle::printField() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) std::cout << field[i][j] << " ";
        std::cout << "\n";
    }
}

void task4() {
    std::cout << "Задача 4\n";
    SeaBattle game;
    game.generate();
    game.saveToFile("field.txt");
    std::cout << "Сгенерировано поле и сохранено в field.txt\n";

    SeaBattle game2;
    if (game2.loadFromFile("field.txt")) {
        if (game2.isValidStandard()) std::cout << "Расстановка корректна.\n";
        else std::cout << "Расстановка некорректна.\n";
    }
    else std::cout << "Ошибка загрузки файла.\n";

    std::cout << "\nВариант 1: Игровой процесс\n";
    std::cout << "Введите координаты выстрела (строка и столбец от 0 до 9):\n";
    int r, c;
    std::cin >> r >> c;
    game2.shoot(r, c);
}