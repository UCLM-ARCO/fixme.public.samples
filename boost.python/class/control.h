#include <vector>

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

    std::vector<int> all() {
        std::vector<int> a;
	a.push_back(10);
	a.push_back(20);
        return a;
    }
};
