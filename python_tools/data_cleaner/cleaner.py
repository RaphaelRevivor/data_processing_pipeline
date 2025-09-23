import numpy as np

def cleaner():
    print("Cleaning block")

def dropMissingRows(rows: list[dict]):
    print("Dropping rows with missing values")
    for row in rows:
        if(any(row.value is None or isinstance(row.value, float))):
            rows.remove(row)

def normalizeText():
    print("Normalizing text data")

def handleNaNs():
    print("Hanlding NaN values")

    