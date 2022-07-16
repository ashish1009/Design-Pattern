//
//  builder_groovy_style.h
//  DesignPatterns
//
//  Created by iKan on 16/07/22.
//

#ifndef builder_groovy_style_h
#define builder_groovy_style_h

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <ostream>

struct Tag {
  std::string name, text;
  std::vector<Tag> childs;
  std::vector<std::pair<std::string, std::string>> attribute;
  
  friend std::ostream& operator <<(std::ostream& os, const Tag& t) {
    os << "<" << t.name;
    
    for (const auto& att : t.attribute)
      os << " " << att.first << "=\"" << att.second << "\"";
    
    if (t.childs.size() == 0 and t.text.length() == 0)
      os << "/>" << std::endl;
    else {
      os << ">" << std::endl;
      if (t.text.length())
        os << t.text << std::endl;
      
      for (const auto& c : t.childs)
        os << c;
      
      os << "</" << t.name << ">" << std::endl;
    }
    return os;
  }
protected:
public:
  Tag(const std::string& name, const std::string& text) : name(name), text(text) {}
  Tag(const std::string& name, const std::vector<Tag>& childs)
  : name(name), childs(childs) {}
};

struct P : public Tag {
public:
  P(const std::string& text) : Tag("p", text) {}
  P(std::initializer_list<Tag> li) : Tag("p", li) {}
};

struct IMG : public Tag {
public:
  IMG(const std::string& url) : Tag("imp", "") {
    attribute.emplace_back(std::make_pair("src", url));
  }
};

#endif /* builder_groovy_style_h */
