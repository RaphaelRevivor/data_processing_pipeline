#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <vector>

using namespace std;

class Parser {
public:
  // virtual constructor that needs to be overridden in sub-classes
  virtual void parse(const string& filename) = 0;
  virtual ~Parser() = default;
  virtual void print() = 0;
  // real internal implementation is hidden from users
  virtual vector<vector<pair<string, string>>> getEntries() = 0;
  virtual vector<pair<string, string>> getEntryById(const string& id) = 0;
};

#endif