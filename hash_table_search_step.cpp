// *********************************************************
// Program: hash_table_search_step.cpp
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
// Member_1:
// Member_2: Hash table search & Hash table search step
// Member_3:
// Member_4:
// *********************************************************

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
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

int hashFunction(long long key, int tableSize) 
{
    return key % tableSize;
}

void insertRecord(vector<Record>& table, long long key, string value)
{
    int tableSize = table.size();
    int index = hashFunction(key, tableSize);

    while (table[index].occupied)
    {
        index = (index + 1) % tableSize; // linear probing
    }

    table[index].key = key;
    table[index].value = value;
    table[index].occupied = true;
}

void searchStep(vector<Record>& table, long long target)
{
    int tableSize = table.size();
    int index = hashFunction(target, tableSize);
    int startIndex = index; // to detect if already looped through the entire table

    string filename = "hash_table_search_step_" + to_string(target) + ".txt";
    ofstream out(filename);

    out << "Target: " << target << endl;
    out << "Hash index: " << index << endl;
    out << "Search path: " << endl;

    while (table[index].occupied)
    {
        out << "Index " << index << ": ";

        if (table[index].key == target)
        {
            out << table[index].key << " = " << table[index].key << "/" << table[index].value << endl;
            cout << "Target found. Output saved to " << filename << endl;
            
            out.close();
            return;
        }
        else
        {
            out << table[index].key << " != " << target << endl;
        }

        index = (index + 1) % tableSize; // linear probing

        if (index == startIndex)
        {
            break; // already looped through the entire table
        }
    }

    out << "-1 != " << target << endl;
    out << "Target not found." << endl;

    cout << "Target not found. Output saved to " << filename << endl;
    out.close();
}

int main()
{
    string datasetFile;
    long long target;

    cout << "Enter dataset filename: ";
    cin >> datasetFile;

    ifstream file(datasetFile);

    if (!file)
    {
        cout << "Error: Dataset file cannot be opened or not found." << endl; //dataset file not in same folder/not created yet
        return 1;
    }

    vector<pair<long long, string>> data;
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string keyStr, value;

        getline(ss, keyStr, ',');
        getline(ss, value);

        long long key = stoll(keyStr);
        data.push_back({key, value});
    }

    file.close();

    int tableSize = data.size() * 2 + 1;
    vector<Record> hashTable(tableSize);

    for (auto& item : data)
    {
        insertRecord(hashTable, item.first, item.second);
    }

    cout << "Dataset loaded successfully." << endl;
    cout << "Total records: " << data.size() << endl;
    cout << "Hash table size: " << tableSize << endl;

    cout << "Enter target integer: ";
    cin >> target;

    searchStep(hashTable, target);
    return 0;
}