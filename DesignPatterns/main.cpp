//
//  main.cpp
//  DesignPatterns
//
//  Created by iKan on 16/07/22.
//

#include <iostream>
#include <sstream>

#include "SOLID_Design_Principles/single_responsibility_p.h"
#include "SOLID_Design_Principles/open_close_p.h"
#include "SOLID_Design_Principles/liskov_substitutaion_p.h"
#include "SOLID_Design_Principles/interface_segregation_p.h"
#include "SOLID_Design_Principles/dependency_inversion_p.h"

#include "Creational/builder.h"
#include "Creational/builder_groovy_style.h"
#include "Creational/builder_facets.h"

int main(int argc, const char * argv[]) {
  // insert code here...
  std::cout << "Hello, World!\n";
  
  // SOLID
  {
    // Single responsibility
    {
      Journal journal("New Diary");
      journal.add_entry("This is january");
      journal.add_entry("This is february");
    }
    
    // Open Close
    {
      Product apple {"apple", Color::gree, Size::small };
      Product tree {"Tree", Color::gree, Size::large };
      Product house {"House", Color::blue, Size::large };
      
      std::vector<Product*> items {&apple, &tree, &house};
      
      // Problem
      ProductFilter pf;
      auto gree_things = pf.by_color(items, Color::gree);
      
      for (auto& i : gree_things)
        std::cout << i->name << " is green \n";
      
      // Solution
      BetterFilter bf;
      ColorSpec green(Color::gree);
      
      for (auto& i : bf.filter(items, green))
        std::cout << i->name << " is green \n";
      
      // Combinatero
      SizeSpec large(Size::large);
      
      AndSpecification<Product> green_large(green, large);
      for (auto& i : bf.filter(items, green_large))
        std::cout << i->name << " is green and large \n";
      
      // Clean version
      auto spec = ColorSpec(Color::gree) && SizeSpec(Size::large);
      for (auto& i : bf.filter(items, spec))
        std::cout << i->name << " is green and large \n";
    }
    
    // Liscov substituteion
    {
      Rectangle r(5, 7);
      process(r);
      
      Square s(8);
      process(s);
      
      auto rr = ReectangleFactory::create_rectangle(5, 7);
      process(rr);
      auto ss = ReectangleFactory::create_suare(8);
      process(ss);
    }
    
    // Dependency inversion
    {
      Person p{"John"};
      Person c1{"Chriss"}, c2{"Mat"};
      Better_low_level_Relationships r;
      r.add_parent_and_child(p, c1);
      r.add_parent_and_child(p, c2);
      
      Better_Research _(r);
    }
    
  }
  // Builder
  {
    auto text = "hello";
    std::string output;
    output += "<p>";
    output += text;
    output += "</p>";
    
    std::cout << output << std::endl;
    
    std::string words[] = { "hello", "world" };
    std::ostringstream oss;
    oss << "ul";
    for (auto w : words)
      oss << "  <li>" << w << "</li>";
    oss << "</ul>";
    std::cout << oss.str() << std::endl;
    
    // with builder
    HtmlBuilder h{"ul"};
    h.add_child("li", "hello");
    h.add_child("li", "world");
    std::cout << h.str() << std::endl;
    
    // with fluint builder
    HtmlBuilder h1{"ul"};
    h1.add_child_fluint("li", "hello").add_child_fluint("li", "world");
    std::cout << h1.str() << std::endl;
    
    // withou builder
    HtmlElement e{"ul", ""};
    e.elemennts.push_back({"li", "hello"});
    e.elemennts.push_back({"li", "world"});
    std::cout << e.str() << std::endl;
    
    // groofy style
    
    std::cout <<
    P {
      IMG("This/path/img.png")
    }
    << std::endl;
    
    Builder::Person::create().
                     lives().at("H-15").
                             in("Delhi").
                             with_post_code("110059").
                     works().as_a("Engineed").
                             at("Some Company").
                             earning(1000);
  }
  
  // Factoru
  {
    
  }
  return 0;
}
