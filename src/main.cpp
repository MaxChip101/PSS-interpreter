#include <iostream>
#include <string>
using namespace std;

void interpret(string content) {
    unsigned int data_size;
    unsigned int scope_size = 2;
    string temp;
    bool sizefound = true;
    int **dat = nullptr;
    unsigned int pointer = 0;
    unsigned int scope = 0;
    unsigned int loopcount;
    unsigned int loopstartpos;

    for(int i = 0; i < content.size(); i++) {
        if (sizefound) {
            // get data size
            if (content[i] == '\'') {
                data_size = stoi(temp);
                i++;
                temp = "";
            }
            if (content[i] == ':') {
                // get scope size
                sizefound = false;
                scope_size = stoi(temp);
                dat = new int*[data_size];
                for (int row = 0; row < data_size; ++row) {
                    dat[row] = new int[scope_size];
                }
                for (int row = 0; row < data_size; ++row) {
                    for (int col = 0; col < scope_size; ++col) {
                        dat[row][col] = 0;
                    }
                }
            }
            temp += content[i];
        } else {
            switch(content[i]) {
                case '.':
                // print
                    if(content[i-1] == 'c') {
                        cout << char(dat[pointer][scope]);
                    } else {
                        cout << dat[pointer][scope];
                    }
                    break;
                case ',':
                // input
                    if(content[i-1] == 'c') {
                        char c;
                        cin >> c;
                        dat[pointer][scope] = int(c);
                    } else {
                        int n;
                        cin >> n;
                        dat[pointer][scope] = int(n);
                    }
                        break;
                case '<':
                // move pointer left
                    if(pointer >= 0){
                        pointer--;
                    }
                    break;
                case '>':
                // move pointer right
                    if(pointer <= data_size - 1) {
                        pointer++;
                    }
                    break;
                case '+':
                // increase cell
                    dat[pointer][scope]++;
                    break;
                case '-':
                // decrease cell
                    dat[pointer][scope]--;
                    break;
                case '[':
                // begin loop
                    loopstartpos = i+1;
                    loopcount = dat[pointer][scope];
                    break;
                case ']':
                // end loop
                    if(loopcount != 0) {
                        i = loopstartpos;
                        loopcount--;
                    }
                    break;
                case '~':
                // get pointer position
                    dat[pointer][scope] = pointer;
                    break;
                case '(':
                // begin scope
                    scope++;
                    for(int e = 0; e < data_size; e++) {
                        dat[e][scope] = dat[e][scope-1];
                    }
                    break;
                case ')':
                // end scope
                    scope--;
                    for(int e = 0; e < data_size; e++) {
                        dat[e][scope+1] = 0;
                    }
            }
        }
    }
    delete[] dat;
}



int main() {
    string content;
    cin >> content;
    interpret(content);
    return 0;
}

// protocol scope script