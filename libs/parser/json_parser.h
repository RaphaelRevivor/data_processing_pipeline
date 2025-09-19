#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <map>
#include <fstream>
#include <nlohmann/json.hpp>

#include "parser.h"

using namespace std;

class JsonParser : public Parser {
public:
  vector<map<string, string>> rows;
  void parse(const string& filename) override;
  void print() override;
  virtual vector<vector<pair<string, string>>> getEntries() override;
  virtual vector<pair<string, string>> getEntryById(const string& id) override;
};

#endif