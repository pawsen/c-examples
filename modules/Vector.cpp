module; // this compilation will define a module

// ... here we put stuff that Vector might need for its implementation ...
#include <stdexcept> // std::out_of_range

export module Vector; // defining the module called "Vector"

export class Vector {
public:
  Vector(int s);
  double &operator[](int i);
  int size() const;
  // for range-based for loop
  double *begin();
  double *end();

private:
  double *elem; // elem points to an array of sz doubles
  int sz;
};

Vector::Vector(int s)
    : elem{new double[s]}, sz{s} // initialize members
{}

double &Vector::operator[](int i) {
  if (i < 0 || size() <= i)
    throw std::out_of_range{"Vector::operator[]"};
  return elem[i];
}

double *Vector::begin() { return &elem[0]; }
double *Vector::end() { return &elem[sz]; }

int Vector::size() const { return sz; }

export int size(const Vector &v) { return v.size(); }
