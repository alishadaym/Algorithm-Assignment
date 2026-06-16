#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

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
void writeCSV(string filename, vector<Record> data)
{
    ofstream file(filename);

    if (!file)
    {
        cout << "Error creating file." << endl;
        return;
    }

    for (int i = 0; i < data.size(); i++)
    {
        file << data[i].number << "," << data[i].word;

        if (i != data.size() - 1)
        {
            file << endl;
        }
    }
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

    if (data.size() == 0)
    {
        cout << "Dataset is empty or cannot be read." << endl;
        return 0;
    }

    cout << "Total records loaded: " << data.size() << endl;

    heapSort(data);

    string outputFile = "heap_sorted_" + inputFile;

    writeCSV(outputFile, data);

    cout << "Heap sort completed." << endl;
    cout << "Output fileL " << outputFile << endl;

    return 0;
}
