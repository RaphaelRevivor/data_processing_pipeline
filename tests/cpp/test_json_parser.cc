#include <gtest/gtest.h>
#include "tools/cpp/runfiles/runfiles.h"

#include "libs/parser/json_parser.h"
#include "libs/parser/parser_factory.h"

using namespace std;

class JsonParserTest : public ::testing::Test
{
protected:
  static shared_ptr<Parser> parserPtr;

  static void SetUpTestSuite()
  {
    parserPtr = ParserFactory("json");
  }

  static void TearDownTestSuite()
  {
    parserPtr.reset();
  }

};

shared_ptr<Parser> JsonParserTest::parserPtr= nullptr;

TEST_F(JsonParserTest, JsonParserEntries)
{
  string err;
  // use TEST_SRCDIR for tests
  auto runfiles = bazel::tools::cpp::runfiles::Runfiles::CreateForTest(&err);
  ASSERT_TRUE(runfiles) << "Runfiles error: " << err;

  string filepath = runfiles->Rlocation("data_processing_pipeline/tests/cpp/example.json");
  ifstream file(filepath);
  cout << filepath << endl;
  ASSERT_TRUE(file.is_open()) << "Could not open: " << filepath;

  parserPtr->parse(filepath);
  parserPtr->print();

  EXPECT_EQ(parserPtr->getEntryById("1")[2].second, "Alice");
  auto entries = parserPtr->getEntries();
  EXPECT_EQ(entries[0][2].second, "Alice");
}