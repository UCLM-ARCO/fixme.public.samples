// -*- mode: c++ -*-

#include <boost/python.hpp>
#include "control.h"

using namespace boost::python;

IntRW global;

list
Wrap::all() {
  list retval;

  std::vector<A> aux =\
    _i.all();
  for(std::vector<A>::const_iterator it = aux.begin();
      it != aux.end(); ++it)
    retval.append(*it);

  return retval;
}


Wrap
wrap_factory() {
  return Wrap(global);
}

BOOST_PYTHON_MODULE(Control)
{
  class_<IntRW>("IntRW")
    .def("set", &IntRW::set)
    .def("get", &IntRW::get)
    .def("all", &IntRW::all)
    ;

  class_<Wrap>("Wrap",
	       init<IntRW>())
    .def("all", &Wrap::all)
    ;

  class_<A>("A", init<int>())
    .def("get", &A::get)
    ;

  def("wrap_factory", wrap_factory);
}

