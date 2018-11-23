#ifndef _MAKEFILE_
#define _MAKEFILE_
#include <string>
#include <iostream>
#include "target.h"

const int maxTargets = 20;

struct Makefile {     
  std::ostream &out;     // Makefile ostream
  int num_targets;  	 // Number of Targets existing
  std::string *keys;     // Array of Target names
  Target **targets; 	 // Array of ptr to Targets
  int timestamp;  	 // Time Stamp

  Target* find_target(std::string name) const; // Helper

  Makefile(std::ostream &out = std::cout);
  ~Makefile();
  void addDepend(const std::string &t, const std::string &d);
  void changeTarget(const std::string &t);
  void rebuild(const std::string &t);
};

#endif

