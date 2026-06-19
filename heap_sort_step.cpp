// *********************************************************
// Program: heap_sort_step.cpp
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

using namespace std;

struct Record
{
    long long number;
    string word;
};

//print array
void printArray(vector<Record>& arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i].number << " ";
    }
    cout << endl;
}

//read csv file
vector<Record> readCSV(string filename)
{
    vector<Record> data;
    ifstream file(filename);

    if (! file)
    {
        cout << "Error opening file." << endl;
        return data;
    }

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string num, word;
        getline(ss, num, ',');
        getline(ss, word);

        Record temp;
        temp.number = stoll(num);
        temp.word = word;

        data.push_back(temp);
    }

    file.close();
    return data;
}

//heapify with steps
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

        cout << "Heapify swap: ";
        printArray(arr);

        heapify(arr, n, largest);
    }
}

//bulding heap with steps
void buildHeap(vector<Record>& arr)
{
    int n = arr.size();

    cout << "Building max heap.." << endl;

    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    cout << "After buildHeap: ";
    printArray(arr);
}

//heap sort with steps
void heapSort(vector<Record>& arr)
{
    int n = arr.size();

    buildHeap(arr);

    cout << "\nStarting Heap Sort...\n" << endl;

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);

        cout << "After swapping root with index " << i << ": ";
        printArray(arr);

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
        cout << "Dataset empty or cannot be read." << endl;
        return 0;
    }

    cout << "\nOriginal data: ";
    printArray(data);

    heapSort(data);

    cout << "\nFinal Sorted Data: ";
    printArray(data);
    
    return 0;
}