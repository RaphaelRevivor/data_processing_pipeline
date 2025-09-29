from python_tools.data_cleaner.cleaner import DataCleaner

def test_dropMissingRowsCSV():
    cleaner = DataCleaner(filename="tests/python/example1input.csv", output="tests/python/example1output.csv")
    cleaner.readFile('input')
    cleaner.dropMissingRows()
    cleaner.readFile('output')


    assert cleaner.filecontent == [        
        {'id': '1', 'name': 'Alice', 'age': '30', 'score': '88'}, 
        {'id': '3', 'name': 'Charlie', 'age': '35', 'score': '95'}
    ]

def test_normalizeTextCSV():
    cleaner = DataCleaner(filename="tests/python/example2input.csv", output="tests/python/example2output.csv")
    cleaner.readFile('input')
    cleaner.normalizeText()
    cleaner.readFile('output')

    assert cleaner.filecontent == [
        {'id': '1', 'name': 'alice', 'age': '30', 'score': '88'},
        {'id': '2','name': 'bob', 'age': '25', 'score': '72'},
        {'id': '3','name': 'charlie', 'age': '35', 'score': '95'},
        {'id': '4','name': 'diana', 'age': '45', 'score': '85'},
    ]

def test_handleNaNsCSV():
    cleaner = DataCleaner(filename="tests/python/example3input.csv", output="tests/python/example3output.csv")
    cleaner.readFile('input')
    cleaner.handleNaNs()
    cleaner.readFile('output')
    

    assert cleaner.filecontent == [
        {'id': '1', 'name': 'Alice', 'age': '30', 'score':'0'},
        {'id': '2', 'name': '0', 'age': '0', 'score':'72'},
        {'id': '3', 'name': "Charlie", 'age': '22', 'score':'95'},
        {'id': '4', 'name': "Diana", 'age': '0', 'score':'0'},

    ]



def test_dropMissingRowsJSON():
    cleaner = DataCleaner(filename="tests/python/example1input.json", output="tests/python/example1output.json")
    cleaner.readFile('input')
    cleaner.dropMissingRows()
    cleaner.readFile('output')

    assert cleaner.filecontent == [        
        {'id': 1, 'name': 'Alice', 'age': 30, "score": 88}, 
        {'id': 3, 'name': 'Charlie', 'age': 22, "score": 95}
    ]

def test_normalizeTextJSON():
    cleaner = DataCleaner(filename="tests/python/example2input.json", output="tests/python/example2output.json")
    cleaner.readFile('input')
    cleaner.normalizeText()
    cleaner.readFile('output')

    assert cleaner.filecontent == [
        {'id': 1, "name": "alice", "age": 30, "score": 88},
        {'id': 2, "name": "bob", "age": 25, "score": 72},
        {'id': 3, "name": "charlie", "age": 35, "score": 95},
        {'id': 4, "name": "diana", "age": 45, "score": 85},
    ]


def test_handleNaNsJSON():
    cleaner = DataCleaner(filename="tests/python/example3input.json", output="tests/python/example3output.json")
    cleaner.readFile('input')
    cleaner.handleNaNs()
    cleaner.readFile('output')
    

    assert cleaner.filecontent == [
        {'id': 1, "name": "Alice", "age": 0, "score": 88},
        {'id': 2, "name": "Bob", "age": 25, "score": 0},
        {'id': 3, "name": 0, "age": 22, "score": 95},
        {'id': 4, "name": "Diana", "age": 0, "score": 0},

    ]

# This is added temporarily to solve the pytest not able to run via Bazel issue,
# see: https://stackoverflow.com/a/58345932.
# This can further be eliminated using either a macro or rule
if __name__ == "__main__":
    import pytest
    raise SystemExit(pytest.main([__file__]))