#include <sstream>

using namespace std;

string itos(int n) {
	stringstream s;
	s<<n;
	return s.str();
}

int main() {
	int n = -15;

	for (int i=0; i<10000; ++i) {
		itos(n);
	}
}

