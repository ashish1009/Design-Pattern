//
//  dependency_inversion_p.h
//  DesignPatterns
//
//  Created by iKan on 16/07/22.
//

#ifndef dependency_inversion_p_h
#define dependency_inversion_p_h

#include <iostream>
#include <vector>
#include <tuple>

/*
 Defination :
 A. High-level module should not depend on low-level modules
    Both should depend on abstraction.
 B. Abstraction should not depend on details
    Detauls should depend on abstraction.
 */

/*
 Example :
 */
enum class Relationship {
  parent, child, sibling
};

struct Person {
  std::string name;
};
struct Relationships { // low- level module as this is data storage
  std::vector<std::tuple<Person, Relationship, Person>> relations;
  
  void add_parent_and_child(const Person& p, const Person& c) {
    relations.push_back({p, Relationship::parent, c});
    relations.push_back({c, Relationship::child, p});
  }
};

/*
 TODO: PROBLEM
 As this hlm depending on llm
 if ever low level module decide to change or hide its member
 high level module breaks
 */
struct Research { // High level as accessing element
  Research(const Relationships& r) {
    auto& rel = r.relations;
    for (auto&& [first, rr, second] : rel) {
      if (first.name == "John" && rr == Relationship::parent)
        std::cout << "John has a child called " << second.name << std::endl;
    }
  }
};

/*
 SOLUTION:
 */
struct RelationshipBrowser {
  virtual std::vector<Person> find_all_children_of(const std::string& p) = 0;
};

struct Better_low_level_Relationships : RelationshipBrowser { // low- level module as this is data storage
  std::vector<std::tuple<Person, Relationship, Person>> relations;
  
  void add_parent_and_child(const Person& p, const Person& c) {
    relations.push_back({p, Relationship::parent, c});
    relations.push_back({c, Relationship::child, p});
  }
  
  std::vector<Person> find_all_children_of(const std::string& p) override {
    std::vector<Person> result;
    for (auto&& [first, rr, second] : relations) {
      if (first.name == p && rr == Relationship::parent)
        result.push_back(second);
    }
    return result;
  }
};

struct Better_Research { // High level as accessing element
  Better_Research(RelationshipBrowser& rb) {
    for (auto c : rb.find_all_children_of("John"))
      std::cout << "John has a child called " << c.name << std::endl;
  }
};


#endif /* dependency_inversion_p_h */
