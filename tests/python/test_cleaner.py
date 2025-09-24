from python_tools.data_cleaner import cleaner
import numpy as np

def test_dropMissingRows():
    list_of_dicts = [
        {'name': 'Alice', 'age': 30},
        {'name': 'Bob', 'age': None},
        {'name': None, 'age': 25},
        {'name': 'Charlie', 'age': 35},
    ]
    assert cleaner.dropMissingRows(list_of_dicts) == [        
        {'name': 'Alice', 'age': 30}, 
        {},
        {},
        {'name': 'Charlie', 'age': 35}
    ]

def test_normalizeText():
    list_of_dicts = [
        {'name': 'Al ic e', 'age': 30},
        {'name': ' Bob', 'age': 25},
        {'name': 'C h arl ie ', 'age': 35},
        {'name': 'Dia ngelo', 'age': 45},
    ]

    assert cleaner.normalizeText(list_of_dicts) == [
        {'name': 'alice', 'age': 30},
        {'name': 'bob', 'age': 25},
        {'name': 'charlie', 'age': 35},
        {'name': 'diangelo', 'age': 45},

    ]

def test_handleNaNs():
    list_of_dicts = [
        {'name': 'Alice', 'age': np.nan},
        {'name': np.nan, 'age': 25},
        {'name': "Charlie", 'age': 35},
        {'name': np.nan, 'age': np.nan},
    ]
        
    assert cleaner.handleNaNs(list_of_dicts) == [
        {'name': 'Alice', 'age': "0"},
        {'name': "0", 'age': "0"},
        {'name': "Charlie", 'age': 35},
        {'name': "0", 'age': "0"},

    ]

# This is added temporarily to solve the pytest not able to run via Bazel issue,
# see: https://stackoverflow.com/a/58345932.
# This can further be eliminated using either a macro or rule
if __name__ == "__main__":
    import pytest
    raise SystemExit(pytest.main([__file__]))