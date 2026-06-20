#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>

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
    auto start = chrono::high_resolution_clock::now();

    for (long long target : targets)
    {
        searchRecord(table, target);
    }

    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;
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
    int tableSize = n * 2 + 1; //using prime number greater than 2n for better distribution

    vector<Record> hashTable(tableSize);

    for (auto item : data)
    {
        insertRecord(hashTable, item.first, item.second);
    }

    vector<long long> bestTargets;
    vector<long long> averageTargets;
    vector<long long> worstTargets;

    //Best case: repeatedly search first few existing keys
    for (int i = 0; i < n; i++)
    {
        bestTargets.push_back(data[0].first);
    }

    //Average case: seaarch all existing keys
    for (int i = 0; i < n; i++)
    {
        averageTargets.push_back(data[i].first);
    }

    //Worst case: search keys that doesn't exist
    for (int i = 0; i < n; i++)
    {
        worstTargets.push_back(9999999999LL - i);
    }

    double bestTime = measureSearchTime(hashTable, bestTargets);
    double averageTime = measureSearchTime(hashTable, averageTargets);
    double worstTime = measureSearchTime(hashTable, worstTargets);

    string outputFile = "hash_table_search_dataset_" + to_string(n) + ".txt";
    ofstream out(outputFile);

    out << "Dataset size: " << n << endl;
    out << "Best case time: " << bestTime << " seconds" << endl;
    out << "Average case time: " << averageTime << " seconds" << endl;
    out << "Worst case time: " << worstTime << " seconds" << endl;

    out.close();

    cout << "\nHash Table Search Runtime Result" << endl;
    cout << "Dataset size: " << n << endl;
    cout << "Best case time: " << bestTime << " seconds" << endl;
    cout << "Average case time: " << averageTime << " seconds" << endl;
    cout << "Worst case time: " << worstTime << " seconds" << endl;
    cout << "\nOutput saved to " << outputFile << endl;

    return 0;
}