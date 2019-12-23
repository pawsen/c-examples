/* copy constructor: deep copy

   The default constructors does not handle pointers to memory as we want (ie.
   they do shallow copy/movement, copying the value of the pointer, not the
   content they point to.)
   This example shows how to do deep copy/move, ie. copy the content the pointer
   administers. We also need a custom delete operator, the default only
   deletes the pointer.

   Illustration of which constructors are being called
   MyClass fn();            // function returning a MyClass object
   MyClass foo;             // default constructor
   MyClass bar (foo);       // object initialization: copy constructor called
   MyClass bar = foo;       // object initialization: copy constructor called
   MyClass baz = fn();      // move constructor
   foo = bar;               // object already initialized: copy assignment called
   baz = MyClass();         // move assignment

   http://www.cplusplus.com/doc/tutorial/classes2/#copy_assignment
*/

#include <iostream>
#include <string>
using namespace std;

class Example5 {
  string *ptr;

public:
  Example5() : ptr(new string) {}
  Example5(const string &str) : ptr(new string(str)) {}
  ~Example5() { delete ptr; }

  // copy constructor:
  Example5(const Example5 &x) : ptr(new string(x.content())) {}
  // copy assignment
  Example5 &operator=(const Example5 &x) {
    delete ptr;                    // delete currently pointed string
    ptr = new string(x.content()); // allocate space for new string, and copy
    return *this;
  }
  // Or even better, since its string member is not constant, it could
  // re-utilize the same string object:
  /*
  Example5& operator= (const Example5& x) {
    *ptr = x.content();
    return *this;
  }
  */

  // move constructor
  Example5(Example5 &&x) : ptr(x.ptr) { x.ptr = nullptr; }
  // move assignment
  Example5 &operator=(Example5 &&x) {
    delete ptr;
    ptr = x.ptr;
    x.ptr = nullptr;
    return *this;
  }

  // access content:
  const string &content() const { return *ptr; }
  // addition:
  Example5 operator+(const Example5 &rhs) {
    return Example5(content() + rhs.content());
  }
};

int main() {
  Example5 boo;
  Example5 foo("example");
  Example5 bar = foo;           // object initialization: copy constructor called
  Example5 baz {foo};           // object initialization: copy constructor called
  foo = bar;                    // object already initialized: copy assignment called

  Example5 foo2 ("Exam");
  Example5 bar2 = Example5("ple");   // move-construction
  foo2 = foo2 + bar2;                // move-assignment

  cout << "bar's content: " << bar.content() << '\n';
  cout << "baz's content: " << baz.content() << '\n';
  cout << "foo2's content: " << foo2.content() << '\n';
  return 0;
}
