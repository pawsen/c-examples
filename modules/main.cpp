/* HOW to compile with -std=c++2a
 *
 * 1. Precompile module-file into precompiled module (.pcm file)
 *    NOTE: pcm is not a object file. It is the equivalent of an old header
 *    file with high-level information on function declarations
 * 2. Compile *.cpp files and link them together
 *
 * If the cpp-file includes std-libraries, we need to include two extra flags:
 *   -fimplicit-modules -fimplicit-module-maps
 *
 * 1.
 *  clang++ -std=c++2a -c Vector.cpp -Xclang -emit-module-interface -o Vector.pcm
 * 2.
 *  clang++ -std=c++2a -fprebuilt-module-path=. main.cpp Vector.cpp
 *   or split the command
 *  clang++ -std=c++2a -fimplicit-module-maps -fprebuilt-module-path=. main.cpp -c
 *  clang++ -std=c++2a -fimplicit-modules -fimplicit-module-maps Vector.cpp -c
 *  clang++ -std=c++2a main.o Vector.o
 *
 * Or see the build2, the new c++ build chain
 * https://build2.org/
 *
 * For more on clang with modules
 * https://quuxplusone.github.io/blog/2019/11/07/modular-hello-world
 * https://quuxplusone.github.io/blog/2019/08/02/the-tough-guide-to-cpp-acronyms
 */
#include <numeric>     // std::iota
#include <stdexcept>   // std::out_of_range
#include <iostream>
#include <cmath>       // get the standard-library math function interface including sqrt()
#include <vector>
#include <assert.h>     /* assert */
#include <map>          // std::map
import Vector;         // get Vector's interface

double sqrt_sum(Vector &v) {
  double sum = 0;
  for (int i = 0; i != v.size(); ++i)
    sum += std::sqrt(v[i]);
  return sum;
}


int f(Vector& v) {
  // try to fill out-of-bound for array.
     try{ // exceptions here are handled by the handler defined below
          v[v.size()] = 7; // try to access beyond the end of v
          std::cout << "accessed out-of-bond error" << std::endl;
     } catch (std::out_of_range &err) { // oops: out_of_range error
       // ... handle range error ...
       std::cerr << err.what() << '\n';
     }
     return 0;
}

void user2(int sz) {
  Vector v(sz);
  std::iota(&v[0], &v[sz - 1], 1); // fill v with 1,2,3,4... (see §14.3)
  std::cout << "modify vector using for-range\n";
  for (auto &&x : v)
    x *= 10;
  for (const auto &x : v)
    std::cout << x << " ";
  std::cout << std::endl;
}

void user(int sz) noexcept {
  // convert exception into a terminate()
     Vector v(sz);
     std::iota(&v[0],&v[sz-1],1);     // fill v with 1,2,3,4... (see §14.3)
     std::cout << "noexcept convert exception into termination\n";
     for (const auto& x : v)
       std::cout << x << " ";
     std::cout << std::endl;
}

int sum(const std::vector<int>& v) {
     int s = 0;
     for (const int &i : v)
          s += i;
     return s;
}

void structured_bindings() {
  // show how to use structured bindings in the case of key, value pairs
  // https://stackoverflow.com/a/45481030
  std::map<int, int> m = {{ 0, 1 }, { 2, 3 }};
  for(const auto &[key, value]: m) {
    std::cout << key << ": " << value << std::endl;
  }
}

int main(int argc, char *argv[]) {
  Vector v(6);
  // could be filled using iota
  for (int i = 0; i != v.size(); ++i)
    v[i] = i;

  std::cout << sqrt_sum(v) << std::endl;
  f(v); // throw error
  user(6);
  user2(6);

  std::vector fib = {1,2,3,5,8,13,21};
  int x = sum(fib);
  assert(x == 53);
  std::cout << "fib sum " << x << std::endl;

  structured_bindings();
 
  return 0;
}
