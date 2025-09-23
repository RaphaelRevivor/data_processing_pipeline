#include "libs/parser/csv_parser.h"
#include "tools/cpp/runfiles/runfiles.h"

#include "libs/parser/parser_factory.h"
#include <gtest/gtest.h>

using namespace std;

class CsvParserTest : public ::testing::Test{

    protected:
    static shared_ptr<Parser> parserPtr;
        void SetUp() override {
            //Called before each test
            parserPtr = ParserFactory("csv");

        }

        void TearDown() override{
            parserPtr.reset();
        }

};

shared_ptr<Parser> CsvParserTest::parserPtr= nullptr;


TEST_F(CsvParserTest, CsvParserEntries){

    /**
     * TODO: Implement CSV tests
     * 1. Test opening the example.csv file
     * 2. Test parsing the example.csv file
     * 3. Test for getEntries() function
     * 4. Test for getEntryById() function
     */

    string err;
    auto runfiles = bazel::tools::cpp::runfiles::Runfiles::CreateForTest(&err);

    ASSERT_TRUE(runfiles) << "Runfiles error: " << err; //Using assert because if it fails, other tests will fail 
    string filepath = runfiles->Rlocation("data_processing_pipeline/tests/cpp/example.csv");
    ifstream file(filepath);
    cout << filepath << endl;
    ASSERT_TRUE(file.is_open()) << "Could not open: " << filepath; //Using assert because other tests need the files data
    
    //Parse file and print to secure that parsing was successful
    parserPtr->parse(filepath);
    parserPtr->print();

    //Testing getEntries() 
    vector<vector<pair<string, string>>> entries = parserPtr->getEntries();
    EXPECT_EQ(entries[0][0].second, "23");
    //cout << "Tested getentries" << endl;

    //Testing getEntryById()
    EXPECT_EQ(parserPtr->getEntryById("2")[2].second, "Bob");
};
