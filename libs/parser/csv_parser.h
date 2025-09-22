#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include <string>
#include <memory>
#include <fstream>
#include <map>
#include <algorithm>

#include "parser.h"

using namespace std;

class CsvParser : public Parser {
public:
  vector<map<string, string>> rows;
  void parse(const string& filename) override;
  void print() override;
  
  vector<vector<pair<string, string>>> getEntries() override;
  vector<pair<string, string>> getEntryById(const string& id) override;
};

#endif