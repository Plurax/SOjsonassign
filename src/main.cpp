#include <iostream>
#include <unistd.h>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class Base
{
  public:
    Base () :str("Hurray") { };
    virtual json tojson() const = 0;
    std::string str;
};

class Derived1;
void to_json(json& j, const Derived1& p);

class Derived1 : public Base
{
  public:
    Derived1() { myInt = 1; };
    json tojson() const
    {
        json j;
        ::to_json(j, *this);
        return j;
    }
  public:
    int myInt;
};


class Derived2 : public Base
{
  public:
    Derived2() { myInt = 5; };
    json tojson() const
    {
        json j = myInt;
        return j;
    }
    operator int() const {return myInt; };
  public:
    int myInt;
};


void to_json(json& j, const Derived1& p) {
    j = json{{"Derived1", p.myInt}};
}

void from_json(const json& j, Derived1& p) {
    j.at("name").get_to(p.myInt);
}



void to_json(json& j, const Base& p) {
    j = json{{"Base", p.str}};
}

void from_json(const json& j, Base& p) {
    j.at("Base").get_to(p.str);
}



int main(int argc, char* argv[]) {

    json myJ;
    Derived1 D1;
    myJ["D1"] = D1;
    std::cout << "Direct assignment calls to_json: " << myJ.dump() << std::endl;

    std::shared_ptr<Base> pointerD1 = std::make_shared<Derived1>();
    json DerivedJson;
    DerivedJson["D1"] = pointerD1->tojson();
    std::cout << "Assignment via pointer:" << DerivedJson.dump() << std::endl  << std::endl;

    json replace;
    std::cout << "Replace existing string with D2 (int): " << std::endl;
    replace["rep"] = "replaceMe";
    std::cout << "Before: " << replace.dump() << std::endl;

    std::shared_ptr<Base> pointerD2 = std::make_shared<Derived2>();
    replace["rep"] = pointerD2->tojson();;
    std::cout << "After: " << replace.dump() << std::endl;
}
