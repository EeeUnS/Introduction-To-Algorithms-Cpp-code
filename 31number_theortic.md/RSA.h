
#ifndef RSA__H
#define RSA__H
#include<utility>
#include<string>
#include<iostream>

class RSA
{
public:
	RSA();
	~RSA();
	void Encryption(char* st);
	void Encryption(std::string& str);
	void Decryption(char* str);
	void Decryption(std::string& str);
	void generate_key(int p, int q);
	void setter_public_key(std::pair<int, int> key);
	std::pair<int, int> getter_secret_key();
	std::pair<int, int> getter_public_key();
private:
	//public  P (e,n) or secret S = (d, n)
	std::pair<int, int> secret_key;
	std::pair<int, int> public_key;
	bool is_prime(int a);
	int MODULAR_EXPONENTIATION(int a, int b, int n);
	int extended_Euclid_for_multiple_inverse(const int a, const int mod_n);
	int gcd(int a, int b);
};
#endif
