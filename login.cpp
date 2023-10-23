#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "authlib.h"
#include "openssl/sha.h"

using namespace std;

// Function to get the SHA256 hash of a string
string getSHA256(const string& input) {
    // Testing input
    cout << input << std::endl;
    // Implementing SHA256 hash using openssl
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256; 
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.size()); // Hashing our input
    SHA256_Final(hash, &sha256); // Storing our input inside of hash.
    // Converting unsigned char to string
    string  hash_stringified;
    // hash_stringified should return the stringed hash
    cout << hash_stringified << std::endl;;
    // Hash should return the RAW HASH
    cout << hash << std::endl;; 
    // Returning hash as string
    return hash_stringified;
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
    string hashedPassword(getSHA256(passwordIn));

    // Opens passwords.txt file
    ifstream passwordsFile("passwords.txt");
    //If there's any sort of problem with passwords file
    if (!passwordsFile) {
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
