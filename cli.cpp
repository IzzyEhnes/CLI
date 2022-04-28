#include <iostream>
using namespace std;

string legal_commands[14] = {"cd", "exec", "exit", "gcc", "ls", "man", "more", "mv", "rm", "pwd", "sh", "touch", "which", "$path"};

void get_input(int argc, char *argv[], char* envp[])
{
    cout << "argc = " << argc << endl;
    for (int i = 1; i < argc; i++)
    {
        cout << "argv[" << i << "] = " << argv[i] << endl;
        cout << "Executing command \'" << argv[i] << "\'" << endl;
        execute_CLI(argv[i]);
        cout << endl;
    }
}

void execute_CLI(const char* command)
{
    system(command);
}

int main(int argc, char *argv[], char* envp[])
{
    get_input(argc, *argv[], envp[]);
}