#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

vector<string> words;
vector<int> wordLengths;
vector<vector<int> > linePenalties;

int main(){

    int maxLineWidth;
    cout << "Enter a maximum line width to use when breaking the text into lines: ";
    cin >> maxLineWidth;

    ifstream in;
    in.open("words.txt");

    string word;
    int i = 0;

    while(in>>word){
        words.push_back(word);
        i++;
    }
    in.close();

    // for (auto itr = words.begin(); itr != words.end(); ++itr) {
    //     cout << *itr << endl;
    // }
    for (auto itr = words.begin(); itr != words.end(); ++itr) {
        wordLengths.push_back((*itr).length());
    }

    // for (auto itr = wordLengths.begin(); itr != wordLengths.end(); ++itr) {
    //     cout << *itr << endl;
    // }


    linePenalties.resize(words.size());
    // just in case: auto itr = words.begin(); itr != words.end(); ++itr
    for (int n = 0; n < words.size(); n++) {
        // *itr is the word we grabbed
        int k = 0;
        int occupied = 0; // this is the total number of space occupied by words
        int penalty = 0;
            // while still have space to use
            while (occupied + wordLengths[k+1] > maxLineWidth) {
                occupied += wordLengths[k];
                // I will have k+1 words that I have grabbed from the list.
                // And I will have one less space than the number of words I have grabbed.
                // That's just k. I have k blank spaces in between the words.
                penalty = pow((maxLineWidth - occupied - k), 3);
                linePenalties[n].push_back(penalty);
                k++;
            }
    }

    cout << linePenalties[0][0] << endl;

    for (auto itr = linePenalties.begin(); itr != linePenalties.end(); ++itr) {
        for (auto itr2 = itr->begin(); itr2 != itr->end(); ++itr2){
                cout << *itr2 << endl;
        }
    }

    cout << "checkpoint2" << endl;
    



    return 0;
}