# 31.2
### GCD Euclid's algorithm

O(log b)
```
int EUCLID(int a, int b)
{
	if (b == 0)
		return a;
	else
		return EUCLID(b, a % b);
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

# 31.4

### MODULAR_LINEAR_EQUATION_SOLVER

O(lg n + gcd(a,n))
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

```
# 31.6
## 고속 거듭제곱 모듈러 연산

CLRS에 소개된 의사코드는 잘못되어있다

코드를 살펴보면 c를 사용하지않음
d - bit 
O(d)
```
int MODULAR_EXPONENTIATION(int a, int b, int n)//a^b mod n
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
```


```
int MODULAR_EXPONENTIATION(int a, int b)//a^b mod n
{
	int x = a, y = 1;
	while(b != 0)
	{
		if (b & 1)
		{
			y = (x * y);
		}
		x = (x * x);
		b = b >> 1;
	}
	return y;
}
```
# 31.8 Primality tetsting

O(sqrt(n))

```
bool trial_division(int n)
{
	if (n == 2)
	{
		return true;
	}

	if ((n % 2 == 0) | (n == 1))
	{
		return false;
	}
	for(int i = 3; i*i <= n ; i += 2)
	{
		if(n%i == 0)
		{
			return false;
		}
	}
	return true;
}

```




### PSEUDOPRIME(n)
Carmichael numbers 561 1105 1729
```
constexpr bool PRIME = true;
constexpr bool COMPOSITE = false;

bool PSEUDOPRIME(int n)
{
	if (MODULAR_EXPONENTIATION(2, n - 1, n) != 1)
	{
		return COMPOSITE;
	}
	return PRIME;
}
```
## MILLER_RABIN_primality_test
https://casterian.net/archives/396

https://www.acmicpc.net/problem/5615


O(k log^3 n)


```

bool WITNESS(int a, int n)
{
	int t = 1;
	int et = 2;
	while ((n - 1)%et == 0)
	{
		et *= 2;
		t++;
	}
	et /= 2;
	t--;
	int u = (n-1) / et;
	int x_pre = MODULAR_EXPONENTIATION(a, u, n);
	int x = x_pre;
	for (int i = 0; i < t; i++)
	{
		x = (x_pre * x_pre) % n;
		if (x == 1 && x_pre != 1 && x_pre != n - 1)
		{
			return true;
		}
		x_pre = x;
	}
	if (x != 1)
		return true;
	return false;
}
```

a = 2,3,5,7,11,13,17, 31,61 ,73
정도로할때 정수표현가능한 모든 소수를 판ㄴ별할수있다.

```
constexpr bool PRIME = true;
constexpr bool COMPOSITE = false;

bool MILLER_RABIN(int n, int s)
{
	if (n == 2)
	{
		return PRIME;
	}
	if (n == 1 || n%2 == 0)
	{
		return COMPOSITE;

	}
	int a = 1;
	for (int j = 0; j < (n-1)/2 ; j++)
	{
		a++;
		if (WITNESS(a, n)) //합성수일시 true 반환
		{
			return COMPOSITE;
		}
	}
	return PRIME; //probably
}

```
전체적으로 소수들을 구할때는 에라토스테네스의 체가 효율적이라고 생각.



# 31.9 Integer factorization

https://www.acmicpc.net/problem/4149


test X
```
void POLLARED_RHO(int n)
{
	int i = 1;
	int x = 2;// random n
	int y = x;
	int k = 2;
	int x_n = 0;
	int d = 0;
	while (1)
	{
		i++;
		x_n = (x * x - 1) % n;
		d = EUCLID(y - x, n);
		if (d != 1 && d != n)
		{
			std::cout << d << '\n';
		}
		if (i == k)
		{
			y = x_n;
			k = 2 * k;
		}
	}
}

```

# Problems

### 31-2 Binary gcd algorithm

```

unsigned int gcd(unsigned int u, unsigned int v)
{
	if (u == 0)
	{
		return v;
	}
	if (v == 0)
	{
		return u;
	}

	if (((u & v) & 1) == 0) // 짝수
	{
		return (gcd(u >> 1, v >> 1)) << 1;
	}
	if ((u & 1) == 0) // 짝수
	{
		return gcd(u >> 1, v );
	}
	if((v & 1) == 0)
	{
		return gcd(u, v >> 1);
	}
	if (v > u)
	{
		int a = v;
		v = u;
		u = a;
	}
	
	else
	{
		return gcd((u-v)>>1, v);
	}
}
```

### 31-3 Three algorighms for Fibonacci numbers


(a) O(2^n)
```
int Fibonacci_numbers(int n)
{
	if (n == 1 || n == 2)
	{
		return 1;
	}
	return Fibonacci_numbers(n - 1) + Fibonacci_numbers(n - 2);
}
```


(b)
memoization

O(n)
```
int Fibonacci_numbers(int n)
{

	if (n == 1 || n == 2)
	{
		return 1;
	}
	int x = 1, y = 1;

	int Fibonacci = 1;
		for (int i = 3; i <= n; i++)
		{

			Fibonacci = x + y;
			x = y;
			y = Fibonacci;

		}
	return Fibonacci;
}

```


(c)
O(log n)

```
int Fibonacci_numbers(int n)
{
	int mat[2][2] = { 0,1,1,1 };
	int y[2][2] = { 0,1,1,1 };
	int z[2][2] = { 0,1,1,1 };
	if (n == 1 || n == 2)
	{
		return 1;
	}
	int a = n - 1;
	while (a != 0)
	{
		if (a & 1)
		{
			y[0][0] = z[0][0];
			y[0][1] = z[0][1];
			y[1][0] = z[1][0];
			y[1][1] = z[1][1];
			z[0][0] = y[0][0] * mat[0][0] + y[1][0] * mat[0][1];
			z[0][1] = y[0][0] * mat[0][1] + y[0][1] * mat[1][1];
			z[1][0] = y[1][0] * mat[0][0] + y[1][1] * mat[1][0];
			z[1][1] = y[1][0] * mat[0][1] + y[1][1] * mat[1][1];
		}
		y[0][0] = mat[0][0];
		y[0][1] = mat[0][1];
		y[1][0] = mat[1][0];
		y[1][1] = mat[1][1];
		mat[0][0] = y[0][0] * y[0][0] + y[1][0] * y[0][1];
		mat[0][1] = y[0][0] * y[0][1] + y[0][1] * y[1][1];
		mat[1][0] = y[0][0] * y[1][0] + y[1][0] * y[1][1];
		mat[1][1] = y[1][0] * y[0][1] + y[1][1] * y[1][1];
		a = a >> 1;
	}
	return z[1][0];
}
```