from python_tools.data_cleaner.cleaner import DataCleaner


def test_handleNaNsCSV():
    cleaner = DataCleaner("tests/python")
    cleaner.readFile("tests/python/example1.csv")
    cleaner.handleNaNs()
    cleaner.writeFile()

    assert cleaner.filecontent == [
        {'id': '1', 'name': 'Alice', 'age': '30', 'score':'88'},
        {'id': '3', 'name': "Charlie", 'age': '35', 'score':'95'},

    ]

def test_normalizeTextCSV():
    cleaner = DataCleaner("tests/python")
    cleaner.readFile("tests/python/example2.csv")
    cleaner.normalizeText()
    cleaner.writeFile()


    assert cleaner.filecontent == [
        {'id': '1', 'name': 'alice', 'age': '30', 'score': '88'},
        {'id': '2','name': 'bob', 'age': '25', 'score': '72'},
        {'id': '3','name': 'charlie', 'age': '35', 'score': '95'},
        {'id': '4','name': 'diana', 'age': '45', 'score': '85'},
    ]



def test_handleNaNsJSON():
    cleaner = DataCleaner("tests/python")
    cleaner.readFile("tests/python/example1.json")
    cleaner.handleNaNs()
    cleaner.writeFile()
    

    assert cleaner.filecontent == [
        {'id': 1, "name": "Alice", "age": 30, "score": 88},
        {'id': 3, "name": "Charlie", "age": 35, "score": 95},

    ]


def test_normalizeTextJSON():
    cleaner = DataCleaner("tests/python")
    cleaner.readFile("tests/python/example2.json")
    cleaner.normalizeText()
    cleaner.writeFile()

    assert cleaner.filecontent == [
        {'id': 1, "name": "alice", "age": 30, "score": 88},
        {'id': 2, "name": "bob", "age": 25, "score": 72},
        {'id': 3, "name": "charlie", "age": 35, "score": 95},
        {'id': 4, "name": "diana", "age": 45, "score": 85},
    ]



def test_completeCleaningCSV():
    cleaner = DataCleaner("tests/python")
    cleaner.readFileAndClean("tests/python/example3.csv")

    assert cleaner.filecontent == [
        {'id': '1', 'name': 'alice', 'age': '30', 'score': '88'},
        {'id': '3', 'name': "charlie", 'age': '22', 'score': '95'},
        {'id': '4', 'name': "diana", 'age': '45', 'score': '85'},
        {'id': '6', 'name': "freddy", 'age': '90', 'score': '100'}
]

def test_completeCleaningJSON():
    cleaner = DataCleaner("tests/python") 
    cleaner.readFileAndClean("tests/python/example3.json")

    assert cleaner.filecontent == [
        {'id': 1, 'name': 'alice', 'age': 30, 'score': 88},
        {'id': 3, 'name': "charlie", 'age': 22, 'score': 95},
        {'id': 4, 'name': "diana", 'age': 45, 'score': 85},
        {'id': 6, 'name': "freddy", 'age': 90, 'score': 100}
]