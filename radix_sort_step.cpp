// *********************************************************
// Program: radix_sort_step.cpp
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

// print current radix sort step into txt file 
void printStep(ofstream& output, vector<Record>& data, string label)
{
    output << label << endl;

    // print every record 
    for(int i=0; i < data.size(); i++)
    {
        output << data[i].number << "/" << data[i].word;

        // add comma except last data 
        if(i != data.size()-1)
        {
            output << ", ";
        }

        output << endl;
    }

    output << endl;
}

// sort according to current digit
void countingSort(vector<Record>& data, long long digit)
{
    // get number of records
    int size = data.size();

    // temporary sorted storage 
    vector<Record> output(size);

    // stores frequency of digits 0-9
    int count[10] = {0}; // creates 10 storage or buckets [] initialized to 0

    // count digits 
    for(int i=0; i < size; i++)
    {
        int value = (data[i].number / digit) % 10;
        count[value]++;
    }

    // convert count into actual positions
    for (int i = 1; i < 10; i++)
    {
         count[i] = count[i] + count[i - 1];
    }

    // place records into correct position
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

int main()
{
    // store input filename
    string filename;

    // selected rows 
    int startRow;
    int endRow;

    cout << "Enter dataset filename: " << endl;
    cin >> filename;

    cout << "Start row: " << endl;
    cin >> startRow;

    cout << "End row: " << endl;
    cin >> endRow;

    // open file
    ifstream input(filename); 

    if (!input)
    {
        cout << "File cannot be opened" << endl;
        return 0;
    }

    // storing all CSV records
    vector<Record> data;
    string line;

    // track current row number 
    int row = 1;

    // read CSV line by line
    while (getline(input, line))
    {
        // only take wanted rows 
        if (row >= startRow && row<= endRow)
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

        row++;
    }

    input.close();

    // create output filename 
    string outputName = filename.substr(0, filename.size()-4) 
                         + "_radix_sorted_step_" 
                         + to_string(startRow)
                         + "_" 
                         + to_string(endRow)
                         + ".txt";

    // create txt output 
    ofstream output(outputName);

    int d = 10; // dataset numbers are fixed as 10-digit integers, d is position

    // process all 10 digits 
    for(long long digit = 1; digit <= 1000000000; digit *= 10)
    {
        // sort current digit 
        countingSort(data, digit);

        printStep(output, data, "d = " + to_string(d));

        d--;
    }

    output.close();

    cout << "Created output file: " << outputName;

    return 0;
}

