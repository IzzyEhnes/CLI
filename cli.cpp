#include <iostream>
#include <queue>

using namespace std;

string legal_commands[14] = {"cd", "exec", "exit", "gcc", "ls", "man", "more", "mv", "rm", "pwd", "sh", "touch", "which", "$path"};
int legal_commands_length = sizeof(legal_commands) / sizeof(int);



void print_legal_commands()
{

    cout << "Legal commands: ";
    for (int i = 0; i < legal_commands_length; i++)
    {
        cout << legal_commands[i] << ' ';
    }

    cout << endl;
}



bool is_legal_command(string inCommand)
{
    for (int i = 0; i < legal_commands_length; i++)
    {
        if (legal_commands[i] == inCommand)
        {
            return true;
        }
    }

    return false;
}



void execute_CLI(const char* command)
{
    system(command);
}



void process_input(int argc, char *argv[], char* envp[])
{
    print_legal_commands();

    std::queue <string> commands;

    string raw_commands = "";

    for (int i = 1; i < argc; i++)
    {
        raw_commands += argv[i];
        raw_commands += " ";
    }

    cout << raw_commands;
}



int main(int argc, char *argv[], char* envp[])
{
    process_input(argc, argv, envp);
}