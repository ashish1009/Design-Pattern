//
//  builder.h
//  DesignPatterns
//
//  Created by iKan on 16/07/22.
//

#ifndef builder_h
#define builder_h

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

/*
 Defination :
 Create instance of complex object piece by piece with clean API.
 NOTE: do not create 10s of constructor ...
 */

/*
 TODO: PROBLEM EXAMPLE
 */
#ifdef INSIDE_MAIN // Life without builder
{
  auto text = "hello";
  std::string output;
  output += "<p>";
  output += text;
  output += "</p>";
  
  std::cout << output << endl;
  
  std::string words[] = { "hello", "world" };
  ostringstream oss;
  oss << "ul";
  for (auto w : words)
    oss << "  <li>" << w << "</li>";
  oss << "</ul>";
  std::cout << oss.str() << std::endl;
}
#endif

/*
 SOLUTION :
 Simple builder
 */

struct HtmlBuilder;
struct HtmlElement {
  std::string name, text;
  std::vector<HtmlElement> elemennts;
  
  const size_t indent_size = 2;
  
  HtmlElement() {}
  HtmlElement(const std::string& name, const std::string& text)
  : name(name), text(text) {}
  
  std::string str(int indent = 0) const {
    std::ostringstream oss;
    std::string i(indent_size * indent, ' ');
    oss << i << "<" << name << ">" << std::endl;
    if(text.size() > 0)
      oss << std::string(indent_size * (indent+1), ' ') << text << std::endl;
    
    for (const auto& e: elemennts)
      oss << e.str(indent + 1);
    
    oss << i << "</" << name << ">" << std::endl;
    return oss.str();
  }
  
  // Give  hints to CLient about builder
  // Again Fluint builder api
#if 0
  // This code not complie in single . h file
  static HtmlBuilder build(std::string& root_name) {
    return {root_name};
  }
  
  // API after this
  // auto builder = HtmlElement::build("ul").add_child_fluint("", "").add_child_fluint("", "") .....
#endif
};

struct HtmlBuilder {
  HtmlElement root;
  
  HtmlBuilder(const std::string& name) {
    root.name = name;
  }

  // For fluint builder API
  /*
   withou fluent API was like :
         HtmlBuilder h{"ul"};
         h.add_child("li", "hello");
         h.add_child("li", "world");
         std::cout << h.str() << std::endl;
   
   Fluiunt Builder
   
   with fluent builer api is
         HtmlBuilder h{"ul"};
         h.add_child("li", "hello").add_child("li", "world");
         std::cout << h.str() << std::endl;
   */
  HtmlBuilder& add_child_fluint(const std::string& name, const std::string& text) {
    HtmlElement e(name, text);
    root.elemennts.emplace_back(e);
    return *this;
  }

  void add_child(const std::string& name, const std::string& text) {
    HtmlElement e(name, text);
    root.elemennts.emplace_back(e);
  }
  
  std::string str() const {
    return root.str();
  }
  
  // for fluient api
  operator HtmlElement() const { return root; }
  // API after this
  // HtmlElement root = HtmlElement::build("ul").add_child_fluint("", "").add_child_fluint("", "") .....
};

#endif /* builder_h */
