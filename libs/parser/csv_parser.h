#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include <string>
#include <memory>

#include "parser.h"

class CsvParser : public Parser {
public:
  void parse(const string& filename) override;
};

#endif