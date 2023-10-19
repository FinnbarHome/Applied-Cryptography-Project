#include <iostream>
#include <fstream>
#include <sstream>
#include "authlib.h"
#include "openssl/sha.h"

// Function to get the SHA256 hash for a string provided o it
std::string getSHA256(const std::string& input) {
    // Implement SHA256 hash using openssl
    // Return hash as string
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
}
