import numpy as np

def dropMissingRows(rows: list[dict]):
    for row in rows:
        for key, value in row.items():
            if(value is None):
                row.clear()
                break
    return rows

def normalizeText(rows: list[dict]):
    for row in rows:
        for key, value in row.items():
            if(isinstance(row[key], str)):
                row[key] = value.lower().replace(" ", "")
    return rows

def handleNaNs(rows: list[dict]):
    for row in rows:
        for key, value in row.items():
            if(value is np.nan):
                value = "0"
    return rows    