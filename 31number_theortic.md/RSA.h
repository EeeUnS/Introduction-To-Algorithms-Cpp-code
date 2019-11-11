
#ifndef RSA__H
#define RSA__H
#endif
#include<utility>


class RSA
{
public:
//	RSA(int p , int q);
//	RSA(std::pair<int,int> key);
	~RSA();

private:

	//public  P (e,n) or secret S = (d, n)
	std::pair<int, int> secret_key;
	std::pair<int, int> public_key;
public:
//	std::pair<int, int> getter_key();
	
private:
	int MODULAR_EXPONENTIATION(int a, int b, int n);
	int extended_Euclid_for_multiple_inverse(const int a, const int mod_n);
public:
	void generate_key(int p, int q);
	void setter_key(std::pair<int, int> key);
	bool is_prime(int a);
	std::pair<int, int> getter_secret_key();
	std::pair<int, int> getter_public_key();
};


RSA::RSA() :secret_key(0,0) ,public_key(0,0)
{
	;
}

RSA::~RSA()
{
	;
}


int RSA::MODULAR_EXPONENTIATION(int a, int b, int n)
{
	// TODO: 여기에 구현 코드 추가.
	return 0;
}


int RSA::extended_Euclid_for_multiple_inverse(const int a, const int mod_n)
{
	// TODO: 여기에 구현 코드 추가.
	return 0;
}


void RSA::generate_key(int p, int q)
{
	// TODO: 여기에 구현 코드 추가.
}


void RSA::setter_key(std::pair<int, int> key)
{
	// TODO: 여기에 구현 코드 추가.
}


bool RSA::is_prime(int a)
{
	// TODO: 여기에 구현 코드 추가.


	return false;
}


std::pair<int, int> RSA::getter_secret_key()
{
	// TODO: 여기에 구현 코드 추가.
	return std::pair<int, int>();
}


std::pair<int, int> RSA::getter_public_key()
{
	// TODO: 여기에 구현 코드 추가.
	return std::pair<int, int>();
}
