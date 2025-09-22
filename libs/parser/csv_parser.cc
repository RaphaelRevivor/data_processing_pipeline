#include "csv_parser.h"

using json = nlohmann::json;

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

    size_t idx {0};
    while(getline(file, line)){
        map<string, string> temp_map {};
        string header {};

        //If empty line
        if(line.empty()) {cout << "Line is empty!" << endl; continue;}

        //Generates a header vector which contains the headers to use
            for (size_t i = 0; i < line.size(); i++)
            {
               if(line[i] == ',' || line[i] == '\n'){
                    headers.push_back(header);
                    header.clear();
                    continue;
               } 
               header += line[i];
            } 
            headers.push_back(header);

        while(getline(file, line)){
            for (size_t i = 0; i < line.size(); i++)
            {
            if(line[i] == ','){
                idx++;
                continue;
            } else if(line[i] != ',' && line[i] != '\n'){
                temp_map[headers[idx]] += line[i];        
            }
        }
        //Emplace back temp_map
        rows.emplace_back(temp_map);
        idx = 0;
        //Clear internal vars
        temp_map.clear();
        header.clear();   
        }
        break;
        

        //Emplace back temp_map
        rows.emplace_back(temp_map);
        idx++;
        //Clear internal vars
        temp_map.clear();
        file.close();   
        }    
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
                    temp.emplace_back(make_pair(key ,value));
                }
                
            }
        }
        return temp;
};

void CsvParser::print(){
    for(auto &&row: rows){
        for(auto &&[key, value]: row){
            cout << key << ": " << value;
        } 
        cout << endl;
    }
};