#include <iostream>
#include <string>
#include <fstream>

#ifdef __linux__
    #include <unistd.h>
#elif _WIN32
    #include <windows.h>
#endif


using namespace std;

string script;

void interpret(string content) {
    unsigned int data_size;
    unsigned int scope_size = 0;
    string temp;
    bool sizefound = true;
    int **dat = nullptr;
    unsigned int pointer = 0;
    unsigned int scope = 0;
    unsigned int loopcount;
    unsigned int loopstartpos;
    int copy_value;
    bool copy = false;

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
                dat = new int*[scope_size];
                for (int row = 0; row < scope_size; ++row) {
                    dat[row] = new int[data_size];
                }
                for (int row = 0; row < scope_size; ++row) {
                    for (int col = 0; col < data_size; ++col) {
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
                        cout << char(dat[scope][pointer]);
                    } else {
                        cout << dat[scope][pointer];
                    }
                    break;
                case ',':
                // input
                    if(content[i-1] == 'c') {
                        char c;
                        cin >> c;
                        dat[scope][pointer] = int(c);
                    } else {
                        int n;
                        cin >> n;
                        dat[scope][pointer] = int(n);
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
                // increase value
                    dat[scope][pointer]++;
                    break;
                case '-':
                // decrease value
                    dat[scope][pointer]--;
                    break;
                case '[':
                // begin loop
                    loopstartpos = i+1;
                    loopcount = dat[scope][pointer];
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
                    dat[scope][pointer] = pointer;
                    break;
                case '(':
                // begin scope
                    scope++;
                    dat[scope] = dat[scope-1];
                    break;
                case ')':
                // end scope
                    scope--;
                    dat[scope+1] = nullptr;
                    break;
                case '|':
                // copy paste
                    if(copy) {
                        dat[scope][pointer] = copy_value;
                        copy = false;
                    } else {
                        copy_value = dat[scope][pointer];
                        copy = true;
                    }
                    break;
                case '@':
                // go to position
                    pointer = dat[scope][pointer];
                    break;
                case '*':
                // equal zero
                    dat[scope][pointer] = 0;
                    break;
                case '!':
                // invert value
                    dat[scope][pointer] = -dat[scope][pointer];
                    break;
            }
        }
    }
    delete[] dat;
}



int main(int argc, char **argv) // does not work on windows (boowop)
{
    string content;

    #ifdef __linux__
        char cwd[1024];

        string argument = argv[1];
        string tmpcwd = getcwd(cwd, sizeof(cwd));
        string fullcwd = tmpcwd + "/" + argument;

        ifstream pssfile(fullcwd.c_str());
        if (!pssfile.is_open()) {
            cerr << "Error: File '" << fullcwd << "' does not exist." << endl;
            return 1;
        }

        getline(pssfile, content);

    #elif _WIN32
        string argument = argv[1];
        
        // Get current working directory
        char buffer[MAX_PATH];
        GetCurrentDirectoryA(MAX_PATH, buffer);
        string cwd(buffer);
        
        string fullcwd = cwd + "\\" + argument;

        // Open file
        ifstream pssfile(fullcwd.c_str());
        if (!pssfile.is_open()) {
            cerr << "Error: File '" << fullcwd << "' does not exist." << endl;
            return 1;
        }

        getline(pssfile, content);
    #else
        cout << "Not certain of platform" << endl;
        return(1);
    #endif

    interpret(content);
    return 0;
}

// protocol scope script
