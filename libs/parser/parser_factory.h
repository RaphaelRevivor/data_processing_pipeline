#ifndef PARSER_FACTORY_H
#define PARSER_FACTORY_H

#include "parser.h"
#include "json_parser.h"
#include "csv_parser.h"

shared_ptr<Parser> ParserFactory(const string& type);

#endif