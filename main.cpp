//
// Author: Adithya Jose, UIC, Spring 2021
// Assignment: Project 02: Part 02
//
// g++ -g -Wall main.cpp -o main
// ./main
//
// Project Description:
// The goal for project 02 is to extend the banking program I created to support N (any number) bank accounts.
// In project 02 we’re going to support any number of bank accounts, along with the ability to add, subtract, and get certain information from specified accounts and balances.
// Specifically we will be using dynamically-allocated arrays for storing and manipulating the bank data.
// In part 01, I’ll introduce arrays and update the interactive loop accordingly.
// In part 02, I’ll be focusing on the dynamic aspect of the arrays and adding support for adding, deleting, and merging accounts.
//
//


#include <iostream>
#include <iomanip>   
#include <fstream>
#include <string>

using namespace std;


//
// checkArrays
//
// Required function that currently outputs to console, but when submitted
// to gradescope this function will be replaced by one that performs more
// extensive checks to make sure the data was input correctly.
//
void checkArrays(int accounts[], double balances[], int N)
{
 cout << std::fixed;
 cout << std::setprecision(2);
 cout << "** Checking arrays..." << endl;
 cout << "1. " << accounts[0] << ", $" << balances[0] << endl;
 cout << N << ". " << accounts[N-1] << ", $" << balances[N-1] << endl;
}


//
// search
//
// Given an array of N accounts in ascending order, searches for
// the account that matches "acct". If found, the index of that
// account is returned; if not found -1 is returned.
//
int search(int accounts[], int N, int acct)
{
    int searchedIndex; // index of account we return
    
    for (int i = 0; i < N; ++i)
    {
        if (accounts[i] == acct)
        {
            searchedIndex = i;
            return searchedIndex;
        }
    }
    
    return -1; // assume search will fail and in that case return -1 
}


//
// maxBalance
//
// Given an array of N balances, searches for the highest balances
// and returns the index of this balance. If there's a tie, the
// first (smaller) index is returned. Assumes N > 0.
//
int maxBalance(double balances[], int N)
{
    
    int maxIndex; // index of balance we return
    double maxBalance = 0;
    
    for (int i = 0; i < N; i++)
    {
        if (balances[i] > maxBalance)
        {
            maxBalance = balances[i];
            maxIndex = i;
        }
    }
    
    return maxIndex;
    
}


//
// maxAccount
//
// Given an array of N accounts, searches for the highest account number
// and returns the index of this account. If there's a tie, the
// first (smaller) index is returned. Assumes N > 0.
//
int maxAccount(int accounts[], int N)
{
    
    int maxIndex; // index of balance we return
    int maxAccount = 0;
    
    for (int i = 0; i < N; i++)
    {
        if (accounts[i] > maxAccount)
        {
            maxAccount = accounts[i];
            maxIndex = i;
        }
    }
    
    return maxIndex;
    
}


int main()
{
    cout << std::fixed;
    cout << std::setprecision(2);
    
    cout << "** Welcome to UIC Bank v2.0 **" << endl;
    
    string filename;
    cout << "Enter bank filename> " << endl;        // prompt to enter input file
    cin >> filename;
    
    ifstream infile;        // declares an input file object
     
    infile.open(filename);        // opens input file
    
    cout << "** Inputting account data..." << endl;

    // mitigation to make sure input file is legitmate otherwise prints error message
    
    if (!infile.good())  // file is NOT good, i.e. could not be opened:
    {
        cout << "**Error: unable to open input file '" << filename << "'" << endl;
        return 0;  // return now since we cannot continue without proper input file
    }
    
    int N; 
                    // creating int object for how many accounts and balances as pairs there are
    infile >> N;

    int* accounts;
    accounts = new int[N];
                            // creating accounts and balances array of how many there are taken in by N
    double* balances;
    balances = new double[N];

    for (int i = 0; i < N; ++i) // filling in array with data from file based on N
    {
        infile >> accounts[i];
        infile >> balances[i];
    }
        
    infile.close(); // close input file

    checkArrays(accounts, balances, N);
        
    
    ofstream outfile;        // declares an output file object
     
    outfile.open(filename);        // opens output file
    
    outfile << std::fixed;
    outfile << std::setprecision(2);
    
    // mitigation to make sure output file is legitmate otherwise prints error message

    // if (!outfile.good())  // file is NOT good, i.e. could not be opened:
    // {
        // cout << "**Error: unable to open output file '" << filename << "'" << endl;
        // return 0;  // return now since we cannot continue without output file
    // }
    // else
    // {
        cout << "** Processing user commands..." << endl;        // message to indicate opening output file was succesful
    // }
    
    // various int, double, and string objects made to be used if our while loop that process different commands
    
    string commandInput;
    int accountID;
    int low;
    int high;
    double balanceDiff;
    int balanceIndex;
    int accountIndex;
    double ogBalance;
    double posBalsSum;
    
    //
    // Deposit: + account amount
    // Withdrawal: - account amount
    // Check balance: ? account
    // Find the account with the largest balance: ^
    // List accounts and balances in range: * low high
    // List of accounts with a negative balance: <
    // Total of all positive balances in the bank: $
    // Add a new account: add
    // Delete an existing account: del acct
    // Exit: x
    //
    
    while (commandInput != "x") // while loop will only end if "x" is given as an input hence ending the program
    {
    
        cout << "Enter command (+, -, ?, ^, *, <, $, add, del, x):" << endl; // prompt for user to input a command

        cin >> commandInput;

        // if loop to make sure proper commands are being inputted otherwise error message will be displayed

        if ((commandInput != "+") && (commandInput != "-") && (commandInput != "?") && (commandInput != "^") && (commandInput != "*") && (commandInput != "<") && (commandInput != "$") && (commandInput != "add") && (commandInput != "del") && (commandInput != "x"))
        {
            cout << "** Invalid command, try again..." << endl;
        }
        
        if (commandInput == "+") // adds to a certain balance
        {
            
            cin >> accountID;
            cin >> balanceDiff;
            
            balanceIndex = search(accounts, N, accountID);
            
            if (balanceIndex == -1)
            {
                cout << "** Invalid account, transaction ignored" << endl;
            }
            else
            {
                ogBalance = balances[balanceIndex];
                balances[balanceIndex] = ogBalance + balanceDiff;

                cout << "Account " << accounts[balanceIndex] << ": balance $" << balances[balanceIndex] << endl;
            }
        }
        
        if (commandInput == "-") // subtracts from a certain balance
        {
            
            cin >> accountID;
            cin >> balanceDiff;
            
            balanceIndex = search(accounts, N, accountID);
            
            if (balanceIndex == -1)
            {
                cout << "** Invalid account, transaction ignored" << endl;
            }
            else
            {
                ogBalance = balances[balanceIndex];
                balances[balanceIndex] = ogBalance - balanceDiff;

                cout << "Account " << accounts[balanceIndex] << ": balance $" << balances[balanceIndex] << endl;
            }   
                
        }
        
        if (commandInput == "^") // display account with the greatest balance
        {
            
            balanceIndex = maxBalance(balances, N);
            
            cout << "Account " << accounts[balanceIndex] << ": balance $" << balances[balanceIndex] << endl;
            
        }
        
        if (commandInput == "?") // gets data of a certain account and its balance
        {
            
            cin >> accountID;
            
            accountIndex = search(accounts, N, accountID);
            
            if (accountIndex == -1)
            {
                cout << "** Invalid account, transaction ignored" << endl;
            }
            else
            {
                cout << "Account " << accounts[accountIndex] << ": balance $" << balances[accountIndex] << endl;
            }
        }
        
        if (commandInput == "*") // displays all accounts and balances from low-to-high range given
        {
            cin >> low;
            cin >> high;
            
            for (int i = 0; i < N; ++i)
            {
                if ((accounts[i] >= low) && (accounts[i] <= high))
                {
                    cout << "Account " << accounts[i] << ": balance $" << balances[i] << endl;
                }    
            }
        }
        
        if (commandInput == "<") // displaying all negative account balances
        {
            for (int i = 0; i < N; ++i)
            {
                if (balances[i] < 0)
                {
                    cout << "Account " << accounts[i] << ": balance $" << balances[i] << endl;
                }
            }
        }
        
        if (commandInput == "$") // displaying total of all positive balances in the bank
        {
            posBalsSum = 0;
            
            for (int i = 0; i < N; ++i)
            {
                if (balances[i] > 0)
                {
                    posBalsSum = posBalsSum + balances[i];
                }
            }
            
            cout << "Total deposits: $" << posBalsSum << endl;
            
        }
        
        if (commandInput == "add") // adding a new bank account with a balance of $0.00
        {
            
            int NewAcctNum;
            NewAcctNum = 1 + accounts[maxAccount(accounts, N)]; // applying set maxAccount function here to creat a new account number
            
            int* A;
            A = new int[N + 1];

            double* B;
            B = new double[N + 1];
            
            for (int i = 0; i < N; ++i)
            {
                A[i] = accounts[i];
            }
            
            for (int i = 0; i < N; ++i)
            {
                B[i] = balances[i];
            }
            
            A[(N + 1) - 1] = NewAcctNum;
                                            // setting new account and balance and index at the last index of our arrays
            B[(N + 1) - 1] = 0.00;
            
            delete[] accounts;
            delete[] balances;
            
            accounts = A;
            balances = B;
            
            N += 1;
            
            cout << "Added account " << accounts[N - 1] << ": balance $" << balances[N - 1] << endl;
            
        }
        
        if (commandInput == "del") // deleting a specified bank account
        {
            
           cin >> accountID;
            
           accountIndex = search(accounts, N, accountID);
            
           if (accountIndex == -1)
           {
               cout << "** Invalid account, transaction ignored" << endl;
           }
           else
           {
               for(int i = accountIndex; i < N - 1; ++i) // appplying the left shift method here using the for and different indexes
               {
                   accounts[i] = accounts[i + 1];
                   balances[i] = balances[i + 1];
               }

               N = N - 1;

               cout << "Deleted account " << accountID << endl;
           } 
        }
    
    }
    
    cout << "** Saving account data..." << endl; // message to indicate we are outputting to out output file
    
    outfile << N << endl; // outputting number of accounts and balances
    
    for (int j = 0; j < N; ++j) // simple for loop to output all of the final data
    {
        outfile << accounts[j] << " " << balances[j] << endl;
    }
    
    cout << "** Done **" << endl; // program function is done
    
    outfile.close(); // closes output file
    
    // mitigation to stay clear from memory leaks or errors
    
    delete[] accounts;
    delete[] balances;
    
    return 0; // terminates program
}