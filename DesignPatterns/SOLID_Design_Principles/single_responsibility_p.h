//
//  single_responsibility_p.h
//  DesignPatterns
//
//  Created by iKan on 16/07/22.
//

#ifndef single_responsibility_p_h
#define single_responsibility_p_h

#include <iostream>
#include <vector>

/*
 Defination :
 A class should have a single reason to change. A class should have primary
 responsibility, should not be responsible for any other responsibility.
 */

/*
 Example :
 Main responsibility of journal is to add and store the entiry in the
 Journal. If we want to store these entries in some file then we should not
 modify this class as this class main responsibility to add entiry and store
 only as class member. Should not be responsible to hold or write in any file
 */
struct Journal {
  std::string title;
  std::vector<std::string> entries;
  
  Journal(const std::string& title) : title(title) { }
  
  void add_entry(const std::string& entry) {
    static int count = 1;
    entries.push_back(std::to_string(count++) + ": " + entry);
  }
  
  /*
   TODO: PROBLEM :
   This is completely wrong way of doing. we have separate persistance code in
   my main journal class. save might be used by only few of the modules.
   */
  void save(const std::string& filename) {
    // Open some file
    // write the data in file
  }
};

/*
 SOLUTION :
 Have separate persistance manager
 */
struct PersistanceManager {
  static void save(const Journal& j, const std::string& filename) {
    // Open some file
    // write the data in file
  }
};

/*
 Another Use case:
 if  we want to change the file save method (now we want to use some database
 instead of file) all we have to do is just change the persistance not the
 entire journal
 */

/*
 Another example:
 We store entities in scene but we never have any API in scene to save them in
 Some file, we create separate serializer for that
 */

#endif /* single_responsibility_p_h */
