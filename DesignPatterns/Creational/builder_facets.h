//
//  builder_facets.h
//  DesignPatterns
//
//  Created by iKan on 16/07/22.
//

#ifndef builder_facets_h
#define builder_facets_h

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <ostream>

// Person.h
namespace Builder {
  class PersonBuilder;
  class Person {
  private:
    // address
    std::string street_add, post_code, city;
    
    // employment
    std::string company_name, position;
    int anual_income = 0;
    
  public:
    static PersonBuilder create();
    
    friend class PersonBuilder;
    friend class PersonJobBuilder;
    friend class PersonAddressBuilder;
  };
  
  // PersonBuilder.h
  class PersonAddressBuilder;
  class PersonJobBuilder;
  class PersonBaseBuilder {
  protected:
    Person& p;
  public:
    PersonBaseBuilder(Person& p) : p(p) {}
    
    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;
  };

  class PersonBuilder : public PersonBaseBuilder {
  private:
    Person p;
  public:
    PersonBuilder() : PersonBaseBuilder(p) {}
  };
  
  class PersonAddressBuilder : public PersonBaseBuilder {
  public:
    typedef PersonAddressBuilder Self;
    PersonAddressBuilder(Person& p) : PersonBaseBuilder(p) {}
    
    Self& at(const std::string& sa) {
      p.street_add = sa;
      return *this;
    }
    Self& with_post_code(const std::string& pc) {
      p.post_code = pc;
      return *this;
    }
    Self& in(const std::string& city) {
      p.city = city;
      return *this;
    }
  };
  
  class PersonJobBuilder : public PersonBaseBuilder{
  public:
    typedef PersonJobBuilder Self;
    PersonJobBuilder(Person& p) : PersonBaseBuilder(p) {}
    
    Self& at(const std::string& cn) {
      p.company_name = cn;
      return *this;
    }
    Self& as_a(const std::string& pos) {
      p.position = pos;
      return *this;
    }
    Self& earning(int sal) {
      p.anual_income = sal;
      return *this;
    }
  };
  
  // Implementaition
  PersonBuilder Person::create() {
    return PersonBuilder();
  }
  
  PersonAddressBuilder PersonBaseBuilder::lives() const{
    return PersonAddressBuilder{p};
  }
  PersonJobBuilder PersonBaseBuilder::works() const {
    return PersonJobBuilder{p};
  }

  
}
#endif /* builder_facets_h */
