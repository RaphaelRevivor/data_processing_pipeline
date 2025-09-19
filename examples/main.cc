#include "tools/cpp/runfiles/runfiles.h"
#include "main.h"

int main(int argc, char** argv)
{
  // following is needed to use bazel runfiles
  string err;
  auto runfiles = bazel::tools::cpp::runfiles::Runfiles::Create(argv[0], &err);
  if(!runfiles)
  {
    cerr << "Runfiles error: " << err << endl;
    return 1;
  }

  // this seems like hard-coded, but it's actually stable
  string filepath = runfiles->Rlocation("data_processing_pipeline/examples/example.json");
  cout << filepath << endl;
  auto parserPtr = ParserFactory("json");
  parserPtr->parse(filepath);
  parserPtr->print();

  return 0;
}