// *********************************************************
// Program: radix_sort.cpp
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
#include <sstream> // split csv line
#include <vector>
#include <string>
#include <chrono> // measure the running time
#include <iomanip>
using namespace std;

struct Record
{
    long long number;
    string word;
};

// get largest number
long long getMax(vector<Record>& data)
{
    long long maxNum = data[0].number; // assume first number is biggest

    // check every record starting from second item
    for (int i = 1; i < data.size(); i++)
    {
        // if current number is bigger
        if (data[i].number > maxNum)
        {
            // update biggest number
            maxNum = data[i].number;
        }
    }
    return maxNum;
}

// counting sort for each digit
void countingSort(vector<Record>& data, long long digit)
{
    // get number of records
    int size = data.size();

    // temporary array to store sorted result
    vector<Record> output(size);

    // stores frequency of digits 0-9
    int count[10] = {0};

    // count how many times each digit appears
    for (int i = 0; i < size; i++)
    {
        int value = (data[i].number / digit) % 10;
        count[value]++;
    }

    // convert count into actual positions
    for (int i = 1; i < 10; i++)
    {
        count[i] = count[i] + count[i - 1];
    }

    // loop backwards to keep stable sorting
    for (int i = size - 1; i >= 0; i--)
    {
        int value = (data[i].number / digit) % 10;

        // put record into output array
        output[count[value] - 1] = data[i];
        count[value]--;
    }

    // copy sorted result back to original vector
    data = output;
}

void radixSort(vector<Record>& data)
{
    long long maxNum = getMax(data);

    // repeat sorting from rightmost digit to leftmost digit
    for (long long digit = 1; maxNum / digit > 0; digit *= 10) // keep looping until maxNum / digit becomes 0
    {
        // sort current digit
        countingSort(data, digit);
    }
}

int main()
{
    // store input filename
    string filename;

    cout << "Enter dataset filename: " << endl;
    cin >> filename;

    ifstream input(filename); // open file

    if (!input)
    {
        cout << "File cannot be opened" << endl;
        return 0;
    }

    // storing all CSV records
    vector<Record> data;
    string line;

    // read CSV line by line
    while (getline(input, line))
    {
        // put line into stringstream
        stringstream ss(line);

        string num;
        string word;

        getline(ss, num, ','); // read value before comma
        getline(ss, word);     // read value after comma

        // convert number string to long long, then store number + word
        data.push_back({stoll(num), word});
    }

    input.close();

    // start measuring sorting time
    auto start = chrono::high_resolution_clock::now();
    // run radix sort
    radixSort(data);

    // stop measuring time
    auto end = chrono::high_resolution_clock::now();

    // calculate total runtime
    chrono::duration<double> time = end - start;

    string datasetName =  filename.substr(0, filename.size()-4);
    string outputName = datasetName + "_radix_sorted_" + filename;
    ofstream output(outputName);

    // write sorted records into file
    for (Record r : data)
    {
        output << r.number << "," << r.word << endl;
    }

    // write running time in file
    output << endl
           << "Running time: " << time.count() << "seconds.";

    output.close();

    // display completion message
    cout << "Radix sort completed" << endl;
    cout << fixed << setprecision(6) << "Running time: " << time.count() << "seconds." << endl;
    cout << "Output file:" << outputName << endl;

    return 0;
}
