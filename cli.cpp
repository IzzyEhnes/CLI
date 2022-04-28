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



string extract_command(string inString)
{
    string command = "";
    int currChar = 0;

    while (currChar < inString.length())
    {
        if (inString[currChar] == ' ')
        {
            break;
        }

        else
        {
            command += inString[currChar];
        }

        currChar++;
    }

    return command;
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



void execute_command(const char* command)
{
    system(command);
}



void process_queue(std::queue<string> in_queue)
{
    cout << in_queue.size() + 1 << " strings passed to argv[]\n\n";

    while (!in_queue.empty())
    {
        string command = in_queue.front();

        string command_without_args = extract_command(command);

        cout << "Next string is '" << command << "'\n";

        if (!is_legal_command(command_without_args))
        {
            cout << "'" << command_without_args << "' is not one of the predefined commands. Skipping...\n";
        }

        else
        {
            cout << "'" << command_without_args << "' is one of the predefined commands. Executing now...\n";
            execute_command(command.c_str());
            cout << endl;
        }

        in_queue.pop();
    
    }

    execute_command("pwd");
    cout << "is the current working directory.";
    cout << "\n\nGoodbye.\n";
}



void process_input(int argc, char *argv[], char* envp[])
{
    // A queue that will hold all of our commands 
    std::queue <string> command_queue;

    // Add all CLI arguments to string raw_commands
    string raw_commands = "";
    for (int i = 1; i < argc; i++)
    {
        raw_commands += argv[i];
        raw_commands += " ";
    }

    // String where we will build the current command (and any associated arguments)
    string temp_command = "";

    // Add individual commands and their arguments to command_queue
    for (int i = 0; i < raw_commands.length(); i++)
    {
        // If a comma is encountered, this indicated the end of a single command (and any associated arguments)
        if (raw_commands[i] == ',' || i == raw_commands.length() - 1)
        {
            // Add command to command_queue and reset temp_command
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

            // Add current char to temp_command
            else
            {
                temp_command += raw_commands[i];
            }
        }
    }

    process_queue(command_queue);
}



int main(int argc, char *argv[], char* envp[])
{
    print_greeting();
    process_input(argc, argv, envp);
}