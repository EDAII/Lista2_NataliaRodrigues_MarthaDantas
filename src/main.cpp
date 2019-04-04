#include <iostream>
#include <vector>

using namespace std;

FILE * openFile(FILE * file);

int main() {
    FILE * file;
  
    file = openFile(file);
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

