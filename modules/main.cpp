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

#include <iostream>
import Vector;         // get Vector's interface
#include <cmath>       // get the standard-library math function interface including sqrt()

double sqrt_sum(Vector &v) {
  double sum = 0;
  for (int i = 0; i != v.size(); ++i)
    sum += std::sqrt(v[i]);
  return sum;
}

int main(int argc, char *argv[]) {
  Vector v(6);
  for (int i = 0; i != v.size(); ++i)
    v[i] = i;

  std::cout << sqrt_sum(v) << std::endl;
  return 0;
}
