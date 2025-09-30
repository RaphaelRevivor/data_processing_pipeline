from python_tools.data_cleaner.cleaner import DataCleaner

def test_dropMissingRowsCSV():
    cleaner = DataCleaner()
    cleaner.readFile("tests/python/example1.csv")
    cleaner.dropMissingRows()
    cleaner.writeFile()


    assert cleaner.filecontent == [        
        {'id': '1', 'name': 'Alice', 'age': '30', 'score': '88'}, 
        {'id': '3', 'name': 'Charlie', 'age': '35', 'score': '95'}
    ]
    
    
    
def test_normalizeTextCSV():
    cleaner = DataCleaner()
    cleaner.readFile("tests/python/example2.csv")
    cleaner.normalizeText()
    cleaner.writeFile()


    assert cleaner.filecontent == [
        {'id': '1', 'name': 'alice', 'age': '30', 'score': '88'},
        {'id': '2','name': 'bob', 'age': '25', 'score': '72'},
        {'id': '3','name': 'charlie', 'age': '35', 'score': '95'},
        {'id': '4','name': 'diana', 'age': '45', 'score': '85'},
    ]

def test_handleNaNsCSV():
    cleaner = DataCleaner()
    cleaner.readFile("tests/python/example3.csv")
    cleaner.handleNaNs()
    cleaner.writeFile()

    assert cleaner.filecontent == [
        {'id': '1', 'name': 'Alice', 'age': '30', 'score':'0'},
        {'id': '2', 'name': '0', 'age': '0', 'score':'72'},
        {'id': '3', 'name': "Charlie", 'age': '22', 'score':'95'},
        {'id': '4', 'name': "Diana", 'age': '0', 'score':'0'},

    ]


def test_dropMissingRowsJSON():
    cleaner = DataCleaner()
    cleaner.readFile("tests/python/example1.json")
    cleaner.dropMissingRows()
    cleaner.writeFile()

    assert cleaner.filecontent == [        
        {'id': 1, 'name': 'Alice', 'age': 30, "score": 88}, 
        {'id': 3, 'name': 'Charlie', 'age': 22, "score": 95}
    ]

def test_normalizeTextJSON():
    cleaner = DataCleaner()
    cleaner.readFile("tests/python/example2.json")
    cleaner.normalizeText()
    cleaner.writeFile()

    assert cleaner.filecontent == [
        {'id': 1, "name": "alice", "age": 30, "score": 88},
        {'id': 2, "name": "bob", "age": 25, "score": 72},
        {'id': 3, "name": "charlie", "age": 35, "score": 95},
        {'id': 4, "name": "diana", "age": 45, "score": 85},
    ]


def test_handleNaNsJSON():
    cleaner = DataCleaner()
    cleaner.readFile("tests/python/example3.json")
    cleaner.handleNaNs()
    cleaner.writeFile()
    

    assert cleaner.filecontent == [
        {'id': 1, "name": "Alice", "age": 0, "score": 88},
        {'id': 2, "name": "Bob", "age": 25, "score": 0},
        {'id': 3, "name": 0, "age": 22, "score": 95},
        {'id': 4, "name": "Diana", "age": 0, "score": 0},

    ]

def test_completeCleaningCSV():
    cleaner = DataCleaner()
    cleaner.readFileAndClean("tests/python/example4.csv")

    assert cleaner.filecontent == [
        {'id': '1', 'name': 'alice', 'age': '30', 'score': '88'},
        {'id': '2', 'name': 'bob', 'age': '25', 'score': '0'},
        {'id': '3', 'name': "charlie", 'age': '22', 'score': '95'},
        {'id': '4', 'name': "diana", 'age': '45', 'score': '85'},
        {'id': '6', 'name': "freddy", 'age': '90', 'score': '100'}
]

def test_completeCleaningJSON():
    cleaner = DataCleaner()
    cleaner.readFileAndClean("tests/python/example4.json")

    assert cleaner.filecontent == [
        {'id': 1, 'name': 'alice', 'age': 30, 'score': 88},
        {'id': 2, 'name': 'bob', 'age': 25, 'score': 0},
        {'id': 3, 'name': "charlie", 'age': 22, 'score': 95},
        {'id': 4, 'name': "diana", 'age': 45, 'score': 85},
        {'id': 6, 'name': "freddy", 'age': 90, 'score': 100}
]


# This is added temporarily to solve the pytest not able to run via Bazel issue,
# see: https://stackoverflow.com/a/58345932.
# This can further be eliminated using either a macro or rule
if __name__ == "__main__":
    import pytest
    raise SystemExit(pytest.main([__file__]))