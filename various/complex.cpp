#include <iostream>
using namespace std;

class complex {
  double re, im; // representation: two doubles
public:
  complex(double r, double i)
      : re{r}, im{i} {}               // construct complex from two scalars
  complex(double r) : re{r}, im{0} {} // construct complex from one scalar
  complex() : re{0}, im{0} {}         // default complex: {0,0}

  // the member functions of a const object can only be called if they
  // themselves are specified as const members
  // Thus if we declare: const complex z = {1,2}; real, imag, print,
  // must be declared as const member functions
  double real() const { return re; }
  void real(double d) { re = d; } // set real value
  double imag() const { return im; }
  void imag(double d) { im = d; }
  void print() const {
    int img = im < 0 ? -im : im;
    std::cout << re << (im < 0 ? " - ": " + ")  << "i" << img  << std::endl;
  }

  complex &operator+=(complex z) {
    re += z.re; // add to re and im
    im += z.im;
    return *this; // and return the result
  };

  complex &operator-=(complex z) {
    re -= z.re;
    im -= z.im;
    return *this;
  }

  complex &operator*=(complex z){
    re = re*z.re - im*z.im;
    im = re*z.im + im*z.re;
    return *this;
  }

  complex &operator/=(complex z){
    double denum = z.re*z.re + z.im*z.im;
    re = (re*z.re + im*z.im) / denum;
    im = (im*z.re - re*z.im) / denum;
    return *this;
  }
};

// friend functions:
// Many useful operations do not require direct access to the representation of
// complex, so they can be defined separately from the class definition:
// Here, I use the fact that an argument passed by value is copied so that I can
// modify an argument without affecting the caller’s copy and use the result as
// the return value.
complex operator+(complex a, complex b) { return a += b; }
complex operator-(complex a, complex b) { return a -= b; }
complex operator-(complex a) { return {-a.real(), -a.imag()}; } // unary minus
complex operator*(complex a, complex b) { return a *= b; }
complex operator/(complex a, complex b) { return a /= b; }

// equal
bool operator==(complex a, complex b) {
  return a.real() == b.real() && a.imag() == b.imag();
}

// not equal
bool operator!=(complex a, complex b) { return !(a == b); }

complex sqrt(complex); // the definition is elsewhere

complex f(complex z) {
  complex a = {2.3}; // construct {2.3,0.0} from 2.3
  complex b = {1 / a};
  complex c = {a + z * complex{1, 2.3}};

  if (c != b)
    c = -(b / a) + 2 * b;
  return c;
}


int main(int argc, char *argv[]) {
  complex c = {1, 2};
  c.print();
  c.real(10);
  c.imag(100);
  c.print();

  const complex c1 = {1,2};
  cout << c1.real() << endl;
  c1.print();

  complex z = f(c);
  z.print();

  complex z1{1,2}, z2{2,3};
  complex z3 = z1*z2;
  complex z4 = z1/z2;
  z3.print();
  z4.print();

  return 0;
}
