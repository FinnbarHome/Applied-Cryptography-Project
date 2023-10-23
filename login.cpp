#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "authlib.h"
#include "openssl/sha.h"

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
            // Extract username from the read line
            getline(ss, usernameFromFile, ':'); 
            // Extract password from the read line
            getline(ss, passwordFromFile, ':'); 
            // Check if entered credentials match any in the file
            isAuthenticated = usernameFromFile == usernameIn && passwordFromFile == getSHA256(passwordIn); 
        }
        // Close the file after reading
        passwordsFile.close(); 

        if (isAuthenticated) {
            // Exit indicating successful authentication
            authenticated(usernameIn); return 0; 
        } 
        else if(attempts < MAX_ATTEMPTS) {
            cout << "Incorrect login details. You have " << (MAX_ATTEMPTS - attempts) << " attempts left." << endl;
            system("clear"); // Clear the console screen
        }
        // If maximum attempts exceeded, reject the user
        else {
            rejected(usernameIn); 
        } 
    }
    return 0;
}
