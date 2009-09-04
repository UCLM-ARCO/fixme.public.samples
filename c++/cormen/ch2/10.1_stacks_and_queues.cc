#include <iostream>
#include <stack>
#include <queue>

using namespace std;

int
main()
{
	stack<string>  s;
	queue<string>  q;

	string str;
	while (cin >> str) {
		s.push(str); q.push(str);
	}

	while (!s.empty()) {
		cout << s.top() <<  " " << q.front() << endl;
		s.pop(); q.pop();
	}

	
}

