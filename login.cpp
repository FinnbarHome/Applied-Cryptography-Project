#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "authlib.h"
#include "openssl/sha.h"

using namespace std;

// getSHA256 will return the SHA-256 hash of string
string getSHA256(const string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH]; // defining hash to store the initial hashed output
    SHA256_CTX sha256; 
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.size()); // Hashing our input
    SHA256_Final(hash, &sha256); // Storing our input inside of hash.
    stringstream strStream; // Converting unsigned char to string via string stream
    for (int i=0; i < SHA256_DIGEST_LENGTH; i++){ // Loop for the length of the hash
        strStream << hex << setw(2) << setfill('0') << (int)hash[i]; // Convert the binary of the hash to hexidecimal
    }
    string hash_stringified = strStream.str(); // Storing the string stream as a string
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
    // If there's any sort of problem with passwords file
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
