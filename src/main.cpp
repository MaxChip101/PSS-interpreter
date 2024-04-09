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
    unsigned int scope_size = 2;
    string temp;
    bool sizefound = true;
    int **data_array = nullptr;
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
                data_array = new int*[scope_size];
                for (int row = 0; row < scope_size; ++row) {
                    data_array[row] = new int[data_size];
                }
                for (int row = 0; row < scope_size; ++row) {
                    for (int col = 0; col < data_size; ++col) {
                        data_array[row][col] = 0;
                    }
                }
            }
            temp += content[i];
        } else {
            switch(content[i]) {
                case '.':
                // print
                    if(content[i-1] == 'c') {
                        cout << char(data_array[scope][pointer]);
                    } else {
                        cout << data_array[scope][pointer];
                    }
                    break;
                case ',':
                // input
                    if(content[i-1] == 'c') {
                        char c;
                        cin >> c;
                        data_array[scope][pointer] = c;
                    } else {
                        int n;
                        cin >> n;
                        data_array[scope][pointer] = n;
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
                    data_array[scope][pointer]++;
                    break;
                case '-':
                // decrease value
                    data_array[scope][pointer]--;
                    break;
                case '[':
                // begin loop
                    loopstartpos = i;
                    loopcount = abs(data_array[scope][pointer])-1;
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
                    data_array[scope][pointer] = pointer;
                    break;
                case '(':
                // begin scope
                    scope++;
                    data_array[scope] = data_array[scope-1];
                    break;
                case ')':
                // end scope
                    if(scope > 0) { 
                        scope--;
                        data_array[scope+1] = nullptr;
                    }
                    break;
                case '|':
                // copy paste
                    if(copy) {
                        data_array[scope][pointer] = copy_value;
                        copy = false;
                    } else {
                        copy_value = data_array[scope][pointer];
                        copy = true;
                    }
                    break;
                case '@':
                // go to position
                    pointer = data_array[scope][pointer];
                    break;
            }
        }
    }
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
