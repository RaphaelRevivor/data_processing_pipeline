#include <fstream>

#include "stats.h"
#include "parser_factory.h"
#include "tools/cpp/runfiles/runfiles.h"

using namespace std;

int main(int argc, char* argv[]) 
{
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <file_path>" << endl;
        return 1;
    }

    string filePath = argv[1];
    int totalSize = filePath.size();
    int suffixSize = 4;

    if(totalSize < suffixSize) 
    {
        cerr << "File path not correct" << endl;
        return 1;
    } 

    shared_ptr<Parser> parserPtr;
    
    if (filePath.compare(totalSize - suffixSize, suffixSize, ".csv") == 0)
    {
        parserPtr = ParserFactory("csv");
    } 
    else if (filePath.compare(totalSize - suffixSize, suffixSize, "json") == 0) 
    {
        parserPtr = ParserFactory("json");
    } 
    else 
    {
        cerr << "Unsupported file type" << endl;
        return 1;
    }

    parserPtr->parse(filePath);
    auto data = parserPtr->getEntries();
    
    Stats stats;
    stats.readData(data);
    stats.loadScores();
    json jsonObj;
    stats.fillJSONObject(jsonObj);
    string outFilePath = argv[2];
    ofstream output(outFilePath);
    output << jsonObj.dump();

    return 0;
}
