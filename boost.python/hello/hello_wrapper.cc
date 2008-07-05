#include <boost/python.hpp>

std::string hello();

using namespace boost::python;

BOOST_PYTHON_MODULE(Hello) {
    def("hello", hello);
}
