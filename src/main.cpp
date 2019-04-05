#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <vector>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

FILE * openFile(FILE * file);
void readWords(FILE * file, vector<pair<int,char>> word);
void randomChacarter(vector<pair<int,char>> word);
void getInit();
void startProgram();
void doWhatChildDo();
vector<pair<int, char>> insertionSort(vector<pair<int, char>> word);
void saveOrdenedWord(vector<pair<int, char>> word);
void finishProgram();
void writeBegin(FILE *fp);
void writeMiddle(FILE *fp);
void writeEnd(FILE *fp);

vector<vector<pair<int, char>>> words;
float time_execution;
int position;

int counter = 0;

int main() {
    vector<pair<int,char>> word;
    FILE * file;
  
    file = openFile(file);
    readWords(file, word);
    getInit();

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

void getInit() {
    cout << "Enter time for program execution: ";
    cin >> time_execution;

    cout << "Enter start position for programa execution: ";
    cin >> position;

    startProgram();
}

void startProgram() {
    pid_t child = fork();

    if(child == 0) {
        doWhatChildDo();
    }
    else {
        sleep(time_execution);
        kill(child, SIGTERM);
        finishProgram();
    }
}

void doWhatChildDo() {
    for(int i = position; i < words.size(); i++) {
        saveOrdenedWord(insertionSort(words[i]));
    }
}

vector<pair<int, char>> insertionSort(vector<pair<int, char>> word) {
    vector<pair<int, char>> ordened_word = word;
    pair<int, char> key;
    int i, j;
    
    for (i = 1; i < ordened_word.size(); i++) { 
        key = ordened_word[i]; 
        j = i - 1; 
  
        while (j >= 0 && ordened_word[j].first > key.first) { 
            ordened_word[j+1] = ordened_word[j]; 
            j--; 
        } 
        ordened_word[j+1] = key; 
    } 

    return ordened_word;
}

void saveOrdenedWord(vector<pair<int, char>> word) {
    FILE *fp = fopen("ordened_words.txt", "a+");

    fprintf(fp, "*");
    for(int i = 0; i < word.size(); i++) {
        fprintf(fp, "%c", word[i].second);
    }
    fprintf(fp, "*\n");

    fclose(fp);
}

void finishProgram() {
    FILE *fp = fopen("new.txt", "a+");

    writeBegin(fp);
    writeMiddle(fp);
    writeEnd(fp);

    fclose(fp);

    remove("ordened_words.txt");
    rename("new.txt", "ordened_words.txt");

    cout << "\n\n" << counter - 1 << " words were ordened!\n\n";
}

void writeBegin(FILE *fp) {
    for(int i = 0; i < position; i++) {
        for(int j = 0; j < words[i].size(); j++) {
            fprintf(fp, "%c", words[i][j].second);
        }
        fprintf(fp, "\n");
    }
}

void writeMiddle(FILE *fp) {
    FILE *wd = fopen("ordened_words.txt", "r");
    char a;

    while(!feof(wd)) {
        fscanf(wd, "%c", &a);
        fprintf(fp, "%c", a);

        if(a == '\n')
            counter++;
    }

    fclose(wd);
}

void writeEnd(FILE *fp) {
    for(int i = position + counter - 1; i < words.size(); i++) {
        for(int j = 0; j < words[i].size(); j++){
            fprintf(fp, "%c", words[i][j].second);
        }
        fprintf(fp, "\n");
    }
}

