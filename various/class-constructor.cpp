#include <iostream>
using namespace std;

class point {
public:
  // default Constructor & Non-default Constructor with initialization list
  point () {};
  point (double px, double py) : x(px), y(py) {}
  double x, y;
};

int main(void) {
  // Define an array of size 10 & of type point
  // we need a default constructor for this
    point a[10];
    a[0].x = 1;
    a[0].y = 2;

    double &p = a->x;
    cout << p << endl;

    // parameterized constructor
  point b = point(5, 6);

  cout << a->x << ", " << a->y << endl;
  cout << b.x << ", " << b.y << endl;

}
