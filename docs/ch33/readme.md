# 33 Computational Geometry

```cpp
struct point
{
	ll x;
	ll y;
	ll operator*(const point &p1)
	{
		return (x * p1.y) - (p1.x * y);
	}
	point operator-(const point &p1)
	{
		return { x - p1.x, y - p1.y };
	}
};
```

# 33.1 Line-segment properties


```cpp
ll DIRECTION(point pi, point pj, point pk)
{
	return (pk - pi) * (pj - pi);
}

bool ON_SEGMENT(const point &pi, const point& pj, const point& pk)
{
	return (min(pi.x, pj.x) <= pk.x && pk.x <= max(pi.x, pj.x)) && 
		(min(pi.y, pj.y) <= pk.y && pk.y <= max(pi.y, pj.y));
}


bool SEGMENTS_INTERSECT(const point &p1, const point& p2, const point& p3, const point& p4)
{
	ll d1 = DIRECTION(p3, p4, p1);
	ll d2 = DIRECTION(p3, p4, p2);
	ll d3 = DIRECTION(p1, p2, p3);
	ll d4 = DIRECTION(p1, p2, p4);
	if (
		((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && 
		((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))
		)
	{
		return true;
	}
	else if (d1 == 0 && ON_SEGMENT(p3, p4, p1))
	{
		return true;
	}
	else if (d2 == 0 && ON_SEGMENT(p3, p4, p2))
	{
		return true;
	}
	else if (d3 == 0 && ON_SEGMENT(p1, p2, p3))
	{
		return true;
	}
	else if (d4 == 0 && ON_SEGMENT(p1, p2, p4))
	{
		return true;
	}
	else
	{
		return false;
	}
}
```


# 33.2 Determining whether any pair of segments intersects

# 33.3 Finding the convex hull

$O(n\log n)$

```cpp
point p0;

bool sorty(const point& a, const point& b)
{
	if (a.y != b.y)
	{
		return a.y < b.y;
	}
	return a.x < b.x;
}

bool sortCounterClockWise(const point& p1, const point& p2) {
	double result = DIRECTION(p0, p1, p2);
	if (result != 0)
	{
		return result < 0;
	}
	return sorty(p1, p2);
}

stack<point> GRAHAM_SCAN(vector<point> &Q)
{
	sort(Q.begin(), Q.end(), sorty);
	p0 = Q[0];
	sort(Q.begin() + 1, Q.end(), sortCounterClockWise);
	stack<point> st;
	if (Q.size() < 2)
		return st;

	st.push(Q[0]);
	st.push(Q[1]);

	for (int i = 2; i < Q.size(); i++)
	{
		while (st.size() >= 2)
		{
			point v2 = st.top();
			st.pop();
			point v3 = st.top();

			if (DIRECTION(v3, v2, Q[i]) < 0)
			{
				st.push(v2);
				break;
			}
		}
		st.push(Q[i]);
	}
	return st;
}
```


# 33.4 Finding the closest pair of points
