#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
using namespace std;

const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in

void Loop(int init, int max, int i, string a, const string dict[], int size, string results[], int& count);
void Loop2 (string a, const string dict[], int size, string results[], int initial, int& count);
void Loop3 (string a, string results[], int initi, int& count);

int readDict(istream &dictfile, string dict[], int& count)
{
    if (count >= 30000) //if number of words being read in reaches MAXDICTWORDS, stop reading in and return
        return 30000;
    string tmp;
    dictfile >> tmp;
    if (tmp != "") //stop reading in words when it's an empty string
    {
        dict[0] = tmp;
        count++;
        return 1 + readDict(dictfile, dict + 1, count); //return number of words read in
    }
    
    else
        return 0;
}
int readDictionary(istream &dictfile, string dict[])
{
    int count = 0;
    return readDict(dictfile, dict, count);
}

void swap(char& x, char& y) //to swap two characters
{
    char temp;
    temp = x;
    x = y;
    y = temp;
}
void permute(string a, int i, int n, const string dict[], int size, string results[], int& count)
{
    if (i == n) //signals that permutation is complete
    {
        Loop2(a, dict, size, results, 0, count); //function to loop and check against each word in dictionary
    }
    else
    {
        Loop(i, n, i, a, dict, size, results, count); //function to loop and permute words by swapping letters
    }
}

void Loop(int init, int max, int i, string a, const string dict[], int size, string results[], int& count) {
    if (init >= max)
        return;
    swap(a[i], a[init]);
    permute(a, i+1, max, dict, size, results, count);
    swap(a[i], a[init]);
    Loop(init + 1, max, i, a, dict, size, results, count);
}

void Loop2 (string a, const string dict[], int size, string results[], int initial, int& count)
{
    if (initial >= size)
        return;
    if (a == dict[initial])
        Loop3(a, results, 0, count); //function to loop and check against each word in results to store only unique results
    
    Loop2(a, dict, size, results, initial + 1, count);
}

void Loop3 (string a, string results[], int initi, int& count)
{
    if (initi >= MAXRESULTS) //ensures number of strings stored doesn't exceed maxresults
        return;
    if (results[initi] == "") //store string in position where there is an empty string
    {results[initi] = a;
        count++; //increase count when string stored
        return;}
    else if (results[initi] == a) //check for duplicates
        return;
    Loop3(a, results, initi + 1, count);
}

int recursivePermute(string word, const string dict[], int size, string results[])
{
    int count = 0;
    permute(word, 0, word.size(), dict, size, results, count); //permute the word
    return count; //return number of strings stored in results
}

void recurPrint(const string results[], int size)
{
if (size == 0)
    return;
cout << results[0] << endl; //print each result
recurPrint(results + 1, size -1);
}

int main()
{
    string results[MAXRESULTS];
    string dict[MAXDICTWORDS];
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;
    
    dictfile.open("/Users/aashitapatwari/Desktop/words.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }
    
    nwords = readDictionary(dictfile, dict);
    //cout << nwords << endl;
    cout << "Please enter a string for an anagram: ";
    cin >> word;
    
    int numMatches = recursivePermute(word, dict, nwords, results);
    if (!numMatches)
      cout << "No matches found" << endl;
    else
      recurPrint(results, numMatches);
}





