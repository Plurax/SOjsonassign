
#include <iostream>
#include <unistd.h>
#include <nlohmann/json.hpp>


class Base
{
  const string() { return str; }
  std::string str;
};


class Derived1 : public Base
{
  int myInt;
};


void to_json(json& j, const Base& p) {
  j = json{{"Derived1", p.myInt}};
}

void from_json(const json& j, person& p) {
  j.at("name").get_to(p.name);
  j.at("address").get_to(p.address);
  j.at("age").get_to(p.age);
}

int main(int argc, char* argv[]) {
  std::cout << "Hello World!" << std::endl;

  json myJ;
  myJ["D1"] = D1;

  
}
