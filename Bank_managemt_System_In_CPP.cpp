#include <bits/stdc++.h>
#define MAX_NO_OF_USERS 100
using namespace std;

class User
{
public:
    long long int account_number;
    string name;
    double balance;
    string address;

    User(long long int acc_no, string name, double balance, string address)
        : account_number(acc_no), name(name), balance(balance), address(address) {}

    void printUser() const
    {
        cout << "Account Number: " << account_number << endl;
        cout << "Name: " << name << endl;
        cout << "Balance: " << balance << endl;
        cout << "Address: " << address << endl;
    }
};

void adminMode(vector<User> &users);
void userMode(vector<User> &users);
void createUser(vector<User> &users);
void readUsers(const vector<User> &users);
void updateUser(vector<User> &users);
void deleteUser(vector<User> &users);
int searchUser(const vector<User> &users, const string &name);
void transaction(vector<User> &users);

int main()
{
    vector<User> users;

    int choice;
    do
    {
        cout << "\nBank Management System\n";
        cout << "1. Admin Mode\n";
        cout << "2. User Mode\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            adminMode(users);
            break;
        case 2:
            userMode(users);
            break;
        case 3:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}

void adminMode(vector<User> &users)
{
    int choice;
    do
    {
        cout << "\nAdmin Mode\n";
        cout << "Press 1 to View all Records.\n";
        cout << "Press 2 to Create Records.\n";
        cout << "Press 3 to Update Records.\n";
        cout << "Press 4 to Delete Records.\n";
        cout << "Press 5 for Transactions.\n";
        cout << "Press 6 to Exit.\n";
        cout << "Enter your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            readUsers(users);
            break;
        case 2:
            createUser(users);
            break;
        case 3:
            updateUser(users);
            break;
        case 4:
            deleteUser(users);
            break;
        case 5:
            transaction(users);
            break;
        case 6:
            cout << "Exiting admin mode...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
}

void userMode(vector<User> &users)
{
    string name;
    cout << "Enter your name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    getline(cin, name);

    int index = searchUser(users, name);
    if (index != -1)
    {
        cout << "Welcome, " << users[index].name << "!\n";
        users[index].printUser();
    }
    else
    {
        cout << "User not found.\n";
    }
}

void createUser(vector<User> &users)
{
    long long int acc_no;
    string name;
    double balance;
    string address;

    cout << "Enter account number: ";
    cin >> acc_no;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter address: ";
    getline(cin, address);
    cout << "Enter initial balance: ";
    cin >> balance;

    users.emplace_back(acc_no, name, balance, address);
}

void readUsers(const vector<User> &users)
{
    cout << "All registered users displaying:\n";
    for (const auto &user : users)
    {
        user.printUser();
        cout << "------------------\n";
    }
}

void updateUser(vector<User> &users)
{
    string name;
    cout << "Enter the name of the user to update: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    getline(cin, name);

    int index = searchUser(users, name);
    if (index != -1)
    {
        cout << "Enter new balance: ";
        cin >> users[index].balance;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        cout << "Enter address: ";
        getline(cin, users[index].address);
        cout << "Record updated successfully.\n";
    }
    else
    {
        cout << "User not found.\n";
    }
}

void deleteUser(vector<User> &users)
{
    string name;
    cout << "Enter the name of the user to delete: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    getline(cin, name);

    int index = searchUser(users, name);
    if (index != -1)
    {
        users.erase(users.begin() + index);
        cout << "Record deleted successfully.\n";
    }
    else
    {
        cout << "User not found.\n";
    }
}

int searchUser(const vector<User> &users, const string &name)
{
    for (size_t i = 0; i < users.size(); ++i)
    {
        if (users[i].name == name)
        {
            return i;
        }
    }
    return -1;
}

void transaction(vector<User> &users)
{
    string name;
    cout << "Enter your name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    getline(cin, name);

    int index = searchUser(users, name);
    if (index != -1)
    {
        int choice;
        double amount;
        cout << "1. Balance Enquiry\n";
        cout << "2. Cash Deposit\n";
        cout << "3. Cash Withdrawal\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Your current balance is: " << users[index].balance << endl;
            break;
        case 2:
            cout << "Enter deposit amount: ";
            cin >> amount;
            users[index].balance += amount;
            cout << "Amount deposited successfully. Your updated balance is: " << users[index].balance << endl;
            break;
        case 3:
            cout << "Enter withdrawal amount: ";
            cin >> amount;
            if (amount <= users[index].balance)
            {
                users[index].balance -= amount;
                cout << "Amount withdrawn successfully. Your updated balance is: " << users[index].balance << endl;
            }
            else
            {
                cout << "Insufficient balance.\n";
            }
            break;
        default:
            cout << "Invalid choice.\n";
        }
    }
    else
    {
        cout << "User not found.\n";
    }
}
