

```C++
#include <complex>
#include <valarray>

constexpr double PI = 3.141592653589793238460;
typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;
```



# 30.2 The DFT and FFT

DFT 를 구하기위해 FFT를 사용한다.

ref
<https://rosettacode.org/wiki/Fast_Fourier_transform>


```C++
CArray RECURSIVE_FFT(CArray& a)
{

	const std::size_t n = a.size();
	if (n <= 1)
		return a;
	//w = cos(x) + i * sin(x)
	// w_n = e^{(2pi/n)*i }
	Complex wn = std::polar(1.0, 2 * PI / n);
	Complex w = 1;

	// divide
	//even
	CArray a0 = a[std::slice(0, n / 2, 2)];
	//odd
	CArray a1 = a[std::slice(1, n / 2, 2)];

	// conquer
	CArray y0 = RECURSIVE_FFT(a0);
	CArray y1 = RECURSIVE_FFT(a1);

	CArray y(Complex(0), n);
	// combine
	for (size_t k = 0; k < n / 2; ++k)
	{
		y[k] = y0[k] + w * y1[k];
		y[k + n / 2] = y0[k] - w * y1[k];
		w = w * wn;
	}
	return y;
}
```
