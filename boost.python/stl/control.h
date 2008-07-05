#include <vector>
#include <map>

using namespace std;

typedef vector<string> VectorInt;
typedef map<string,string> MapDict;

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

    VectorInt all() {
        VectorInt retval;
	retval.push_back("one");
	retval.push_back("two");
        return retval;
    }

    MapDict refs() {
        MapDict retval;
        retval["foo"] = "hello";
        retval["bar"] = "bye";
        return retval;
    }
};
