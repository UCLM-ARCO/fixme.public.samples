#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

class A {
public:
	friend int operator <(const A& a, const A& b);
	friend ostream& operator <<(ostream& os, const A& a);
	friend class less_than;
	A(int i) : _i(i) {}
private:
	int _i;
};

int operator <(const A& a, const A& b)
{
	return a._i < b._i;
}

ostream& operator <<(ostream& os, const A& a)
{
	return os << a._i;
}

struct less_than {
	int operator() (const A& a, const A& b) {
		return b._i < a._i;
	}
};

int main()
{
	vector<A> v;
	v.push_back(3);
	v.push_back(2);
	v.push_back(1);

	sort(v.begin(), v.end());
	copy(v.begin(), v.end(), ostream_iterator<A>(cout, "\n"));

	sort(v.begin(), v.end(), less_than());
	copy(v.begin(), v.end(), ostream_iterator<A>(cout, "\n"));
}

