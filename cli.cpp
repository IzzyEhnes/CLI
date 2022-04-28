/** 
 * AUTHOR: Izzy Ehnes
 * DATE: 27 April 2022
 * DESCRIPTION: A command line interpreter that allows users to execute certain Unix commands via a simple shell.
 **/


#include <iostream>
#include <queue>

using namespace std;



// List of predefined commands
string legal_commands[14] = {"cd", "exec", "exit", "gcc", "ls", "man", "more", "mv", "rm", "pwd", "sh", "touch", "which", "$path"};

int legal_commands_length = sizeof(legal_commands) / sizeof(int);



/** 
 * Prints all of the predefined legal commands
 **/
void print_legal_commands()
{

    cout << "Legal commands: ";
    for (int i = 0; i < legal_commands_length; i++)
    {
        cout << legal_commands[i] << ' ';
    }

    cout << endl;
}



/** 
 * Prints the author, release date, as well as a list of legal commands.
 **/
void print_greeting()
{
    cout << "CLI by Izzy Ehnes\n";
    cout << "Released 27 April 2022\n";
    print_legal_commands();
    cout << "Multiple arguments of one cli command must be separated from one another by commas.\nPossible parameters of any one command are separated from the command itself (and from possible further parameters) by white space";
    cout << "\nExample: \"pwd, ls -la\"\n\n";
}



/** 
 * Returns only the command (and no arguments) in inString.
 * 
 * E.g. extract_command("pwd") will return "pwd", and extract_command("ls -la") will return "ls".
 **/
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



/** 
 * Returns 'true' if inCommand is in legal_commands and false otherwise.
 **/
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



/** 
 * Executes an individual command with its arguments, if there are any
 **/
void execute_command(const char* command)
{
    system(command);
}



/** 
 * Processes the queue of commands, and executes them if they are legal.
 **/
void process_queue(std::queue<string> in_queue)
{
    cout << in_queue.size() + 1 << " strings passed to argv[]\n\n";

    // While there are still commands in the queue
    while (!in_queue.empty())
    {
        string command = in_queue.front();

        string command_without_args = extract_command(command);

        cout << "Next string is '" << command << "'\n";

        // If the command is not one of the predefined commands, alert the user and then skip it and continue
        if (!is_legal_command(command_without_args))
        {
            cout << "'" << command_without_args << "' is not one of the predefined commands. Skipping...\n";
        }

        // If the command is legal, execute it
        else
        {
            cout << "'" << command_without_args << "' is one of the predefined commands. Executing now...\n";
            execute_command(command.c_str());
            cout << endl;
        }

        // The command at the front of the queue has been processed, so remove it
        in_queue.pop();
    
    }

    // Prints the working directory once all commands have been executed (or skipped if they are illegal)
    execute_command("pwd");
    cout << "is the current working directory.";
    cout << "\n\nGoodbye.\n";
}



/**
 * Processes the arguments passed in main()
 **/
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

    // All commands and any associated arguments have been queued, so command_queue is ready to be processed
    process_queue(command_queue);
}



int main(int argc, char *argv[], char* envp[])
{
    print_greeting();
    process_input(argc, argv, envp);
}