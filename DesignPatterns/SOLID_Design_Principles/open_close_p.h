//
//  open_close_p.h
//  DesignPatterns
//
//  Created by iKan on 16/07/22.
//

#ifndef open_close_p_h
#define open_close_p_h

#include <iostream>
#include <vector>

/*
 Defination :
 System should be able for any extention in feature with minimal or if
 possible no changes in current working code....
 Open for extention
 Close for modification
 */

/*
 Example :
 */
enum class Color { red, gree, blue };
enum class Size { small, medium, large };

struct Product {
  std::string name;
  Color color;
  Size size;
};

/*
 TODO: PROBLEM :
 This solution is not scalable. If we want to filter something like Size
 then we have to create another function. That not the only problem,
 If we want to filter like "Green large" item some combination then we have
 to create filter for each requirement,
 Imagin 100 proprty so how many combination are possible ?
 .......
 */
struct ProductFilter {
  std::vector<Product*> by_color(std::vector<Product*> items, Color color) {
    std::vector<Product*> result;
    for (auto& i : items) {
      if (i->color == color)
        result.push_back(i);
    }
    return result;
  }
  
  std::vector<Product*> by_size(std::vector<Product*> items, Size size) {
    std::vector<Product*> result;
    for (auto& i : items) {
      if (i->size == size)
        result.push_back(i);
    }
    return result;
  }
  
  std::vector<Product*> by_size_and_color(std::vector<Product*> items, Size size, Color color) {
    std::vector<Product*> result;
    for (auto& i : items) {
      if (i->size == size && i->color == color)
        result.push_back(i);
    }
    return result;
  }
};

/*
 SOLUTION :
 Create some template for filter and check the specification of filter
 */

template <typename T> struct AndSpecification;
template <typename T> struct Specification {
  virtual bool is_satisfied(T* item) = 0;
  
  // JUST to make API more clean
  AndSpecification<T> operator and(Specification<T>&& other) {
    return AndSpecification<T>(*this, other);
  }
};

// All we have to do is define the specification of all the product
// specification only and generic combinator

template <typename T> struct AndSpecification : public Specification<T> {
  Specification<T>& first;
  Specification<T>& second;
  
  AndSpecification(Specification<T>& first,
                   Specification<T>& second) : first(first), second(second) {}
  
  bool is_satisfied(T* item) override {
    return first.is_satisfied(item) and second.is_satisfied(item);
  }
};

struct ColorSpec : Specification<Product> {
  Color color;
  explicit ColorSpec(Color color) : color(color) {}
  
  bool is_satisfied(Product* item) {
    return item->color == color;
  }
};

struct SizeSpec : Specification<Product> {
  Size size;
  explicit SizeSpec(Size size) : size(size) {}
  
  bool is_satisfied(Product* item) {
    return item->size == size;
  }
};

template <typename T> struct Filter {
  virtual std::vector<T*> filter(std::vector<T*> items,
                                 Specification<T>& spec) = 0;
};

struct BetterFilter : Filter<Product> {
  std::vector<Product*> filter(std::vector<Product*> items,
                               Specification<Product>& spec) override {
    std::vector<Product*> result;
    for (auto& i : items) {
      if (spec.is_satisfied(i))
        result.push_back(i);
    }
    return result;
  }
};

/*
 Another Example:
 Might be:
 we can create some filter for components.
 Also we have created Component so that we need not to change Entity class
 every time we add a new component
 */

#endif /* open_close_p_h */
