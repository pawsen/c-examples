/*
   Note the difference between uniform{} and direct() initialization
   For uniform initialization, the following rules are observed
   - If there is an initializer_list constructor of the appropriate type, that
     constructor is used
   - Otherwise the class elements are initialized using the appropriate
     constructor

   Thus when we have initializer_list constructor,
     Vector v1{5}
   results in v1 == 5 instead of v1 == [0,0,0,0,0]
   eg:
   Vector v1(5) // creates an empty vector of size 8, using the int constructor
   Vector v1{5} // creates a one-element vector with data value 8, using the
                   initializer_list constructor

   This happens because the initializer_list constructor takes precedence over
   other constructors when doing uniform initialization.

   https://www.learncpp.com/cpp-tutorial/b-4-initializer-lists-and-uniform-initialization/
 */

#include <algorithm> // std::copy
#include <initializer_list>
#include <iostream>
#include <list>      // std::list
#include <numeric>   // std::iota
#include <stdexcept> // std::out_of_range

// concrete type
class Vector {
public:
  // default constructor. Necessary to init elem-ptr due to the destructor
  Vector() : elem{new double} {};
  // NOTE: ptr values are not zero-initialized by default.
  Vector(int s) : elem{new double[s]}, sz{s} {
    for (auto &v : *this)
      v = 0;
  }
  // either use std::copy or homemade population of array.
  // the standard-library uses unsigned integers for sizes and subscripts, so I
  // need to use the ugly static_cast to explicitly convert the size of the
  // initializer list to an int.
  Vector(std::initializer_list<double> lst)
      : elem{new double[lst.size()]}, sz{static_cast<int>(lst.size())} {
    // std::copy(lst.begin(),lst.end(),elem);
    int i = 0;
    for (const auto &l : lst) {
      elem[i] = l;
      ++i;
    }
  }
  ~Vector() { delete[] elem; }

  double &operator[](int i) {
    if (i < 0 || size() <= i)
      throw std::out_of_range{"Vector::operator[]"};
    return elem[i];
  }

  int size() const { return sz; }
  void print() const {
    for (const auto &n : *this)
      std::cout << n << ' ';
    std::cout << std::endl;
  }

  // for range-based for loop
  double *begin() const { return sz > 0 ? &elem[0] : nullptr; }
  double *end() const { return sz > 0 ? &elem[sz] : nullptr; }

private:
  double *elem; // elem points to an array of sz doubles
  int sz;
};

// abstract type
// defines interface to class and no implementation
class Container {
public:
  virtual double &operator[](int) = 0; // pure virtual function
  virtual int size() const = 0;        // const member function (§4.2.1)
  virtual ~Container() {}              // destructor (§4.2.2)
};

// Vector_container implements Container
class Vector_container : public Container {
public:
  Vector_container(int s) : v(s) {} // Vector of s elements
  // NOTE member destructor (~Vector()) is implicitly invoked by its class’s
  // destructor (~Vector_container()). »
  ~Vector_container() {}

  double &operator[](int i) override { return v[i]; }
  int size() const override { return v.size(); }

private:
  Vector v;
};

class List_container : public Container { // List_container implements Container
public:
  List_container() {} // empty List
  List_container(std::initializer_list<double> il) : ld{il} {}
  ~List_container() {}
  double &operator[](int i) override;
  int size() const override { return ld.size(); }

private:
  std::list<double> ld; // (standard-library) list of doubles (§11.3)
};

double &List_container::operator[](int i) {
  for (auto &x : ld) {
    if (i == 0)
      return x;
    --i;
  }
  throw std::out_of_range{"List container"};
}

void use(Container &c) {
  const int sz = c.size();

  for (int i = 0; i != sz; ++i)
    std::cout << c[i] << " ";
  std::cout << '\n';
}

void g() {
  Vector_container vc(10); // Vector of ten elements
  std::iota(&vc[0], &vc[9], -1);
  use(vc);
}

void h() {
  List_container lc = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  use(lc);
}

void fct(int n) {
  Vector v(n);
  {
    Vector v2(2 * n);
    v2.print();
  } // v2 is destroyed here
    // ... use v ..
} // v is destroyed here »

int main(int argc, char *argv[]) {

  fct(5);

  Vector v1 = 5;
  v1.print();

  Vector v2{5};
  v2.print();

  Vector v3(5);
  // could be filled using iota
  for (int i = 0; i != v3.size(); ++i)
    v3[i] = i;
  v3.print();

  int i = 10;
  Vector v4(5);
  for (auto &v : v4) {
    v = i;
    ++i;
  }
  v4.print();

  Vector v5{1, 2, 3, 4, 5};
  v5.print();

  g();
  h();

  return 0;
}
