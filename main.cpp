#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>


#ifdef __linux__
    #include <unistd.h>
#elif _WIN32
    #include <filesystem>
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
            if (content[i] == '^') {
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
                // initialize
                for (int pos = 0; pos < data_size; ++pos) {
                        data_array[0][pos] = 0;
                }
            }
            temp += content[i];
        } else {
            switch(content[i]) {
                case '!':
                // print
                    if(content[i-1] == 'c') {
                        cout << char(data_array[scope][pointer]);
                    } else {
                        cout << data_array[scope][pointer];
                    }
                    break;
                case '?':
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
                case '_':
                // copy paste
                    if(copy) {
                        data_array[scope][pointer] = copy_value;
                        copy = false;
                    } else {
                        copy_value = data_array[scope][pointer];
                        copy = true;
                    }
                    break;
                case '&':
                // get pointer position
                    data_array[scope][pointer] = pointer;
                    break;
                case '*':
                // get value
                    data_array[scope][pointer] = data_array[scope][data_array[scope][pointer]];
                    break;
                case '~':
                // go to position
                    pointer = data_array[scope][pointer];
                    break;

                case ';':
                // sleep miliseconds
                    this_thread::sleep_for(chrono::milliseconds(data_array[scope][pointer]));
                    break;
                case '$':
                // file
                    
                    if(content[i-1] == 'w') {
                        // write file
                        #ifdef __linux__
                            // linux file support
                        #elif _WIN32
                            // windows fle support
                        #endif
                    } else if(content[i-1] == 'r') {
                        // read file
                        #ifdef __linux__
                            // linux file support
                        #elif _WIN32
                            // windows fle support
                        #endif
                    } else {
                        // create file
                        #ifdef __linux__
                            // linux file support
                        #elif _WIN32
                            // windows fle support
                        #endif
                    }

                    break;
            }
        }
    }
}



int main(int argc, char **argv) {
    
    string fullcwd;
    string content;

    #ifdef __linux__
        char cwd[1024];
        string argument = argv[1];

        // get current working directory
        string tmpcwd = getcwd(cwd, sizeof(cwd));
        fullcwd = tmpcwd + "/" + argument;
    #elif _WIN32
        string argument = argv[1];

        // Get current working directory
        filesystem::path cwd = filesystem::absolute(filesystem::path(__FILE__)).parent_path();
        fullcwd = cwd.string() + "\\" + argument;
    #else
        cout << "Not certain of platform" << endl;
        return(1);
    #endif

    // Open file
    ifstream pssfile(fullcwd.c_str());

    if (!pssfile.is_open()) {
        cerr << "Error: File '" << fullcwd << "' does not exist." << endl;
        return 1;
    }

    // get file lines
    string str;

    while(getline(pssfile, str)) {
        content += str;
        content.push_back('\n');
    }

    // interpret the content
    interpret(content);
    return 0;
}

// protocol scope script
