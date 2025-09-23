#include "csv_parser.h"

using namespace std;


/**
 * Parses the contents of a .csv file to the rows object in csv_parser.
 * @param filename, string representing the filename of the .csv that should be parsed.
 * @return void
 * @note make sure file is read accessible, this function handles empty lines
 * @author Samuel
 */

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

/**
 * Converts rows object to vector of vector of pairs and returns it.
 * @param void
 * @return temp, vector of vector of pairs, containing the same value as the rows object.
 * @author Samuel
 */

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

/**
 * Retrieves a specific entry from parsed CSV data based on provided ID in parameters 
 * @param id, string representing the ID of the entry to be retreived
 * @return temp, the vector of pairs corresponding to the id
 * @author Samuel 
 */

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

/**
 * Prints the parsed CSV data to the console with row object from parsers 
 * @param void 
 * @return void
 * @note Used for debugging
 * @author Samuel 
 */

void CsvParser::print(){
    for(auto &&row: rows){
        for(auto &&[key, value]: row){
            cout << key << ": " << value << " ";
        } 
        cout << endl;
    }
};