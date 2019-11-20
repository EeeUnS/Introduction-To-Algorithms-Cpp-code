
#include"RSA.h"

RSA::RSA() :secret_key(0, 0), public_key(0, 0)
{
	;
}

RSA::~RSA()
{
	;
}

//a^b %n
int RSA::MODULAR_EXPONENTIATION(int a, int b, int n)
{
	int x = a, y = 1;
 	while (b != 0)
	{
		if (b & 1)
		{
			y = (x * y) % n;
		}
		x = (x * x) % n;
		b = b >> 1;
	}
	if (y <= 0)
	{
		y += n;
	}
	return y;
}


int RSA::extended_Euclid_for_multiple_inverse(const int a, const int mod_n)
{
	if (gcd(a, mod_n) != 1)
		return -1;

	int r1, r2, q, r, t, t1, t2;
	r1 = a;
	r2 = mod_n;
	t1 = 0; t2 = 1;

	while (r1 != 1)
	{
		q = r2 / r1;
		r = r2 - r1 * q;
		t = t1 - t2 * q;
		r2 = r1;
		r1 = r;
		t1 = t2;
		t2 = t;
	}
	if (t2 < 0)
		t2 = t2 + mod_n;
	return t2;
}


void RSA::generate_key(int p, int q)
{
	if (!(is_prime(p) && is_prime(q)))
	{
		std::cout << "Input prime" << std::endl;
		return;
	}

	int n = p * q;
	int pi_n = (p - 1) * (q - 1);

	int e = 0;
	for (int i = 2 ; 1; i++)
	{
		if (gcd(i, pi_n) == 1)
		{
			e = i;
			break;
		}
	}
	int d = extended_Euclid_for_multiple_inverse(e, pi_n);
	public_key = std::make_pair(e, n);
	secret_key = std::make_pair(d, n);
}


void RSA::setter_public_key(std::pair<int, int> key)
{
	public_key = key;
}

bool RSA::is_prime(int a)
{
	if (a == 1)
	{
		return false;
	}
	if (a == 2)
		return true;
	for (int i = 3; i * i <= a; i += 2)
	{
		if (a % i == 0)
		{
			return false;
		}
	}
	return true;
}


std::pair<int, int> RSA::getter_secret_key()
{
	if (secret_key.first == 0 || secret_key.second == 0)
	{
		std::cout << "Don't have a secret key" << std::endl;
	}
	return secret_key;
}


std::pair<int, int> RSA::getter_public_key()
{
	if (public_key.first == 0 || public_key.second == 0)
	{
		std::cout << "Don't have a public key" << std::endl;
	}
	return public_key;
}

int RSA::gcd(int a, int b)
{
	if (b == 0)
		return a;
	else
		return gcd(b, a % b);
}

void RSA::Encryption(char* str)
{
	if (public_key.first == 0 || public_key.second == 0)
	{
		std::cout << "Don't have a secret key" << std::endl;
		return;
	}
	for (int i = 0; str[i] != '\0'; i++)
	{
		str[i] = MODULAR_EXPONENTIATION(str[i], public_key.first, public_key.second);
	}
}

void RSA::Encryption(std::string& str)
{
	if (public_key.first == 0 || public_key.second == 0)
	{
		std::cout << "Don't have a secret key" << std::endl;
		return;
	}
	const int n = str.length();
	for (int i = 0; i < n; i++)
	{
		str[i] = MODULAR_EXPONENTIATION(str[i], public_key.first, public_key.second);
	}
}

void RSA::Decryption(char* str)
{
	if (secret_key.first == 0 || secret_key.second == 0)
	{
		std::cout << "Don't have a secret key" << std::endl;
		return;
	}
	for (int i = 0; str[i] != '\0'; i++)
	{
		str[i] = MODULAR_EXPONENTIATION(str[i],  secret_key.first, secret_key.second);
	}
}

void RSA::Decryption(std::string& str)
{
	if (secret_key.first == 0 || secret_key.second == 0)
	{
		std::cout << "Don't have a secret key" << std::endl;
		return;
	}

	const int n = str.length();
	for (int i = 0; i < n; i++)
	{
		str[i] = MODULAR_EXPONENTIATION(str[i], secret_key.first,secret_key.second);
	}
}
