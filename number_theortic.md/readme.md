
## GCD

```
unsigned long long int gcd(const unsigned long long int a, const unsigned long long int b)
{
	if (b == 0)
		return a;
	else
		return gcd(b, a % b);
}
```
### EXTENDED_EUCLID

```
#include<tuple>

std::tuple<int, int, int> EXTENDED_EUCLID(int a, int b)
{
	if (b == 0)
	{
		std::tuple<int, int, int> x(a, 1, 0);
		return x;
	}
	std::tuple<int, int, int> x = EXTENDED_EUCLID(b, a % b);//d x y
	std::tuple<int, int, int> y =
		std::make_tuple(std::get<0>(x), std::get<2>(x), std::get<1>(x) - (a / b) * std::get<2>(x));
	return y;
}
```
### MODULAR_LINEAR_EQUATION_SOLVER
```
void MODULAR_LINEAR_EQUATION_SOLVER(int a, int b, int n)//ax = b (mod n)
{
	std::tuple<int, int, int> set = EXTENDED_EUCLID(a, n);
	int d = std::get<0>(set);
	if (b/d)
	{
		int x_0 = (((std::get<1>(set) * (b / d))%n) + n)%n;
		//x_0 %= n;
		for (int i = 0; i <= d -1; i++)
		{
			std::cout << (x_0 + (i * (n / d))) % n << ' ';
		}
	}
	else
	{
		std::cout << "no solution";
	}
}
```


## modulo 연산에대한 역
```
unsigned long long int extended_Euclid_for_multiple_inverse(const unsigned long long int a, const unsigned  long long int mod_n)
{
	if (gcd(a, mod_n) != 1)
		return -1;
	unsigned long long r1 = a, r2 = mod_n;
	long long t1 = 0, t2 = 1;
	unsigned long long u, r, t;
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

```
# 고속 거듭제곱 모듈러 연산

CLRS에 소개된 의사코드는 잘못되어있다

코드를 살펴보면 c를 사용하지않음
```
int64_t MODULAR_EXPONENTIATION(int64_t a, int64_t b, int64_t n)//a^b mod n
{
	int64_t x = a, y = 1;
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
```


