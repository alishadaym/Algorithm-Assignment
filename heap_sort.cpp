// *********************************************************
// Program: heap_sort.cpp
// Course: CCP6214 Algorithm Design and Analysis
// Lecture Class: TC6L
// Tutorial Class: T21L
// Trimester: 2610
// Member_1: 242UC244S4 | NUR ALISHA DAMIA BINTI SHAMSUL ANUAR | nur.alisha.damia@student.mmu.edu.my | 0166647156
// Member_2: 242UC244DM | FARAH ALYSSA BINTI SHARANI | farah.alyssa.sharani@student.mmu.edu.my | 0192648995
// Member_3: 242UC244RK | ADEENA SHAHIRA BINTI MOHD HAFIZ | adeena.shahira.mohd@student.mmu.edu.my | 0193233705
// Member_4: 243UC247BP | ILIE ISABELLA BINTI FAIROZ IZNI | ilie.isabella.fairoz@student.mmu.edu.my | 0186656781
// *********************************************************
// Task Distribution
// Member_1: Dataset Generator & Heap Sort
// Member_2: Hash Table Search
// Member_3: Radix Sort
// Member_4: Documentation
// *********************************************************

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

//structure to store each record
struct Record
{
    long long number;
    string word;
};

//to read the .csv file
vector<Record> readCSV(string filename)
{
    vector<Record> data;
    ifstream file(filename);

    if (!file)
    {
        cout << "Error opening file." << endl;
        return data;
    }

    string line;

    while (getline(file,line))
    {
        stringstream ss(line);

        string numberStr;
        string word;

        getline(ss, numberStr, ',');
        getline(ss, word);

        Record temp;
        temp.number = stoll(numberStr);
        temp.word = word;

        data.push_back(temp);
    }

    file.close();
    return data;
}

//write csv file to save result after sorting
void writeCSV(string filename, vector<Record>& data, long long runtime)
{
    ofstream file(filename);

    if (!file)
    {
        cout << "Error creating file." << endl;
        return;
    }

    for (int i = 0; i < data.size(); i++)
    {
        file << data[i].number << "," << data[i].word << endl;
    }

    file << endl;
    file << "Running Time (microseconds): " << runtime << endl;

    file.close();
}

//heapify function
void heapify(vector<Record>& arr, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].number > arr[largest].number)
    {
        largest = left;
    }

    if (right < n && arr[right].number > arr[largest].number)
    {
        largest = right;
    }

    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

//build heap
void buildHeap(vector<Record>& arr)
{
    int n = arr.size();

    for (int i = n/2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }
}

//heap sort
void heapSort(vector<Record>& arr)
{
    int n = arr.size();

    buildHeap(arr);

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main()
{
    string inputFile;

    cout << "Enter dataset filename: ";
    cin >> inputFile;

    vector<Record> data = readCSV(inputFile);

    if (data.empty())
    {
        cout << "Dataset is empty or cannot be read." << endl;
        return 0;
    }

    cout << "Total records loaded: " << data.size() << endl;

    auto start = chrono::high_resolution_clock::now();

    heapSort(data);

    auto end = chrono::high_resolution_clock::now();

    long long runtime = chrono::duration_cast<chrono::microseconds>(end-start).count();

    string outputFile = "heap_sort_dataset_" + to_string(data.size()) + ".csv";

    writeCSV(outputFile, data, runtime);

    cout << endl;
    cout << "Heap sort completed." << endl;
    cout << "Output file: " << outputFile << endl;
    cout << "Running Time: " << runtime << " microseconds" << endl;

    return 0;
}
