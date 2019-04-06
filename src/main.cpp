#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

FILE * openFile(FILE * file);
void readWords(FILE * file);
void randomChacarter(vector<pair<int,char>> word);
void savedWords(vector<pair<int,char>> word);

vector<vector<pair<int, char>>> saved_words;

int main() {
    FILE * file;
  
    file = openFile(file);
    readWords(file);

return 0;
}

FILE * openFile(FILE * file) {
    file = fopen("words.txt", "r"); 
    
    if(file == NULL) {
        cout << "Error opening File, finishing execution..." << endl;
        exit(0);
    }
    else {
        // nothind to do.
    }

    return file;
}

void readWords(FILE * file) {
    vector<pair<int,char>> word;
    char aux; 
    int i = 0;
    
    while(fscanf(file,"%c", &aux) != EOF) {
        if(aux != '\n') {
            word.push_back(make_pair(i,aux));
            i++;
        }
        else {
            randomChacarter(word);
            i = 0;
            word.erase(word.begin(), word.end());
        }
        
    }
    randomChacarter(word);
    fclose(file);

    for(unsigned int i = 0; i < saved_words.size(); i++) {
        for(unsigned int j = 0; j < saved_words[i].size(); j++) {
            cout << saved_words[i][j].first << " : "<< saved_words[i][j].second; 
        }
    }
    
}

void randomChacarter(vector<pair<int,char>> word) {
    random_shuffle(word.begin(), word.end());
    savedWords(word);
}

void savedWords(vector<pair<int,char>> word) {
    saved_words.push_back(word);   
}

