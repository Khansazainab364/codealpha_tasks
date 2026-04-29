#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// User structure
struct User {
    string username;
    string password;
};

// Encode password
string encode(string pass) {
    for (int i = 0; i < pass.length(); i++) {
        pass[i] = pass[i] + 2;
    }
    return pass;
}

// Load users
vector<User> loadUsers() {
    vector<User> users;
    ifstream file("users.txt");

    if (!file) {
        cout << "File not found, creating new file...\n";
        return users;
    }

    User temp;
    while (file >> temp.username >> temp.password) {
        users.push_back(temp);
    }

    file.close();
    return users;
}

// Save user
void saveUser(User u) {
    ofstream file("users.txt", ios::app);

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    file << u.username << " " << u.password << endl;
    file.close();
}

// Duplicate check
bool isDuplicate(const vector<User>& users, string name) {
    for (auto u : users) {
        if (u.username == name)
            return true;
    }
    return false;
}

// Sign Up
void signUp() {
    vector<User> users = loadUsers();
    User newUser;

    cout << "\n=== Sign Up ===\n";

    cout << "Username: ";
    cin >> newUser.username;

    cout << "Password: ";
    cin >> newUser.password;

    if (newUser.username.empty() || newUser.password.empty()) {
        cout << "Input cannot be empty!\n";
        return;
    }

    if (newUser.password.length() < 6) {
        cout << "Password too short!\n";
        return;
    }

    if (isDuplicate(users, newUser.username)) {
        cout << "Username already exists!\n";
        return;
    }

    newUser.password = encode(newUser.password);
    saveUser(newUser);

    cout << "Account created successfully!\n";
}

// Sign In
void signIn() {
    vector<User> users = loadUsers();

    string uname, pass;
    cout << "\n=== Sign In ===\n";

    cout << "Username: ";
    cin >> uname;

    cout << "Password: ";
    cin >> pass;

    pass = encode(pass);

    bool ok = false;

    for (auto u : users) {
        if (u.username == uname && u.password == pass) {
            ok = true;
            break;
        }
    }

    if (ok)
        cout << "Welcome back!\n";
    else
        cout << "Login failed!\n";
}

// Main
int main() {
    int option;

    while (true) {
        cout << "\n------ MENU ------\n";
        cout << "1. Sign Up\n";
        cout << "2. Sign In\n";
        cout << "3. Quit\n";
        cout << "Choose: ";
        cin >> option;

        if (option == 1)
            signUp();
        else if (option == 2)
            signIn();
        else if (option == 3) {
            cout << "Program ended.\n";
            break;
        }
        else
            cout << "Wrong option!\n";
    }

    return 0;
}