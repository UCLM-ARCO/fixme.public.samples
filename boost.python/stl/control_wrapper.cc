// -*- coding: utf-8 -*-
#include <boost/python.hpp>
#include "control.h"


// STL containers from http://wiki.python.org/moin/boost.python
using namespace boost::python;

template<class Key, class Val>
struct map_item {
    typedef std::map<Key,Val> Map;

    static Val& get(Map& self, Key const& idx) {
      if (self.find(idx) != self.end()) return self[idx];
      PyErr_SetString(PyExc_KeyError,"Map key not found");
      throw_error_already_set();
    }

    static void set(Map& self, const Key idx, const Val val) { self[idx]=val; }

    static void del(Map& self, const Key n) { self.erase(n); }

    static bool in(Map const& self, const Key n) { return self.find(n) != self.end(); }

    static list keys(Map const& self) {
        list t;
        for (typename Map::const_iterator it=self.begin(); it!=self.end(); ++it)
            t.append(it->first);
        return t;
    }
    static list values(Map const& self) {
        list t;
        for (typename Map::const_iterator it=self.begin(); it!=self.end(); ++it)
            t.append(it->second);
        return t;
    }
    static list items(Map const& self) {
        list t;
        for (typename Map::const_iterator it=self.begin(); it!=self.end(); ++it)
            t.append(make_tuple(it->first, it->second));
        return t;
    }
};


void IndexError() {
  PyErr_SetString(PyExc_IndexError, "Index out of range");
  throw_error_already_set();
}

template<class T>
struct vector_item {

    typedef vector<T> Vector;

    static T& get(Vector& self, int i) {
        if( i<0 ) i+=self.size();
        if( i>=0 && i<self.size() )
	  return self[i];
        IndexError();
    }
    static void set(Vector& self, int i, T const& v) {
        if( i<0 ) i+=self.size();
        if( i>=0 && i<self.size() ) {
	  //x[i]=v;
	  typename Vector::iterator it = self.begin() + i;
	  self.erase(it);
	  self.insert(it, v);
	}
        else IndexError();
    }
    static void del(Vector& self, int i) {
        if( i<0 ) i+=self.size();
        if( i>=0 && i<self.size() ) {
	  typename Vector::iterator it = self.begin() + i;
	  self.erase(it);
	}
        else IndexError();
    }
    static void add(Vector& self, T const& v) {
        self.push_back(v);
    }
};


typedef vector<string> VectorStr;
typedef map<string,string> MapDict;


BOOST_PYTHON_MODULE(Control)
{
  class_<VectorStr>("VectorStr")
    .def("__len__", &VectorStr::size)
    .def("clear", &VectorStr::clear)
    .def("append", &vector_item<string>::add, with_custodian_and_ward<1,2>()) // to let container keep value
    .def("__getitem__", &vector_item<string>::get, return_value_policy<copy_non_const_reference>())
    .def("__setitem__", &vector_item<string>::set, with_custodian_and_ward<1,2>()) // to let container keep value
    .def("__delitem__", &vector_item<string>::del)
    ;

  class_<MapDict>("MapDict")
    .def("__len__", &MapDict::size)
    .def("__getitem__", &map_item<string,string>::get, return_value_policy<copy_non_const_reference>())
    .def("__setitem__", &map_item<string,string>::set)
    .def("__delitem__", &map_item<string,string>::del)
    .def("clear", &MapDict::clear)
    .def("__contains__", &map_item<string,string>::in)
    .def("has_key", &map_item<string,string>::in)
    .def("keys", &map_item<string,string>::keys)
    .def("values", &map_item<string,string>::values)
    .def("items", &map_item<string,string>::items)
    ;

  class_<IntRW>("IntRW")
    .def("set", &IntRW::set)
    .def("get", &IntRW::get)
    .def("all", &IntRW::all)
    .def("refs", &IntRW::refs)
    ;
}
