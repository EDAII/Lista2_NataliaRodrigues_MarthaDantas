#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

FILE * openFile(FILE * file);
void readWords(FILE * file, vector<pair<int,char>> word);
void randomChacarter(vector<pair<int,char>> word);

int main() {
    vector<pair<int,char>> word;
    FILE * file;
  
    file = openFile(file);
    readWords(file, word);

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

void readWords(FILE * file, vector<pair<int,char>> word) {
    char aux; 
    int i = 0;
    
    while(fscanf(file,"%c", &aux) != EOF) {
        if(aux != '\n') {
            word.push_back(make_pair(i,aux));
            i++;
        }
        else {
            i = 0;
        }
        
    }

    fclose(file);

    for(unsigned int i = 0; i < word.size(); i++) {
        cout << word[i].first << ":" << word[i].second << endl; 
    }

    cout << "\n\n" << endl;
      randomChacarter(word);  
}

void randomChacarter(vector<pair<int,char>> word) {
    random_shuffle(word.begin(), word.end());
    for(unsigned int i = 0; i < word.size(); i++) {
        cout << word[i].first << ":" << word[i].second << endl; 
    }
}