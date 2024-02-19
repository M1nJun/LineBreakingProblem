#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

vector<string> words;
vector<int> wordLengths;
vector<vector<int> > linePenalties;
vector<int> minPenalties;
vector<int> optNumWords;

#define INF 1000000000;

//need to make a function that fills in the table

int fillTable(){
    minPenalties[words.size() - 1] = 0; // base case 342

    // indexes for looping over minpenalties backwards
    for(int n = linePenalties.size() - 2; n >= 0; n--){
        // n = 328
        int currPenalty;
        int best = INF;
        for (int k = 0; k < linePenalties[n].size(); k++){
            // need to change this line
            currPenalty = linePenalties[n][k] + linePenalties[n][k+1];
            if(currPenalty < best)
                best = currPenalty;
        }
    minPenalties[n] = best;
    }
}
//and just access the table for answers 
//the function will have similar logic as the recursive
//fill in the base case looping from the back of the words list. bc the ones with 0 pentalties could be filled in first

int minPenalty(int n){
    // compute the lowest possible total penalty you can achieve when laying out words n..N
    // where N is the total number of words in your text

    //loop over all of the possible configurations for the very first sentence

    if(n >= words.size())
        return 0;
    
    if (minPenalties[n] >= 0){
        return minPenalties[n];
    }

    int currPenalty;
    int best = INF;
    for (int k = 0; k < linePenalties[n].size(); k++){

        currPenalty = linePenalties[n][k] + minPenalty(n+k+1);
        if(currPenalty < best)
            best = currPenalty;
    }
    minPenalties[n] = best;
    return best;
    //first rest
    //fill in the first sentence and the next one as best as u could
    //pass the next word available after the first sentence to minPenalty()
}

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
    for(int n = 0; n < words.size(); n++)
        linePenalties[n] = vector<int>();

    // just in case: auto itr = words.begin(); itr != words.end(); ++itr
    for (int n = 0; n < words.size(); n++) {
        // *itr is the word we grabbed
        int k = 0;
        int occupied = 0; // this is the total number of space occupied by words
        int penalty = 0;
        int spaces = 0;
            // while still have space to use
            while ((!(occupied + wordLengths[n+k] + k + 1> maxLineWidth)) && (n + k < words.size())) {
                // making sure that there's no penalty after the last word being used in the last line.
                if (words[n+k] == words[words.size() - 1]){
                    penalty = 0;
                }
                else {
                    occupied += wordLengths[n+k];
                    // I will have k+1 words that I have grabbed from the list.
                    // And I will have one less space than the number of words I have grabbed.
                    // That's just k. I have k blank spaces in between the words.
                    spaces = maxLineWidth - occupied - k;
                    penalty = spaces * spaces * spaces;
                }
                linePenalties[n].push_back(penalty);
                k++;
            }
    }

//     for (auto itr = linePenalties.begin(); itr != linePenalties.end(); ++itr) {
//         for (auto itr2 = itr->begin(); itr2 != itr->end(); ++itr2){
//                 cout << *itr2 << endl;
//         }
//     }

    
    // minPenalties.resize(words.size());
    for(int n = 0; n < words.size(); n++) {
        minPenalties.push_back(-1);
    }

    for(int n = 0; n < words.size(); n++) {
        optNumWords.push_back(-1);
    }

    cout << "this is the minimum penalty you can acheive: " << endl;
    cout << minPenalty(0) << endl;


    return 0;
}
