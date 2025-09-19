#include "json_parser.h"

using namespace std;
using json = nlohmann::json;

string trimNonNumLetters(string s)
{
  auto start = find_if(s.begin(), s.end(), [](unsigned char c) {return isalnum(c);});
  auto end = find_if(s.rbegin(), s.rend(), [](unsigned char c) {return isalnum(c);}).base();
  if(start >= end)
    return "";
  return string(start, end);
}

// function to parse the json file
void JsonParser::parse(const string& filename)
{
  ifstream file(filename);
  if (!file.is_open())
  {
    cerr << "Error: Could not open file " << filename << endl;
    throw runtime_error("Could not open file: " + filename);
  }
  else
  {
    cout << "Parsing Json file " << filename << "..." << endl;
  }

  json json_file;
  try {
    file >> json_file;
  }
  catch (const exception& e)
  {
    cerr << e.what() << endl;
  }

  // example json file:
  // [
  //   { "id": 1, "name": "Alice", "age": 23, "score": 88 },
  //   { "id": 2, "name": "Bob", "age": 25, "score": 72 },
  //   { "id": 3, "name": "Charlie", "age": 22, "score": 95 },
  //   { "id": 4, "name": "Diana", "age": 23, "score": 85 }
  // ]
  for(const auto& item : json_file)
  {
    map<string, string> tmp;
    for(auto iter = item.begin(); iter != item.end(); iter++)
    {
      // store as a string
      tmp[iter.key()] = trimNonNumLetters(iter.value().dump());
    }
    rows.emplace_back(tmp);
  }
}

// function to print all rows using unique patterns
void JsonParser::print()
{
  for(const auto& row : rows)
  {
    for(const auto& [k,v] : row)
    {
      cout << k << ":" << v << ",";
    }
    cout << endl;
  }
}

// function to get all entries
vector<vector<pair<string, string>>> JsonParser::getEntries()
{
  vector<vector<pair<string, string>>> output = {};
  for(const auto& row : rows)
  {
    vector<pair<string, string>> tmp = {};
    for(const auto& [k,v] : row)
    {
      tmp.emplace_back(make_pair(k, v));
    }
    output.emplace_back(tmp);
  }
  return output;
}

// function to get a certain entry by its id
vector<pair<string, string>> JsonParser::getEntryById(const string& id)
{
  vector<pair<string, string>> output = {};
  for(const auto& row : rows)
  {
    // has to use at here
    if (row.at("id") == id)
    {
      for(const auto& [k,v] : row)
      {
        output.emplace_back(make_pair(k, v));
      }
    }
  }

  return output;
}