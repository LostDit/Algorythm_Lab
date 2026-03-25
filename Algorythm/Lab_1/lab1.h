#ifndef LAB1_H
#define LAB1_H

#include <vector>
#include <string>

struct Comparisons {
    long long total = 0;
    long long element = 0;
};

void task1();
void task2();
void task3();
void task4();

class SeaBattle {
private:
    static const int SIZE = 10;
    int field[10][10];
    int hits[10][10];
public:
    SeaBattle();
    void generate();
    void saveToFile(const std::string& filename);
    bool loadFromFile(const std::string& filename);
    bool isValidStandard();
    void shoot(int row, int col);
    void printField();
};

int linear_search(const std::vector<int>& arr, int key, Comparisons* comp = nullptr);
int linear_search_barrier(const std::vector<int>& arr, int key, Comparisons* comp = nullptr);
int binary_search_iter(const std::vector<int>& arr, int key, Comparisons* comp = nullptr);
int binary_search_rec(const std::vector<int>& arr, int key, Comparisons* comp = nullptr);

std::pair<int, int> linear_search_2d(const std::vector<std::vector<int>>& mat, int key, Comparisons* comp = nullptr);
std::pair<int, int> linear_search_2d_barrier(const std::vector<std::vector<int>>& mat, int key, Comparisons* comp = nullptr);
bool search_sorted_matrix(const std::vector<std::vector<int>>& mat, int x);

#endif