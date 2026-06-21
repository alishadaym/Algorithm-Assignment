// *********************************************************
// Program: hash_table_search.cpp
// Course: CCP6214 Algorithm Design and Analysis
// Lecture Class: TC6L
// Tutorial Class: T21L
// Trimester: 2610
// Member_1: 242UC244RK | ADEENA SHAHIRA BINTI MOHD HAFIZ | adeena.shahira.mohd@student.mmu.edu.my | 0193233705
// Member_2: 242UC244DM | FARAH ALYSSA BINTI SHARANI | farah.alyssa.sharani@student.mmu.edu.my | 0192648995
// Member_3: ID | ILIE ISABELLA BINTI FAIROZ IZNI | ilie.isabella.fairoz@student.mmu.edu.my | 0186656781
// Member_4: 242UC244S4 | NUR ALISHA DAMIA BINTI SHAMSUL ANUAR (leader) | nur.alisha.damia@student.mmu.edu.my | 0166647156
// *********************************************************
// Task Distribution
// Member_1: Dataset Generator, Heap Sort & Heap Sort Step
// Member_2: Hash Table Search & Hash Table Search Step
// Member_3: Radix Sort & Radix Sort Step
// Member_4: Documentation
// *********************************************************

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <iomanip>

using namespace std;

struct Record
{
    long long key;
    string value;
    bool occupied;

    Record()
    {
        key = -1;
        value = "";
        occupied = false;
    }
};

int hashFunction (long long key, int tableSize)
{
    return key % tableSize;
}

void insertRecord (vector<Record>& table, long long key, string value)
{
    int tableSize = table.size();
    int index = hashFunction(key, tableSize);

    while (table[index].occupied)
    {
        index = (index + 1) % tableSize;
    }

    table[index].key = key;
    table[index].value = value;
    table[index].occupied = true;
}

bool searchRecord (vector<Record>& table, long long target)
{
    int tableSize = table.size();
    int index = hashFunction(target, tableSize);
    int startIndex = index;

    while (table[index].occupied)
    {
        if (table[index].key == target)
        {
            return true;
        }

        index = (index + 1) % tableSize;

        if (index == startIndex)
        {
            break; //already looped through the entire table
        }
    }

    return false;
}

double measureSearchTime (vector<Record>& table, vector<long long>& targets)
{
    volatile int foundCount = 0; //prevent compiler optimization for search results
    auto start = chrono::high_resolution_clock::now();

    for (long long target : targets)
    {
        if (searchRecord(table, target));
        {
            foundCount++;
        }
    }

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, micro> elapsed = end - start;
    return elapsed.count();
}

int main()
{
    string datasetFile;

    cout << "Enter dataset filename: ";
    cin >> datasetFile;

    ifstream file(datasetFile);

    if(!file)
    {
        cout << "\nError: Dataset file cannot be opened or found." << endl;
        return 1;
    }

    vector<pair<long long, string>> data;
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string keyText, value;

        getline(ss, keyText, ',');
        getline(ss, value);

        long long key = stoll(keyText);
        data.push_back({key, value});
    }

    file.close();

    int n = data.size();
    int tableSize = n + 1; //table size have at least one empty slot to avoid infinite loop in linear probing

    vector<Record> hashTable(tableSize);

    for (auto item : data)
    {
        insertRecord(hashTable, item.first, item.second);
    }

    vector<long long> bestTargets;
    vector<long long> averageTargets;
    vector<long long> worstTargets;

    //Best case: search first 10% existing keys (should be found immediately/fewer probes)
    int tenPercent = n / 10;
    if (tenPercent < 1) tenPercent = 1; //ensure at least one key is searched in best case
    
    for (int i = 0; i < n; i++)
    {
        bestTargets.push_back(data[i % tenPercent].first);
    }

    //Average case: search all existing keys once (keys should be found after some probing)
    for (int i = 0; i < n; i++)
    {
        averageTargets.push_back(data[i].first);
    }

    //Worst case: search last 10% existing keys (should be found after maximum probing)
    //keys are more likely to have been affected by collisions
    for (int i = 0; i < n; i++)
    {
        int index = n - 1 - (i % tenPercent);
        worstTargets.push_back(data[index].first);
    }

    double bestTime = measureSearchTime(hashTable, bestTargets);
    double averageTime = measureSearchTime(hashTable, averageTargets);
    double worstTime = measureSearchTime(hashTable, worstTargets);

    string outputFile = "hash_table_search_dataset_" + to_string(n) + ".txt";
    ofstream out(outputFile);

    out << fixed << setprecision(3);

    out << "Dataset size: " << n << endl;
    out << "Hash table size: " << tableSize << endl;
    out << endl;
    out << "Best case time: " << bestTime << " microseconds" << endl;
    out << "Average case time: " << averageTime << " microseconds" << endl;
    out << "Worst case time: " << worstTime << " microseconds" << endl;

    out.close();

    cout << fixed << setprecision(3);

    cout << "\nHash Table Search Runtime Result" << endl;
    cout << "Dataset size: " << n << endl;
    cout << "Hash table size: " << tableSize << endl;
    cout << endl;
    cout << "Best case time: " << bestTime << " microseconds" << endl;
    cout << "Average case time: " << averageTime << " microseconds" << endl;
    cout << "Worst case time: " << worstTime << " microseconds" << endl;
    cout << "\nOutput saved to " << outputFile << endl;

    return 0;
}