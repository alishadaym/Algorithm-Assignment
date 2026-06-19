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

//print selected rows to file
void printRange(vector<Record>& arr,
                int startRow,
                int endRow,
                ofstream& outFile)
{
    for (int i = startRow - 1;
        i <= endRow - 1 && i < arr.size();
        i++)
    {
        outFile << i + 1
                << ": "
                << arr[i].number
                << ","
                << arr[i].word
                << endl;
    }

    outFile << endl;
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

        string num;
        string word;

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
void heapify(vector<Record>& arr,
            int n,
            int i,
            ofstream& outFile,
            int startRow,
            int endRow)
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

        outFile << "Heapify Swap" << endl;
        printRange(arr, startRow, endRow, outFile);

        heapify(arr, n, largest, outFile, startRow, endRow);
    }
}

//bulding max heap
void buildHeap(vector<Record>& arr,
                ofstream& outFile,
                int startRow,
                int endRow)
{
    int n = arr.size();

    outFile << "Building Max Heap" << endl;
    outFile << endl;

    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i, outFile, startRow, endRow);
    }

    outFile << "After build Heap" << endl;
    printRange(arr, startRow, endRow, outFile);
}

//heap sort with steps
void heapSort(vector<Record>& arr,
                ofstream& outFile,
                int startRow,
                int endRow)
{
    int n = arr.size();

    buildHeap(arr, outFile, startRow, endRow);

    outFile << "Starting Heap Sort" << endl;
    outFile << endl;

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);

        outFile << "After swapping root with index " << i << endl;
        printRange(arr, startRow, endRow, outFile);

        heapify(arr, i, 0, outFile, startRow, endRow);
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

    int startRow;
    int endRow;

    cout << "Enter start row: ";
    cin >> startRow;

    cout << "Enter end row: ";
    cin >> endRow;

    if (startRow < 1 || endRow > data.size() || startRow > endRow)
    {
        cout << "Invalid row range." << endl;
        return 0;
    }

    string outputFile = "dataset_" + to_string(data.size()) + "_heap_sorted_step_" +
        to_string(startRow) + "_" + to_string(endRow) + ".txt";

    ofstream outFile(outputFile);

    if (!outFile)
    {
        cout << "Cannot create output file." << endl;
        return 0;
    }

    heapSort(data, outFile, startRow, endRow);

    outFile.close();

    cout << endl;
    cout << "Heap sort steps saved to: " << outputFile << endl;
    
    return 0;
}