#include <boost/python.hpp>
#include "control.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(Control)
{
    class_<IntRW>("IntRW")
        .def("set", &IntRW::set)
        .def("get", &IntRW::get)
        .def("all", &IntRW::all)
    ;
}
