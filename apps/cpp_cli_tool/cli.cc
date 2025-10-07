/**
 * This should accept file path + type, use factory parser, run statistics, print summary.
 * 
 * DoD:
 * bazel run //apps/cpp_cli_tool:cli -- data.csv works.
 * Console output includes mean, median, variance, frequencies.
 * 
 */

#include <iostream>
#include <string>
#include <iomanip>

#include "tools/cpp/runfiles/runfiles.h"
#include "libs/parser/parser_factory.h"
#include "libs/math/stats.h"


/**
 * main function for CLI tool. Call by running bazel run //apps/cpp_cli_tool:cli --<filepath>
 * @param argc argument count, @param argv an array of C strings (the arguments themselves)
 * @return 0 on success, 1 on failure
 */

int main(int argc, char* argv[]){
    if(argc < 2){
        std::cout << "Usage: mytool <filepath>" << std::endl;
        return 1;
    }

    std::cout << "argc = " << argc << std::endl;

    for (int i = 0; i < argc; ++i)
    std::cout << "argv[" << i << "] = " << argv[i] << std::endl;

    std::string filename = argv[1];
    std::string filetype = filename.substr(filename.find_last_of(".") + 1);



    std::string err;
    std::unique_ptr<bazel::tools::cpp::runfiles::Runfiles> runfiles(bazel::tools::cpp::runfiles::Runfiles::Create(argv[0], &err));

    std::string filepath = runfiles->Rlocation(filename);

    //Create parser w. parserfactory
    static shared_ptr<Parser> parserPtr;
    parserPtr = ParserFactory(filetype); //Evaluates to csv or json parser

    parserPtr->parse(filepath); //Parses the file

    Stats stats = Stats();

    stats.readData(parserPtr->getEntries()); // Should pass in correct datatype 
    stats.loadScores();


    std::cout << std::setfill('=') << std::setw(50) << '\n';
    std::cout << std::setfill(' ') << "Mean: " << stats.calcMean() << std::setw(13);
    std::cout << "Median: " << stats.calcMedian();

    if(stats.calcMode().size() == parserPtr->getEntryById("score").size()){
        std::cout << "No identifiably mode";     
    }else{
        std::cout << std::setw(10) << "Mode: " << stats.calcMode()[0];
        //std::cout << "Size of mode " << stats.calcMode().size() << " Size of scores " << stats.scores.size();
    }

    return 0;
}