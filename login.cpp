#include <iostream>
#include <fstream>
#include <sstream>
#include "authlib.h"
#include "openssl/sha.h"

using namespace std;

// Function to get the SHA256 hash for a string provided o it
string getSHA256(const string& input) {
    // Implement SHA256 hash using openssl
    // Return hash as string
    return 0;
}


int main() {
    // Stores the password and username the user enters
    string usernameIn, passwordIn;

    // Prompt user for username and store
    cout << "Enter your username: ";
    cin >> usernameIn;

    // Prompt user for password and store
    cout << "Enter your password: ";
    cin >> passwordIn;

    // Get SHA256 hash of password
    string hashedPassword(passwordIn);

    // Opens passwords.txt file
    ifstream passwordsFile("passwords.txt");
    //If there's any sort of problem with passwords file
    if (!passwordFile) {
        cerr << "Error opening password file." << endl;
        return 1;
    }

    string line;
    bool isAuthenticated = false;
    while (getline(passwordsFile, line)) {
        stringstream ss(line);
        string usernameFromFile, passwordFromFile;
        getline(ss, usernameFromFile, ':');
        getline(ss, passwordFromFile, ':');

        if (usernameFromFile == usernameIn && passwordFromFile == hashedPassword) {
            isAuthenticated = true;
            break;
        }
    }
    passwordsFile.close();

    if (isAuthenticated) {
        authenticated(usernameIn);
    }
    else {
        rejected(usernameIn);
    }

    return 0;
}
