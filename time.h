#pragma once
#include <iostream>
#include "Binary_tree.h"
#include <vector>
#include <chrono>


using namespace std;

size_t lcg() {
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

float create_time(int num_nodes)
{
    chrono::duration<float> result(0), one_res(0);
    float res = 0;

    for (int i = 0; i < 100; i += 1)
    {
        auto start = chrono::high_resolution_clock::now();
        b_tree tmp;
        for (int j = 0; j < num_nodes; j++)
            tmp.insert(int(lcg()));
        auto end = chrono::high_resolution_clock::now();
        result += end - start;
    }
    result /= 100;
    cout<< endl << "На создание дерева из " << num_nodes << "элементов ушло:: " << result.count() << endl;
    return result.count();
}

float find_time(int num_nodes)
{
    b_tree tmp;
    auto start = chrono::high_resolution_clock::now();
    chrono::duration<float> result(0);

    for (int j = 0; j < num_nodes; j++)
        tmp.insert(int(lcg()));
    for (int i = 0; i < 1000; i += 1)
    {
        auto start = chrono::high_resolution_clock::now();
        tmp.contains(int(lcg()));
        auto end = chrono::high_resolution_clock::now();
        result += end - start;
    }
    result /= 1000;
    cout << endl << "На поиск случайного элемента в дереве из  " << num_nodes << "элементов ушло: " << result.count() << endl;
    return result.count();
}

float insert_time(int num_nodes)
{
    b_tree tmp;
    chrono::duration<float> result(0);

    for (int j = 0; j < num_nodes; j++)
        tmp.insert(int(lcg()));

    for (int i = 0; i < 1000; i += 1)
    {
        auto start = chrono::high_resolution_clock::now();
        tmp.insert(int(lcg()));
        auto end = chrono::high_resolution_clock::now();
        result += end - start;

    }
    result /= 1000;
    cout << endl << "На добавление случайного элемента в дерево из " << num_nodes << "элементов ушло: " << result.count() << endl;
    return result.count();
}

float erase_time(int num_nodes)
{
    b_tree tmp;
    chrono::duration<float> result(0);

    for (int j = 0; j < num_nodes; j++)
        tmp.insert(int(lcg()));

    for (int i = 0; i < 1000; i += 1)
    {
        auto start = chrono::high_resolution_clock::now();
        tmp.erase(int(lcg()));
        auto end = chrono::high_resolution_clock::now();
        result += end - start;

    }
    result /= 1000;
    cout << endl << "На удаление случайного элемента в дереве из " << num_nodes << "элементов ушло: " << result.count() << endl;
    return result.count();
}

//for class-container
float create_time_vector(int num_nodes)
{
    chrono::duration<float> result(0);

    for (int i = 0; i < 100; i += 1)
    {
        vector<int> tmp_vector;
        auto start = chrono::high_resolution_clock::now();
        for (int j = 0; j < num_nodes; j++)
            tmp_vector.push_back(int(lcg()));
        auto end = chrono::high_resolution_clock::now();
        result += end - start;
    }
    result /= 100;
    cout << endl << "На создание дерева из " << num_nodes << "элементов ушло: " << result.count() << endl;
    return result.count();
}

float find_time_vector(int num_nodes)
{
    vector<int> tmp_vector(num_nodes);
    chrono::duration<float> result(0);

    for (int j = 0; j < num_nodes; j++)
        tmp_vector.push_back(int(lcg()));

    for (int i = 0; i < 1000; i += 1)
    {
        auto start = chrono::high_resolution_clock::now();
        find(tmp_vector.begin(), tmp_vector.end(), int(lcg()));
        auto end = chrono::high_resolution_clock::now();
        result += end - start;

    }
    result /= 1000;
    cout << endl << "На поиск случайного элемента в векторе из " << num_nodes << "элементов ушло: " << result.count() << endl;
    return result.count();
}

float insert_time_vector(int num_nodes)
{
    vector<int> tmp_vector(num_nodes);
    chrono::duration<float> result(0);

    for (int j = 0; j < num_nodes; j++)
        tmp_vector.push_back(int(lcg()));

    for (int i = 0; i < 1000; i += 1)
    {
        auto start = chrono::high_resolution_clock::now();
        tmp_vector.push_back(int(lcg()));
        auto end = chrono::high_resolution_clock::now();
        result += end - start;
    }
    result /= 1000;
    cout << endl << "На вставку случайного элемента в вектор из " << num_nodes << "элементов ушло: " << result.count() << endl;
    return result.count();
}

float erase_time_vector(int num_nodes)
{
    vector<int> tmp_vector(num_nodes);
    chrono::duration<float> result(0);

    for (int j = 0; j < num_nodes; j++)
        tmp_vector.push_back(int(lcg()));

    for (int i = 0; i < 1000; i += 1)
    {
        auto start = chrono::high_resolution_clock::now();
        for (auto it = tmp_vector.begin(); it != tmp_vector.end(); )
        {
            if (*it == int(lcg()))
            {
                it = tmp_vector.erase(it);
                break;
            }
            else
                ++it;
        }
        auto end = chrono::high_resolution_clock::now();
        result += end - start;
    }
    result /= 1000;
    cout << endl << "На удаление случайного элемента в векторе из " << num_nodes << "элементов ушло: " << result.count() << endl;
    return result.count();
}