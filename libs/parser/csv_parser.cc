#include "csv_parser.h"

using namespace std;

void CsvParser::parse(const string& filename)
{

    ifstream file(filename);
    string line {""};
    map<string, string> temp_map {};
    vector<string> headers;

    if(!file.is_open()){
        cout << "Error opening " << filename << endl;
    } else {
        cout << "Processing " << filename  << "..." << endl;
    }

    
    if(getline(file, line)){
        stringstream ss(line);
        string header;
        while(getline(ss, header, ',')){
            headers.push_back(header);
        }
    }

    while(getline(file, line)){
        if(line.empty()) continue;

        stringstream ss(line);
        string value;
        map<string, string> row;
        size_t col = 0;

        while(getline(ss, value, ',')){
            if(col < headers.size()){
                row[headers[col]] = value;
            }
            col++;
        }
        rows.emplace_back(row);
    }
    file.close();
}

vector<vector<pair<string, string>>> CsvParser::getEntries(){

     vector<vector<pair<string, string>>> temp = {};
     vector<pair<string, string>> vec = {};

     for (auto &&row : rows)
     {
        for (auto &&[key, value] : row)
        {
            vec.emplace_back(make_pair(key, value));      
        }
        temp.push_back(vec);
        vec.clear();
     }
    
    return temp;
};

vector<pair<string, string>> CsvParser::getEntryById(const string &id){

    vector<pair<string, string>> temp = {};
        for (auto &&row : rows){

            if(row.at("id") == id){

                for (auto &&[key, value] : row)
                {
                    temp.emplace_back(make_pair(key, value));
                }
                
            }
        }
        return temp;
};

void CsvParser::print(){
    for(auto &&row: rows){
        for(auto &&[key, value]: row){
            cout << key << ": " << value << " ";
        } 
        cout << endl;
    }
};