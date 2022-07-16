//
//  liskov_substitutaion_p.h
//  DesignPatterns
//
//  Created by iKan on 16/07/22.
//

#ifndef liskov_substitutaion_p_h
#define liskov_substitutaion_p_h

#include <iostream>
#include <vector>

/*
 Defination :
 Sub types should be imediately substitutable for their base type
 */

/*
 Example :
 */

class Rectangle {
protected:
  int width, height;
public:
  Rectangle(int width, int height) : width(width), height(height) {}
  
  virtual void set_width(int width) {
    Rectangle::width = width;
  }

  virtual void set_height(int height) {
    Rectangle::height = height;
  }
  
  int get_width() const {
    return Rectangle::width;
  }

  int get_height() const {
    return Rectangle::height;
  }
  
  int area() const { return width * height; }
};

class Square : public Rectangle {
public:
  Square(int size) : Rectangle(size, size) {}
  
  // TODO: PROBLEM
  void set_width(int width) override {
    Rectangle::height = Rectangle::width = width;
  }

  // TODO: PROBLEM
  void set_height(int height) override {
    Rectangle::height = Rectangle::width = height;
  }
};

/*
 TODO: PROBLEM
 A function with base class should also work same for derived class.
 in this case as we have override the set width and set height methods in
 derived square so our behaviour is going to be changed.
 
 Any derived class should be able to be substituted in this function without
 any problem
 */
void process(Rectangle& r) {
  int w = r.get_width();
  r.set_height(10);
  
  std::cout << "expected area = " << w * 10
            << " got area = " << r.area()
            << std::endl;
}

/*
 SOLUTION:
 either have some flag in rectangle "is_square"
 or create some factory
 */
struct ReectangleFactory {
  static Rectangle create_rectangle(int w, int h) {
    return Rectangle(w, h);
  }
  static Rectangle create_suare(int s) {
    return Rectangle(s, s);
  }

};

#endif /* liskov_substitutaion_p_h */
