// This program reads data from a file into an array.

#include <iostream>
#include <fstream> // To use ifstream
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <ios>
#include <set>
#include <algorithm>
// dev imports
#include <typeinfo>

#include <sstream>

using namespace std;

std::string cleanWords[36000];

// Function to convert a `std::map<K, V>` to `std::multimap<V, K>`
template <typename K, typename V>
void invertMap(std::map<K, V> const &map)
{
    // Here if greater<int> is used to make
    // sure that elements are stored in
    // descending order of keys.
    multimap<int, string, greater<int>> gramMultiMap;

    // Insert the pair values
    for (auto const &pair : map)
    {
        gramMultiMap.insert(std::make_pair(pair.second, pair.first));
    }

    // Create and open a text file  and log 1gm txt
    multimap<int, string>::iterator it;
    for (it = gramMultiMap.begin(); it != gramMultiMap.end(); it++)
    {
        std::ofstream onegmLogFile("1gm.txt", std::ios_base::app | std::ios_base::out);

        onegmLogFile << (*it).second << "---->" << (*it).first << endl;
    }
}

void sortUnigms(std::map<string, int> unigramMap)
{

    // invert the map , sort and store it in txt
    invertMap(unigramMap);
}
void sortBigms(std::map<string, int> bigramMap)
{
    std::ofstream twogmLogFile("2gm.txt", std::ios_base::app | std::ios_base::out);

    map<string, int>::iterator it;
    for (it = bigramMap.begin(); it != bigramMap.end(); it++)
    {
        twogmLogFile << it->first << "---->" << it->second << endl;
    }
}

// print Map for debugging purpose only

template <typename K, typename V>
void print_map(std::map<K, V> const &m)
{
    for (auto it = m.cbegin(); it != m.cend(); ++it)
    {
        std::cout << "{" << (*it).first << ": " << (*it).second << "}\n";
    }
}
//Save the UNI and BI Grams in their logs
void saveGrams()
{
    std::map<string, int> unigramMap;
    std::map<string, int> bigramMap;

    for (int i = 0; i < 36; i++)
    {
        if (cleanWords[i] == " ")
        {
            continue;
        }

        if (unigramMap.find(cleanWords[i]) == unigramMap.end())
        {                                  // Then we've encountered the word for a first time.
            unigramMap[cleanWords[i]] = 1; // Initialize it to 1.
        }
        else
        {                                // Then we've already seen it before..
            unigramMap[cleanWords[i]]++; // Just increment it
        }
    }

    // print for debugging purpose only
    //print_map(unigramMap);

    // sort the grams before saving
    sortUnigms(unigramMap);

    for (int i = 0; i < 36; i++)
    {

        if (bigramMap.find(cleanWords[i] + "_" + cleanWords[i + 1]) == bigramMap.end())
        {                                                           // Then we've encountered the word for a first time.
            bigramMap[cleanWords[i] + "_" + cleanWords[i + 1]] = 1; // Initialize it to 1.
        }
        else
        {                                                         // Then we've already seen it before..
            bigramMap[cleanWords[i] + "_" + cleanWords[i + 1]]++; // Just increment it
        }
    }

    // print for debugging purpose only
    // print_map(bigramMap);

    // sort the grams before saving
    sortBigms(bigramMap);
}

// search unigram
void searchUnigram()
{
    struct Unigram
    {
        string word;
        int frequency;
    };

    string fileName = "1gm.txt";
    string word;
    std::vector<string> words;
    struct Unigram list[36000];

    cout << "Enter Word to Search";
    cin >> word;
    // read all data from 1gm.txt and copy it into an array of words

    ifstream inputFile(fileName); // Input file stream object  //any other article is possible "sample.txt"

    // Check if exists and then open the file.
    if (inputFile.good())
    {
        // Push items into a vector
        string item;
        while (inputFile >> item)
        {
            words.push_back(item);
        }

        // Close the file.
        inputFile.close();

        for (int i = 0; i < words.size(); i++)
        {

            std::string delimiter = "---->";

            size_t pos = 0;
            Unigram unigram;
            while ((pos = words[i].find(delimiter)) != std::string::npos)
            {
                unigram.word = words[i].substr(0, pos);

                words[i].erase(0, pos + delimiter.length());
            }
            // unigram.frequency =  words[i];s
            stringstream frequency(words[i]);
            frequency >> unigram.frequency;

            list[i].word = unigram.word;
            list[i].frequency = unigram.frequency;
        }

        cout << "Searching for =>" << word << endl;
        // search for the word
        for (int i = 0; i < 36000; i++)
        {
            if (list[i].word == word)
            {
                cout << "Unigram found at index  " << i << " with frequency of" << list[i].frequency;
            }
        }
    }
    else
    {
        cout << "Error! Please run the save command";
        _exit(0);
    }
}

// search Bigram
void searchBigram()
{
    struct Bigram
    {
        string word;
        int frequency;
    };

    string fileName = "2gm.txt";
    string word1;
    string word2;
    std::vector<string> words;
    struct Bigram list[36000];

    cout << "Enter Word1 to Search";
    cin >> word1;
    cout << "Enter Word2 to Search";
    cin >> word2;
    // read all data from 1gm.txt and copy it into an array of words

    ifstream inputFile(fileName); // Input file stream object  //gutenberg-the-time-machine "sample.txt"

    // Check if exists and then open the file.
    if (inputFile.good())
    {
        // Push items into a vector
        string item;
        while (inputFile >> item)
        {
            words.push_back(item);
        }

        // Close the file.
        inputFile.close();

        for (int i = 0; i < words.size(); i++)
        {

            std::string delimiter = "---->";

            size_t pos = 0;
            Bigram bigram;
            while ((pos = words[i].find(delimiter)) != std::string::npos)
            {
                bigram.word = words[i].substr(0, pos);

                words[i].erase(0, pos + delimiter.length());
            }

            stringstream frequency(words[i]);
            frequency >> bigram.frequency;

            list[i].word = bigram.word;
            list[i].frequency = bigram.frequency;
        }

        string searchString = word1 + " " + word2;
        string matchString = word1 + "_" + word2;

        cout << "Searching for =>" << searchString << endl;
        // search for the word
        for (int i = 0; i < 36000; i++)
        {
            if (list[i].word == matchString)
            {
                cout << "bigram found at index  " << i << " with frequency of" << list[i].frequency;
            }
        }
    }
    else
    {
        cout << "Error! Please run the save command";
        _exit(0);
    }
}
// fetch the index number and frequency based on user input
int fetchByIndex()
{
    struct Bigram
    {
        string word;
        int frequency;
    };

    string fileName;
    int index;
    string gramType;
    std::vector<string> words;
    struct Bigram list[36000];

    cout << "Enter Index";
    cin >> index;
    cout << "Unigram or Bigram";
    cin >> gramType;
    // read all data from 1gm.txt or 2gm.txt based on the selection
    if (gramType == "Unigram")
    {
        fileName = "1gm.txt";
    }
    else if (gramType == "Bigram")
    {
        fileName = "2gm.txt";
    }
    else
    {
        cout << "Please enter the gram type properly";
        return 0;
    }

    ifstream inputFile(fileName); // Input file stream object  //gutenberg-the-time-machine "sample.txt"

    // Check if exists and then open the file.
    if (inputFile.good())
    {
        // Push items into a vector
        string item;
        while (inputFile >> item)
        {
            words.push_back(item);
        }

        // Close the file.
        inputFile.close();

        for (int i = 0; i < words.size(); i++)
        {

            std::string delimiter = "---->";

            size_t pos = 0;
            Bigram bigram;
            while ((pos = words[i].find(delimiter)) != std::string::npos)
            {
                bigram.word = words[i].substr(0, pos);

                words[i].erase(0, pos + delimiter.length());
            }

            stringstream frequency(words[i]);
            frequency >> bigram.frequency;

            list[i].word = bigram.word;
            list[i].frequency = bigram.frequency;
        }

        cout << "Index  " << index << ":  ' " << list[index].word << "' with a frequency of " << list[index].frequency;
    }
    else
    {
        cout << "Error! Please run the save command";
        _exit(0);
    }
}

// Quit out of the program
int quitProgram()
{
    cout << "Goodbye!";
    _exit(0);
    ;
}
// Display Commands
void displayCommands()
{
    string command;
    cout << "Commands \n"
         << "Unigram: search for unigram \n"
         << "Bigram : search for bigram \n"
         << "Save :: save 1gms.txt and 2gms.txt \n"
         << "Index :: print index of unigram or bigram \n"
         << "Quit/q ::  terminate program \n";
    cin >> command;

    // switch commands to respective functions
    if (command == "Unigram")
    {
        searchUnigram();
    }
    else if (command == "b")
    {
        searchBigram();
    }
    else if (command == "Save" || command == "s")
    {
        saveGrams();
    }
    else if (command == "Index")
    {
        fetchByIndex();
    }
    else if (command == "Quit" || command == "q")
    {
        quitProgram();
    }
    else
    {
        cout << "Invalid entry. Please try another command!";
    }
}
// get the longest word in the file
int getlongestword(std::vector<string> words, int wordCount)
{
    int i, maxLengthWord = 0, longestWordIndex = -1;
    //count characters of a string wit out space
    for (i = 0; i < wordCount; i++)
    {
        // this condition is used to avoid counting numbers & special chars as words
        if (words[i].at(0) < 'A' || words[i].at(0) > 'Z' && words[i].at(0) < 'a' || words[i].at(0) > 'z')
        {
            continue;
        }
        if (words[i].size() > maxLengthWord)
        {
            maxLengthWord = words[i].size();
            longestWordIndex = i;
        }
    }
    return longestWordIndex;
}
// write to Log file ast1log.txt
void writeToLogFile(string log)
{
    // Create and open a text file  and log
    std::ofstream logFile("ast1log.txt", std::ios_base::app | std::ios_base::out);
    logFile << log + "\n";
}
void replaceNumberWithValue(string s, int index)
{
    string original = s;

    // store the new values to the array
    cleanWords[index] = "NONALPHA";
    //  cleanWords.insert(cleanWords.begin()+(index-1), "NONALPHA");

    string log = s + " =>" + "NONALPHA";

    writeToLogFile(log);
}
void removeSpecialCharacter(string s, int index)
{
    string original = s;
    int i, j;

    for (i = 0; s[i] != '\0'; ++i)
    {
        while (!(s[i] >= 'a' && s[i] <= 'z') && !(s[i] >= 'A' && s[i] <= 'Z') && !(s[i] >= '0' && s[i] <= '9') && !(s[i] == '\0'))
        {
            for (j = i; s[j] != '\0'; ++j)
            {
                s[j] = s[j + 1];
            }
            s[j] = '\0';
        }
    }
    // Transform to lower case
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });

    //    cleanWords.insert(cleanWords.begin()+(index-1), s);
    cleanWords[index] = s;

    string log = original + " =>" + s;

    writeToLogFile(log);
}

// Clean up the read data
void cleanup(std::vector<string> words, int wordCount)
{
    bool foundNumberOnly = false;

    for (int i = 0; i < wordCount; i++)
    {

        if ((words[i].find_first_not_of("0123456789") == string::npos))
        {

            foundNumberOnly = true;
        }
        else
        {

            foundNumberOnly = false;
        }

        // check if only number or special character with other string was found
        // number only found
        if (foundNumberOnly)
        {
            replaceNumberWithValue(words[i], i);
            foundNumberOnly = false;
        }
        else
        {
            removeSpecialCharacter(words[i], i);
            foundNumberOnly = false;
        }
    }
}

int readdata(string fileName)
{
    //declarations
    std::vector<string> words;
    string logValue;
    bool isLoggingOn;
    // Display the array size read and Opened file name

    cout << "Array Size: " << words.size() << "   Dynamic Vector"
         << "\n";
    cout << "Opening File:" << fileName << "\n";

    ifstream inputFile(fileName); // Input file stream object  //gutenberg-the-time-machine "sample.txt"

    // Check if exists and then open the file.
    if (inputFile.good())
    {
        // Push items into a vector
        string item;
        while (inputFile >> item)
        {
            words.push_back(item);
        }

        // Close the file.
        inputFile.close();

        // display finished reading file
        cout << "Finished Reading " << words.size() << "Words. Closing File \n";

        // Log Cleanup condition
        cout << "Log Cleanup? Y/N";
        cin >> logValue;
        cout << "\n Writing log to ast1log.txt \n";

        if (logValue.at(0) == 'Y' || logValue.at(0) == 'y')
        {

            isLoggingOn = true;
        }
        else
        {
            cout << "Not Logging Cleanup.";
            isLoggingOn = false;
        }

        // if there is logging
        if (isLoggingOn)
        {
            // get the longest Word
            int longestWordIndex = getlongestword(words, words.size());
            cout << "Longest Word:" << words[longestWordIndex] << endl;

            // clean up the document
            cleanup(words, words.size());

            //Display command List
            displayCommands();

            cout << endl;
        }
        else
        {
            // not logging just give the results
            cout << "Not Logging ....";
        }
    }
    else
    {
        cout << "Error!";
        _exit(0);
    }

    return 0;
}

int main(int argc, char **argv)
{
    cout << "*************************************** Unigram Bigram Extractor ************************** \n";

    string fileName = argv[1];
    readdata(fileName);
    displayCommands();
}
