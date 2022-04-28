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


void print_greeting()
{
    cout << "CLI by Izzy Ehnes\n";
    cout << "Released 27 April 2022\n";
    print_legal_commands();
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



void process_queue(std::queue <string> in_queue)
{
    while (!in_queue.empty())
    {
        string front = in_queue.front();
        cout << front << endl;
        in_queue.pop();
    }
}



void process_input(int argc, char *argv[], char* envp[])
{
    print_legal_commands();

    std::queue <string> command_queue;

    string raw_commands = "";

    for (int i = 1; i < argc; i++)
    {
        raw_commands += argv[i];
        raw_commands += " ";
    }

    //cout << raw_commands;

    string temp_command = "";
    for (int i = 0; i < raw_commands.length(); i++)
    {
        if (raw_commands[i] == ',' || i == raw_commands.length() - 1)
        {
            command_queue.push(temp_command);
            temp_command = "";
        }

        else
        {
            // Don't add leading space to front of command
            if (temp_command.empty() && raw_commands[i] == ' ')
            {
                continue;
            }

            else
            {
                temp_command += raw_commands[i];
            }
        }
    }
}



int main(int argc, char *argv[], char* envp[])
{
    print_greeting();
    process_input(argc, argv, envp);
}