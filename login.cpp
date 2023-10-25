#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "authlib.h"
#include "openssl/sha.h"

using namespace std;

// getSHA256 will return the SHA-256 hash of string
string getSHA256(const string& input) {
    // defining hash to store the initial hashed output
    unsigned char hash[SHA256_DIGEST_LENGTH]; 
    SHA256_CTX sha256; 
    SHA256_Init(&sha256);
    // Hashing our input
    SHA256_Update(&sha256, input.c_str(), input.size()); 
    // Storing our input inside of hash.
    SHA256_Final(hash, &sha256); 
    // Converting unsigned char to string via string stream
    stringstream strStream; 
    // Loop for the length of the hash
    for (int i=0; i < SHA256_DIGEST_LENGTH; i++){ 
        // Convert the binary of the hash to hexidecimal
        strStream << hex << setw(2) << setfill('0') << (int)hash[i]; 
    }
    // Storing the string stream as a string
    string hash_stringified = strStream.str(); 
    return hash_stringified;
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
        if (isAuthenticated) {
            authenticated(usernameIn);
            return 0;
        } 
        // For incorrect login details, reject and re-prompt input
        if(attempts < MAX_ATTEMPTS) {
            cout << "Incorrect login details. You have " << (MAX_ATTEMPTS - attempts) << " attempts left." << endl;
        // If maximum attempts exceeded, reject the user
        } else {
            rejected(usernameIn);
        }
    }
    return 0;
}