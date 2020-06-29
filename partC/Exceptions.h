#ifndef HW3_EXCEPTION_H
#define HW3_EXCEPTION_H

#include <Auxiliaries.h>
#include <Character.h>

#include <iostream>
#include <string>
namespace mtm {

    class Exception : public std::exception {
       private:
        char* exception_class;

       public:
        Exception (const char* class_name) : exception_class (nullptr) {
            std::string tmp = "A gamerelated error has occurred:" + std::string (class_name);
            exception_class = new char (tmp.length() + 1);
            strcpy (exception_class, tmp.c_str());
        }
        ~Exception() {
            delete[] exception_class;
        }
        const char* what() const noexcept {
            return exception_class;
        }
    };

    class IllegalArgument : public Exception {
       public:
        IllegalArgument() : Exception ("IllegalArgument") {}
    };

    class GameException : public Exception {
    };
    
}  // namespace mtm

#endif  // HW3_EXCEPTION_H
