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

    string error;
    unique_ptr<bazel::tools::cpp::runfiles::Runfiles> runfiles(
        bazel::tools::cpp::runfiles::Runfiles::Create(argv[0], &error)
    );

    if (!runfiles) {
        cerr << "Failed to create Runfiles object: " << error << endl;
        return 1;
    }

    // this is not really hard-coded as the relative dir structure won't change
    auto loc = string("libs/math") + argv[1];
    auto filePath = runfiles->Rlocation(loc.c_str());
    cout << loc << endl;
    
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

    if (!stats.generateStatsFile()) {
        cerr << "Failed to generate stats.json" << endl;
        return 1;
    }

    return 0;
}
