#ifndef LAB3_PERSON_H
#define LAB3_PERSON_H

#include <ctime>

struct PersonID {
    int id;
};

class Person {
private:
    PersonID id;
    char *firstName;
    char *middleName;
    char *lastName;
    time_t birthDate;

public:
    PersonID GetID() {
        return id;
    };
    char *GetFirstName() {
        return firstName;
    };
    char *GetMiddleName() {
        return middleName;
    };
    char *GetLastName() {
        return lastName;
    };
};
#endif //LAB3_PERSON_H
