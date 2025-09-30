import csv
import json
import os
import argparse

from python.runfiles import runfiles

class DataCleaner: 

    def __init__(self):
        self.filename = ""
        self.filetype = ""
        self.filecontent = []
        self.r = runfiles.Create()

    def detect_filetype(self, filepath):
        file_ending = filepath.split(".")[1]
        if(file_ending == "csv"):
            return "csv"
        elif(file_ending == "json"):
            return "json"
        
    def initArgs(self):
        self.parser.add_argument("filepath", help = "Path to the input file")
        self.parser.add_argument("--read-file-only", action="store_true", help="Reading a file without cleaning the data")

    def readFile(self, filepath): 
        workspace = os.environ.get('BUILD_WORKSPACE_DIRECTORY', 'data_processing_pipeline')

        data_location = self.r.Rlocation(f"{workspace}/{filepath}")

        self.filetype = self.detect_filetype(filepath) 
        self.output = filepath.split(".")
        self.output = f"{self.output[0]}_cleaned.{self.output[1]}" 

        self.filecontent.clear()

        if(self.filetype == "csv"):
            with(open(data_location, "r")) as file:
                csv_reader = csv.DictReader(file)
                self.filecontent = [row for row in csv_reader]

        elif(self.filetype == "json"):
            with(open(data_location, "r")) as file:
                self.filecontent = json.load(file)

        else:
            raise ValueError("Unsupported file type")

    def writeFile(self):
        workspace = os.environ.get('BUILD_WORKSPACE_DIRECTORY', 'data_processing_pipeline')

        data_location = self.r.Rlocation(f"{workspace}/{self.output}")

        if(self.filetype == "csv"):
            with(open(data_location, mode='w')) as file:
                csv_writer = csv.DictWriter(file, fieldnames=self.filecontent[0].keys())
                csv_writer.writeheader()
                csv_writer.writerows(self.filecontent)

        elif(self.filetype == "json"):
            with(open(data_location, mode='w')) as file:
                json.dump(self.filecontent, file)
    
    def overrideOutput(self, output):
        self.output = output

    def handleNaNs(self): 
        if self.filetype == "csv": 
            self.filecontent = [
            row for row in self.filecontent
            if not all(value is None or value == '' for value in row.values())
            ]

        elif self.filetype == "json":   
            self.filecontent = [        
                row for row in self.filecontent if not all(value is None or value == '' for value in row.values())
            ]

    def normalizeText(self): 
        for row in self.filecontent:
            for key, value in row.items():
                if(isinstance(row[key], str)):
                    row[key] = value.lower().replace(" ", "")


    def readFileAndClean(self, filepath):   
        self.readFile(filepath)
        self.normalizeText()
        self.handleNaNs()
        self.writeFile()

def main():
    parser = argparse.ArgumentParser(description="Clean CSV/JSON files")
    parser.add_argument("filepath", help="Path to the input file")
    parser.add_argument("--read-file-only", action="store_true", help="Only read the file and not clean")
    args = parser.parse_args()
    cleaner = DataCleaner()

    if args.read_file_only:
        cleaner.readFile(filepath=args.filepath)
    else:
        cleaner.readFileAndClean(filepath=args.filepath)

if __name__ == '__main__':
    main()