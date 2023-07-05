#include <stdio.h>
#include <string.h>

struct human
{
    int age;
    char first_name[20];
    char last_name[20];
};

typedef struct human Human;

void update_struct(Human person, char fname[20], char lname[20])
{
    strcpy(person.first_name, fname);
    strcpy(person.last_name, lname);
    printf("Hello %s %s", person.first_name, person.last_name);
}

int main(void)
{
    Human person;
    person.age = 42;
    strcpy(person.first_name, "John");
    strcpy(person.last_name, "Doe");

    update_struct(person, "Timmy", "Blunt");
    printf("Hello %s %s", person.first_name, person.last_name);
    return 0;
}