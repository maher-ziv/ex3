#ifndef HW3_EXCEPTION_H
#define HW3_EXCEPTION_H

#include <Auxiliaries.h>
#include <Character.h>

#include <iostream>
#include <string>
namespace mtm {

    class Exception : public std::exception {};

    class IllegalArgument : public Exception {
       public:
        const char* what() const noexcept override {
            return "A game related error has occurred: IllegalArgument";
        }
    };
    class IllegalCell : public Exception {
       public:
        const char* what() const noexcept override {
            return "A game related error has occurred: IllegalCell";
        }
    };
    class CellEmpty : public Exception {
       public:
        const char* what() const noexcept override {
            return "A game related error has occurred: CellEmpty";
        }
    };
    class MoveTooFar : public Exception {
       public:
        const char* what() const noexcept override {
            return "A game related error has occurred: MoveTooFar";
        }
    };
    class CellOccupied : public Exception {
       public:
        const char* what() const noexcept override {
            return "A game related error has occurred: CellOccupied";
        }
    };
    class OutOfRange : public Exception {
       public:
        const char* what() const noexcept override {
            return "A game related error has occurred: OutOfRange";
        }
    };
    class OutOfAmmo : public Exception {
       public:
        const char* what() const noexcept override {
            return "A game related error has occurred: OutOfAmmo";
        }
    };
    class IllegalTarget : public Exception {
       public:
        const char* what() const noexcept override {
            return "A game related error has occurred: IllegalTarget";
        }
    };

    class GameException : public Exception {};

}  // namespace mtm

/*
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
*/
#endif  // HW3_EXCEPTION_H
