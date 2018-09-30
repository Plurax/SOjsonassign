
#include <iostream>
#include <unistd.h>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class Base
{
 public:
  Base () :str("Hurray") { };
 private:
  // const std::string() { return str; }
  std::string str;
};


class Derived1 : public Base
{
 public:
  Derived1() { myInt = 1; };
 public:
  int myInt;
};


void to_json(json& j, const Derived1& p) {
  j = json{{"Derived1", p.myInt}};
}

void from_json(const json& j, Derived1& p) {
  j.at("name").get_to(p.myInt);
}

int main(int argc, char* argv[]) {

  json myJ;
  Derived1 D1;
  myJ["D1"] = D1;
  std::cout << "myJ: " << myJ.dump() << std::endl;

  std::shared_ptr<Base> pointer = std::make_shared<Derived1>();
  json DerivedJson;
  //  DerivedJson["D1"] = *pointer;
  //  std::cout << "myJ" << DerivedJson.dump() << std::endl;
}
