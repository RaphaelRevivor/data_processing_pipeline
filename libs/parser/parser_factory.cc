#include "parser_factory.h"

shared_ptr<Parser> ParserFactory(const string& type)
{
  // if (type == "csv")
  // {
  //   return make_shared<CsvParser>();
  // }
  if (type == "json")
  {
    return make_shared<JsonParser>();
  }
  throw invalid_argument("Unknown parser type!");
}