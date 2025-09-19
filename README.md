A data processing pipeline implmented using C++ and Python, compiled with Bazel.# Data Processing Pipeline (Bazel Monorepo MVP)

This repository is a **Bazel monorepo** that demonstrates:

* Medium-level **Bazel usage** (C++, Python, shell, custom rules).
* **C++ fundamentals** (classes, inheritance, polymorphism, smart pointers, containers, file I/O).
* **Python basics** for data cleaning and reporting.
* **Testing frameworks**: GoogleTest (C++) and pytest (Python).
* **Code coverage** integration.

The project simulates a **data processing pipeline**:

1. Parse input data (CSV or JSON).
2. Compute statistics (mean, median, variance, frequency counts).
3. Clean data (Python).
4. Generate reports (Python).
5. Orchestrate everything with a shell script.

---

## 📂 Project Structure

```
data_processing_pipeline/
├── .github/
│   └── workflows/
│       └── ci.yml              # CI pipeline
├── apps/
├── examples/
│   ├── BUILD
│   ├── example.csv             # Sample CSV input
│   ├── example.json            # Sample JSON input
│   ├── main.cc                 # Example entrypoint
│   └── main.h
├── libs/
│   ├── math/                   # Statistics library (C++)
│   └── parser/                 # CSV + JSON parsers (C++)
│       ├── BUILD
│       ├── csv_parser.cc
│       ├── csv_parser.h
│       ├── json_parser.cc
│       ├── json_parser.h
│       ├── parser_factory.cc
│       ├── parser_factory.h
│       ├── parser.cc
│       └── parser.h
├── python_tools/               # Python data processing tools
├── rules/                      # Custom Bazel rules (Starlark)
├── scripts/                    # Shell orchestration scripts
├── tests/
│   ├── cpp/
│   │   ├── BUILD
│   │   ├── example.json        # Test dataset
│   │   ├── test_csv_parser.cc
│   │   ├── test_integration.cc
│   │   ├── test_json_parser.cc
│   │   └── test_stats.cc
│   └── python/
├── .bazelrc
├── BUILD                       # Top-level build
├── MODULE.bazel                # Bazel 8 module dependencies
└── README.md                   # Project overview (this file)
```

---

## 🚀 Usage

### Build everything

```bash
bazel build //...
```

### Run the example C++ tool

```bash
bazel run //examples:example -- $(location //examples:example.csv)
```

### Run tests

```bash
bazel test //tests/...
```


---

## 🧑‍💻 Goals

* **Bazel**: cc\_library, cc\_binary, cc\_test, py\_binary, py\_test, sh\_binary, genrule, custom rules.
* **C++**: class design, inheritance, polymorphism, smart pointers, containers, string manipulation, file I/O.
* **GoogleTest**: assertions, fixtures, mocking basics.
* **pytest**: fixtures, parameterization, CLI args, config-driven tests.
* **Coverage**: collect and report code coverage.

---