//
//  interface_segregation_p.h
//  DesignPatterns
//
//  Created by iKan on 16/07/22.
//

#ifndef interface_segregation_p_h
#define interface_segregation_p_h

#include <iostream>
#include <vector>

/*
 Defination :
 DO NOT CREATE LARGER INTERFACE
 if any interface is getting large then break them
 */

/*
 Example :
 */
struct Document;

struct IMachine {
  virtual void print(Document& d) = 0;
  virtual void scan(Document& d) = 0;
  virtual void fax(Document& d) = 0;
};

// FINE
struct MFP : public IMachine {
  void print(Document& d) override {
    // OK
  }
  void scan(Document& d) override {
    // OK
  }
  void fax(Document& d) override {
    // OK
  }
};

/*
 TODO: PROBLEM
 we have defined so much API in interface that should not be done as alot of
 state might not use all of them at once. so there might be some or more
 unused API in implementation 
 */
struct Scanner : public IMachine {
  void print(Document& d) override {
    // NOT OK
  }
  void scan(Document& d) override {
    // OK
  }
  void fax(Document& d) override {
    // NOT OK
  }
};

/*
 SOLUTION:
 Segregate the interfaces
 */

struct IPrinter {
  virtual void print(Document& d) = 0;
};

struct IScanner {
  virtual void scan(Document& d) = 0;
};

struct IFax {
  virtual void fax(Document& d) = 0;
};

struct Printer : public IPrinter {
  void print(Document& d) override {
    // OK
  }
};

struct I_Print_Scan : public IPrinter, IScanner { }; // virtual interface
struct Print_Scan : public I_Print_Scan {
  IPrinter& p;
  IScanner& s;
  
  Print_Scan(IPrinter& p,
             IScanner& s) : p(p), s(s) {}
  
  void print(Document& d) override {
    p.print(d);
  }
  void scan(Document& d) override {
    s.scan(d);
  }
};

/*
 Another Example:
 Do not define all the Mesage in FAPI base state.
 as in runnung state might not use idle state API
 */

#endif /* interface_segregation_p_h */
