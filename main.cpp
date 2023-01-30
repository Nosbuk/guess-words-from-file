#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

int main()
{
    cout << "Witaj w WordGuess! \n";
    cout << "Wczytywanie słow z pliku words.txt... \n";

    string txt;                 // variable for string formed from file
    ifstream file("words.txt"); // open the words.txt file and save it in file object

    if (file.is_open())         // make sure the words.txt has been opened
        while (file.good())     // until  there are lines
            getline(file, txt); // get each line of the document
    file.close();               // close file -> preserve memory

    cout << "Słowa wczytane z pliku: \n";
    cout << txt;
    cout << "\nNapisz \"play\" aby pomieszać słowa i rozpocząć grę...\n";
    string isGameStarted;
    cin >> isGameStarted;

    while (isGameStarted != "play") // check if player provided correct comand, throw error if not
    {
        cout << "\nNie rozpozonano komendy \"" + isGameStarted + "\"\n Napisz \"play\" aby pomieszać słowa i rozpocząć grę...\n";
        cin >> isGameStarted;
    }
    string delimiter = " ";                                                      // declare delimiter for string spliting
    vector<string> wordsVector;                                                  // vectore to store our randomized strings
    vector<string> randomizedWordsVector;                                        // vectore to store our randomized strings
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // obtain time based seed for random engine

    size_t pos = 0;
    while ((pos = txt.find(delimiter)) != string::npos) // for each word divided by space
    {
        string word = txt.substr(0, pos);
        wordsVector.push_back(word);                                    // push the word into vector                              // assign word to a variable
        shuffle(word.begin(), word.end(), default_random_engine(seed)); // shuffel the word using random engine
        randomizedWordsVector.push_back(word);                          // push the word into vector
        txt.erase(0, pos + delimiter.length());                         // erease pushed word from string
    }

    int points = 0;

    for (size_t i = 0; wordsVector.size() > i; i++)
    {
        string answer;
        cout << "Odgadnij słowo: " + randomizedWordsVector[i] + "\n";
        cout << "Twoja odpowiedź: ";
        cin >> answer;

        if (answer == wordsVector[i])
        {
            cout << "\nGratulacje prawidłowa odpowiedź, +1 punkt\n";
            points++;
            continue;
        }
        cout << "\nOdpowiedź błędna\n";
    }

    cout << "\nDziękujemy za grę!\n";
    cout << "\nUdało cie odpowiedzieć poprawnie na " + to_string(points) + " pytań\n";

    return 0;
}
