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
    std::cout << "\n\n\n";
    
    std::cout << std::setfill('=') << std::setw(25 + strlen("SCORES-STATISTICS")) << "SCORES-STATISTICS" << std::setw(25) << '\n';
    std::cout << std::setfill(' ') << "Mean: " << stats.calcMean() << std::setw(strlen("Median: ") + 2);
    std::cout << "Median: " << stats.calcMedian() << std::setw(strlen("Variance: " + 2)) << " Variance: " << stats.calcVariance();
    std::cout << std::setw(strlen("Standard deviation: ") + 2) << " Standard deviation: " << stats.calcStandardDeviation();

    auto data = parserPtr->getEntries();
    std::vector<int> scores {};

    for (size_t i = 0; i < data.size(); i++)
    {
        auto entry = parserPtr->getEntryById(std::to_string(i+1));
        for (auto &&[k, v]: entry)
        {
            if(k == "score"){
                scores.push_back(std::stoi(v));
                break;
            }
        }
    }
    
    if(stats.calcMode().size() == scores.size()){
        std::cout << std::setw(strlen("No identifiable mode") + 2) << "No identifiable mode";     
    }else{
        std::cout << std::setw(strlen("Mode: ") + 2) << "Mode: " << stats.calcMode()[0];
    }
    std::cout << "\n" << std::endl;

    std::cout << std::setfill('=') << std::setw(25 + strlen("FREQUENCIES-OF-SCORES")) << "FREQUENCIES-OF-SCORES" << std::setw(25) << "\n";
    for (auto &&[k,v] : stats.calcFrequencies())
    {
        std::cout << k << " appeared " << v << " time(s) ";
    }
    std::cout << std::endl;
    std::cout << "\n\n";
    
    return 0;
}