#include <iostream>
#include <string>

struct sPerson {
  std::string name;
  int age;
};

class Person {
 public:
  Person(std::string, int);
  void print() const;

 private:
  std::string name_;
  int age_ = 5;
};

// Person::Person(std::string name, int age) {
//   name_ = name;
//   age_ = age;
// }
Person::Person(std::string name = "", int age = 0) : name_(name), age_(age) {}

void Person::print() const {
  std::cout << name_ << ": " << age_ << std::endl;
}

int main() {
  // struct version
  sPerson a;
  sPerson b;
  a.name = "Calvin";
  b.name = "Hobbes";
  a.age = 30;
  b.age = 20;
  std::cout << a.name << ": " << a.age << std::endl;
  std::cout << b.name << ": " << b.age << std::endl;

  // class version
  Person r("Wales", 40);
  r.print();
  Person r2("Test");
  r2.print();
}
