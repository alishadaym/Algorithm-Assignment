#include <iostream>
#include <fstream>
#include <unordered_set>
#include <random>
#include <string>

using namespace std;

int main()
{
    //sid: 242UC244S4 -> seed: 2421324494
    mt19937_64 rng(2421324494ULL);

    int n;

    cout << "Enter dataset size: ";
    cin >> n;

    //check validity
    if (n <= 0)
    {
        cout << "Dataset size must be greater than 0." << endl;
        return 1;
    }

    //generate file output
    string filename = "dataset_" + to_string(n) + ".csv";

    ofstream file(filename);

    if (!file.is_open())
    {
        cout << "Unable to create file." << endl;
        return 1;
    }

    //to store generated numbers
    unordered_set<long long> usedNumbers;

    //random number distribution
    uniform_int_distribution<long long> numberDist(
        1000000000LL,
        9999999999LL
    );

    //random lowercase letters
    uniform_int_distribution<int> letterDist(0, 25);

    int count = 0;

    while (count < n)
    {
        long long number = numberDist(rng);

        //skip duplicates
        if (usedNumbers.find(number) != usedNumbers.end())
        {
            continue;
        }

        usedNumbers.insert(number);

        //to generate 5 letter string
        string word = "";

        for (int i = 0; i < 5; i++)
        {
            char letter = 'a' + letterDist(rng);
            word += letter;
        }

        file << number << "," << word;

        if (count != n - 1)
        {
            file << endl;
        }

        count++;
    }

    file.close();

    cout << endl;
    cout << "Dataset generated successfully." << endl;
    cout << "Filename: " << filename << endl;
    cout << "Seed used: 2421324494" << endl;
    cout << "Total records: " << n << endl;
    return 0;
}