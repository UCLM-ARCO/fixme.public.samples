#include <iostream>
#include <set>

using namespace std;

int
main()
{
	set<string> sorted;
	string str;

	while (!cin.eof()) {
		cin >> str;
		sorted.insert(str);
	}

	for (set<string>::const_iterator i = sorted.begin(); 
	     i != sorted.end(); ++i)
		cout << *i << endl;
}

