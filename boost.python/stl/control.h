#include <vector>
#include <map>

using namespace std;

class IntRW {
private:
    int _state;

public:
    void set(int value) {
        _state = value;
    }

    int get() {
        return _state;
    }

    vector<string> all() {
        vector<string> retval;
	retval.push_back("one");
	retval.push_back("two");
        return retval;
    }

    map<string,string> refs() {
        map<string,string> retval;
        retval["foo"] = "hello";
        retval["bar"] = "bye";
        return retval;
    }
};
