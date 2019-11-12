
#ifndef RSA__H
#define RSA__H
#endif
#include<utility>


class RSA
{
public:
	RSA();
	~RSA();

    void Encryption(char * str , int n)
    void Encryption(string &str)
    void Decryption(char * str , int n)
    void Decryption(string &str)
	void generate_key(int p, int q);
	void setter_public_key(std::pair<int, int> key);
	bool is_prime(int a);
	std::pair<int, int> getter_secret_key();
	std::pair<int, int> getter_public_key();
private:

	//public  P (e,n) or secret S = (d, n)
	std::pair<int, int> secret_key;
	std::pair<int, int> public_key;

	int MODULAR_EXPONENTIATION(int a, int b, int n);
	int extended_Euclid_for_multiple_inverse(const int a, const int mod_n);

    int gcd(int a, int b)
};



RSA::RSA() :secret_key(0,0) ,public_key(0,0)
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
	while(b != 0)
	{
		if (b & 1)
		{
			y = (x * y) % n;
		}
		x = (x * x) % n;
		b = b >> 1;
	}
	return y;
}


int RSA::extended_Euclid_for_multiple_inverse(const int a, const int mod_n)
{
	if (gcd(a, mod_n) != 1)
		return -1;
	int r1 = a, r2 = mod_n;
	int  t1 = 0, t2 = 1;
	int u, r, t;
	while (r2 > 0)
	{
		u = r1 / r2;

		r = r1 % r2;
		r1 = r2; r2 = r;

		t = t1 - u * t2;
		t1 = t2; t2 = t;
	}
	if (t1 < 0)
		t1 += mod_n;

	return t1;  //e
}


void RSA::generate_key(int p, int q)
{
    if(!(is_prime(p) && is_prime(q)))
    {
        std::cout << "Input prime" <<std::endl;
        return;
    }

	int n = p*q;
    int pi_n = (p-1)*(q-1);

    int e = 0;
    for(int i = pi_n-1 ; 1 ; i--)
    {
        if(gcd(i,pi_n) == 1)
        {
            e = i;
            break;
        }
    }
    int d = extended_Euclid_for_multiple_inverse(e,pi_n);
    public_key = std::make_pair(e,n);
    secret_key = std::make_pair(d,n);
}


void RSA::setter_public_key(std::pair<int, int> key)
{
    public_key = key;
}

int extended_Euclid_for_multiple_inverse(const int a, const int mod_n)
{
	if (gcd(a, mod_n) != 1)
		return -1;
	r1 = a, r2 = mod_n;
	 t1 = 0, t2 = 1;
	u, r, t;
	while (r2 > 0)
	{
		u = r1 / r2;

		r = r1 % r2;
		r1 = r2; r2 = r;

		t = t1 - u * t2;
		t1 = t2; t2 = t;
	}
	if (t1 < 0)
		t1 += mod_n;

	return t1;  //e
}


bool RSA::is_prime(int a)
{
    if(a == 2)
        return true;
    for(int i = 3 ; i*i <= a ; i +=2 )
    {
        if( a%i == 0)
        {
        	return false;
        }
    }
    return true;
}


std::pair<int, int> RSA::getter_secret_key()
{
    if(secret_key == (0,0))
    {
        std::cout << "Don't have a secret key"<< std::endl;
    }
	return secret_key;
}


std::pair<int, int> RSA::getter_public_key()
{
    if(public_key == (0,0))
    {
        std::cout << "Don't have a public key"<< std::endl;
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

void RSA::Encryption(char * str , int n)
{
    for(int i = 0 ; i < n ; i ++)
    {
        str[i] = MODULAR_EXPONENTIATION(i,public_key.second,public_key.first);
    }
}

void RSA::Encryption(string &str)
{
    for(int i = 0 ; i < n ; i ++)
    {
        str[i] = MODULAR_EXPONENTIATION(i,public_key.second,public_key.first);
    }
}

void RSA::Decryption(char * str , int n)
{
    for(int i = 0 ; i < n ; i ++)
    {
        str[i] = MODULAR_EXPONENTIATION(i,secret_key.second,secret_key.first );
    }
}

void RSA::Decryption(string &str)
{
    for(int i = 0 ; i < n ; i ++)
    {
        str[i] = MODULAR_EXPONENTIATION(i,secret_key.second,secret_key.first );
    }
}






