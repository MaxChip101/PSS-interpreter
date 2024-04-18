#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
#include <stack>


#ifdef __linux__
    #include <unistd.h>
#elif _WIN32
    #include <filesystem>
    #include <windows.h>
#endif


using namespace std;

string script;

bool verbose = false;

void error(string exception, int char_pos, string context, bool verbose) {
    if(verbose) {
        cerr << " \033[31m \033[4m" + context + "\033[0m \033[0m" << "\n";
        
        cerr << "\033[31m" << exception + ". CHAR: " + to_string(char_pos) << "\033[0m" << "\n";
    } else {
        cerr << "\033[31m" << exception << "\033[0m" << "\n";
    }
}


void interpret(string content) {
    unsigned int data_size;
    unsigned int scope_size = 2;
    string temp;
    bool sizefound = true;
    int **data_array = nullptr;
    unsigned int pointer = 0;
    unsigned int scope = 0;
    unsigned int loopcount;
    stack<unsigned int> loopstack;
    stack<unsigned int> loopvalue;
    int copy_value;
    bool copy = false;
    bool commented = false;
    string context;

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
            context += content[i];
            switch(content[i]) {
                case '@':
                // comment
                    commented = !commented;
                    break;
                case '!':
                // print
                if(!commented) {
                    if(content[i-1] == 'c') {
                        cout << char(data_array[scope][pointer]);
                    } else if(content[i-1] == 'n') {
                        cout << "\n";
                    } else if(content[i-1] == 's') {
                        cout << " ";
                    } else {
                        cout << data_array[scope][pointer];
                    }
                }
                    break;
                case '?':
                // input
                if(!commented) {
                    if(content[i-1] == 'c') {
                        char c;
                        cin >> c;
                        data_array[scope][pointer] = c;
                    } else {
                        int n;
                        cin >> n;
                        data_array[scope][pointer] = n;
                    }
                }
                        break;
                case '<':
                // move pointer left
                if(!commented) {
                    if(pointer >= 0){
                        pointer--;
                    } else {
                        error("Error 2: cannot go to memory position: " + to_string(pointer), i, context, verbose);
                        return;
                    }
                }
                    break;
                case '>':
                // move pointer right
                if(!commented) {
                    if(pointer <= data_size - 1) {
                        pointer++;
                    } else {
                        error("Error 2: cannot go to memory position: " + to_string(pointer), i, context, verbose);
                        return;
                    }
                }
                    break;
                case '+':
                // increase value
                if(!commented) {
                    data_array[scope][pointer]++;
                }
                    break;
                case '-':
                // decrease value
                if(!commented) {
                    data_array[scope][pointer]--;
                }
                    break;
                case '[':
                // begin loop
                if(!commented) {
                    loopstack.push(i);
                    loopvalue.push(pointer);
                }
                    break;
                case ']':
                // end loop
                if(!commented) {
                    if(data_array[scope][loopvalue.top()] == 0) {
                        loopstack.pop();
                        loopvalue.pop();
                    } else {
                        i = loopstack.top();
                        unsigned int temp = loopvalue.top();
                        loopvalue.pop();
                        loopvalue.push(temp);
                    }
                }
                    break;
                case '(':
                // begin scope
                if(!commented) {
                    if(scope+1 <= scope_size) {
                        scope++;
                        data_array[scope] = data_array[scope-1];
                    } else {
                        cout << verbose << "\n";
                        error("Error code 3: cannot go to scope instance: " + to_string(scope), i, context, verbose);
                        return;
                    }
                }
                    break;
                case ')':
                // end scope
                 if(!commented) {
                    if(scope > 0) { 
                        scope--;
                        data_array[scope+1] = nullptr;
                    } else {
                        error("Error code 3: cannot end scope", i, context, verbose);
                        return;
                    }
                }
                    break;
                case '_':
                // copy paste
                if(!commented) {
                    if(copy) {
                        data_array[scope][pointer] = copy_value;
                    } else {
                        copy_value = data_array[scope][pointer];
                    }
                    copy = !copy;
                }
                    break;
                case '&':
                // get pointer position
                if(!commented) {
                    data_array[scope][pointer] = pointer;
                }
                    break;
                case '*':
                // get value
                if(!commented) {
                    if(data_array[scope][pointer] <= data_size || data_array[scope][pointer] >= 0) {
                        data_array[scope][pointer] = data_array[scope][data_array[scope][pointer]];
                    } else {
                        error("Error code 4: cannot get value of memory position: " + to_string(data_array[scope][pointer]), i, context, verbose);
                        return;
                    }
                }
                    break;
                case '~':
                // go to position
                if(!commented) {
                    if(data_array[scope][pointer] <= data_size || data_array[scope][pointer] >= 0) {
                        pointer = data_array[scope][pointer];
                    } else {
                        error("Error code 2: cannot go to memory position: " + to_string(data_array[scope][pointer]), i, context, verbose);
                        return;
                    }
                }
                    break;

                case ';':
                // sleep miliseconds
                if(!commented) {
                    this_thread::sleep_for(chrono::milliseconds(abs(data_array[scope][pointer])));
                }
                    break;
                case '$':
                // file
                if(!commented) {    
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
                }
                    break;
            }
        }
    }
}



int main(int argc, char **argv) {

    string fullcwd;
    string content;

    if(argc == 1) {
        error("Error code 1: no input file", 0, "", false);
        return 0;
    } 

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

    for(int i = 2; i < argc; i++) {
        cout << argv[i] << "\n";
        if(strcmp(argv[i], "-v") || strcmp(argv[i], "-verbose")) {
            verbose = true;
        }
    }

    // interpret the content
    interpret(content);
    return 0;
}

// protocol scope script
