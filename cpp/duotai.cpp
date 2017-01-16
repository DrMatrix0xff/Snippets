#include <iostream>
#include <string>

class Person
{
public:
    Person(std::string name, int age) : _name(name), _age(age) {
        std::cout << "Person Constructor invoked." << std::endl;
    }
    std::string name() const { return _name; }
    int age() const { return _age; }
    void describe() {
        std::cout << _name << " is " << _age << " years old." << std::endl;
    }

protected:
    std::string _name;
    int _age;
};

class FootballPlayer : public Person
{
public:
    FootballPlayer(std::string name, int age, std::string club) : Person(name, age), _club(club) {
        std::cout << "FootballPlayer Constructor invoked." << std::endl;
    }
    void describe () {
        std::cout << _name << " is " << _age << " years old, now he is a football player of " << _club << "." << std::endl;
    }

private:
    std::string _club;
};

int main(int argc, char *argv[]) {
    FootballPlayer *p;
    p = new FootballPlayer("Henry", 26, "Arsenal Club");
    p->describe();
    Person *f = dynamic_cast<Person*>(p);
    // Person *f = static_cast<Person*>(p);
    f->describe();

    delete p;
    return 0;
}
