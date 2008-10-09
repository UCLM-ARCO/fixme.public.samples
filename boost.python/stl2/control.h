// -*- mode: c++ -*-
#include <vector>
#include <boost/python.hpp>

class A {
  int _b;
public:
  A(int n):_b(n){};
  int get() {
    return _b;
  }
};

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

    std::vector<A> all() const {
        std::vector<A> retval;
	retval.push_back(A(10));
	retval.push_back(A(20));
        return retval;
    }
};



class Wrap {
private:
  const IntRW& _i;

public:
  Wrap(const IntRW& i) : _i(i) {}
  boost::python::list all();
};
