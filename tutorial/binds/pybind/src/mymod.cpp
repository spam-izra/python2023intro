#include <pybind11/iostream.h>
#include <pybind11/smart_holder.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <pybind11/operators.h>
//-----------------------------------------------------------------------------
#include <cmath>
//-----------------------------------------------------------------------------
namespace py = pybind11;
//-----------------------------------------------------------------------------
double my_sqr_func(const double value) {
    return value * value;
}
//-----------------------------------------------------------------------------
class MyObject {
    private:
        double _power;
    public:
        double attr;

        MyObject(double power)
            :_power(power), attr(-1) {}

        double power() const {
            return _power;
        }

        double calculate(const double value) {
            return std::pow(value, _power);
        }

        double operator()(const double value) {
            return calculate(value);
        }
};

class MySharedObject: public MyObject {
    public:
        using MyObject::MyObject;
};

//-----------------------------------------------------------------------------
PYBIND11_MODULE(mymod, m) {
    m.doc() = "Documentation for my modele";

    // Глобальные переменные модуля
    m.attr("MY_STR") = "Hello World";

    py::class_<MyObject>(m, "MyObject", "Объект для возведения в степерь")
        // .def(py::init<const double>(), py::arg("power"))
        .def(py::init(
            [](const double power) {
                return MyObject(power);
            }), py::arg("power"))
        .def("__repr__",
             [](const MyObject &self) {
                 std::stringstream ss;
                 ss << "MyObject(power=" << self.power() << ")";
                 return ss.str();
             })
        .def_readwrite("attr", &MyObject::attr, "Бесполезная переменная")
        //.def_readonly("attr", &MyObject::attr, "Бесполезная переменная")
        .def_property_readonly("power", &MyObject::power)
        .def("__call__", &MyObject::operator())
        .def("calculate", &MyObject::calculate);

    py::class_<MySharedObject, MyObject>(m, "MySharedObject", "Объект в умном указателе")
        .def(py::init([](const double power) { return MySharedObject(power); }));


    py::module_ sub = m.def_submodule("utility", "Подмодуль");
    sub.def("my_sqr", &my_sqr_func,
            "Считает квадрат числа", py::arg("value"));
}
