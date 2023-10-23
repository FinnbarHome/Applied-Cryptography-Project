#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "authlib.h"
#include "openssl/sha.h"

using namespace std;

// Function to get the SHA256 hash of a string
string getSHA256(const string& input) {
    // Implementing SHA256 hash using openssl
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.size()); // Hashing our input
    SHA256_Final(hash, &sha256); // Storing our input inside of hash.

    // Converting unsigned char to string
    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) // Loop for the length of the hash
        ss << hex << setw(2) << setfill('0') << (int)hash[i]; // Convert the binary of the hash to hexidecimal
    return ss.str(); // Returning hash as string
}

int main() {
    const int MAX_ATTEMPTS = 3; // Int to store max amount of attempts allowed
    int attempts = 0; // Stores amount of attempts user has done

    while(attempts++ < MAX_ATTEMPTS){
        string usernameIn, passwordIn, line, hashedPassword; // Stores the password and username the user enters, line string for file reading and hashed password
        cout << "Enter your username: "; // Prompt user for username and store
        cin >> usernameIn;
        cout << "Enter your password: "; // Prompt user for password and store
        cin >> passwordIn;

        // Reading of password
        ifstream passwordsFile("passwords.txt");
        if (!passwordsFile) { cerr << "Error opening password file." << endl; return 1; }
        
        bool isAuthenticated = false;
        while (getline(passwordsFile, line) && !isAuthenticated) {
            stringstream ss(line);
            string usernameFromFile, passwordFromFile;
            getline(ss, usernameFromFile, ':');
            getline(ss, passwordFromFile, ':');
            isAuthenticated = usernameFromFile == usernameIn && passwordFromFile == getSHA256(passwordIn);
        }
        passwordsFile.close();

        if (isAuthenticated) {
            authenticated(usernameIn);
            return 0;
        } else if(attempts < MAX_ATTEMPTS) {
            cout << "Incorrect login details. You have " << (MAX_ATTEMPTS - attempts) << " attempts left." << endl;
            system("clear");
        } else {
            rejected(usernameIn);
        }
    }
    return 0;
}

