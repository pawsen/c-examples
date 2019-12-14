// file Vector.cc:

module; // this compilation will define a module

// ... here we put stuff that Vector might need for its implementation ...

export module Vector; // defining the module called "Vector"

export class Vector {
public:
  Vector(int s);
  double &operator[](int i);
  int size() const;

private:
  double *elem; // elem points to an array of sz doubles
  int sz;
};

Vector::Vector(int s)
    : elem{new double[s]}, sz{s} // initialize members
{}

double &Vector::operator[](int i) { return elem[i]; }

int Vector::size() const { return sz; }

export int size(const Vector &v) { return v.size(); }

