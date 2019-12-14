/* Compile with
 * clang++ -o student-class.out student-class.cpp
 */

#if !defined(STUDENT_CLASS)
#define STUDENT_CLASS 1.0.2

#include <algorithm>
#include <ostream>
#include <stdexcept>
#include <string>
#include <list>
#include <typeinfo>

namespace sc {

class school_class {
    typedef std::list<std::string>::const_iterator student;
public:

    virtual ~school_class() {}
    bool empty() const throw();
    void add_student(const std::string &newbie) throw();
    void expel_student(const std::string &bad_boy)
        throw(std::invalid_argument);
    bool find_student(const std::string &some_one) const throw();

    operator bool() const throw();
    friend std::ostream&
        operator <<(std::ostream &out, const school_class &c) throw();

protected:
    virtual void list_students(std::ostream &out) const throw();

private:
    std::list<std::string> student_list;
};

inline
bool school_class::empty() const throw()
{ return student_list.empty(); }

inline
void school_class::add_student(const std::string &newbie) throw()
{ student_list.push_back(newbie); }

inline
void school_class::expel_student(const std::string &bad_boy)
throw(std::invalid_argument)
{
    if (find_student(bad_boy)) student_list.remove(bad_boy);
    else throw std::invalid_argument("no such student [" + bad_boy + "]");
}

inline
bool school_class::find_student(const std::string &some_one) const throw()
{ return std::count(student_list.begin(), student_list.end(), some_one) != 0; }

inline
void school_class::list_students(std::ostream &out) const throw()
{
    out<<std::endl<<std::string(5, '-')<<"[students in the class]"
        <<std::string(5, '-')<<std::endl;
    for (student some_one = student_list.begin();
         some_one != student_list.end();
         ++some_one)
        out<<*some_one<<std::endl;
    out<<std::string(8 , '-')<<"[end of the list]"
        <<std::string(8, '-')<<std::endl;
}

inline
school_class::operator bool() const throw()
{ return !empty(); }

inline
std::ostream&
operator <<(std::ostream &out, const school_class &c) throw()
{ c.list_students(out); return out; }

} // namespace sc

#endif // STUDENT_CLASS 1.0.2

#include <iostream>
using std::cout;        using std::cerr;
using std::endl;        using std::cin;
using std::getline;     using std::string;
using std::exception;   using std::invalid_argument;
using namespace sc;

int main()
{
    school_class my_class;
    string name;
    while (cout<<"enter student : ", getline(cin, name) && !name.empty())
        my_class.add_student(name);
    while (my_class) {
        cout<<my_class
            <<"enter the name of the student to be kicked out: "<<endl;
        getline(cin, name);
        if (name.empty()) break;
        try {
            my_class.expel_student(name);
            cout<<name<<" is out."<<endl;
        }
        catch (exception &e) {
            if (typeid(e) == typeid(invalid_argument))
                cerr<<"hey man, be careful!"<<endl;
            cerr<<"exception ["<<typeid(e).name()<<"]: "<<e.what()<<endl;
        }
    }
    cout<<endl<<"bye."<<endl;
    return 0;
}
