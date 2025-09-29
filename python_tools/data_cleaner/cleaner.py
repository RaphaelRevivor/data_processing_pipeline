import csv
import json
import os
from python.runfiles import runfiles

class DataCleaner: 

    def __init__(self, filename, output):
        self.filename = filename
        self.filetype = self.detect_filetype()
        self.outputfile = output
        self.filecontent = []
        self.r = runfiles.Create()

    def detect_filetype(self):
        file_ending = self.filename.split(".")[1]
        if(file_ending == "csv"):
            return "csv"
        elif(file_ending == "json"):
            return "json"

    def readFile(self, mode):
        workspace = os.environ.get('BUILD_WORKSPACE_DIRECTORY', 'data_processing_pipeline')

        if mode == 'input':
            data_location = self.r.Rlocation(f"{workspace}/{self.filename}")
        elif mode == 'output':
            data_location = self.r.Rlocation(f"{workspace}/{self.outputfile}")


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

        data_location = self.r.Rlocation(f"{workspace}/{self.outputfile}")

        if(self.filetype == "csv"):
            with(open(data_location, mode='w')) as file:
                csv_writer = csv.DictWriter(file, fieldnames=self.filecontent[0].keys())
                csv_writer.writeheader()
                csv_writer.writerows(self.filecontent)

        elif(self.filetype == "json"):
            with(open(data_location, mode='w')) as file:
                json.dump(self.filecontent, file)

    def dropMissingRows(self): 
        if self.filetype == "csv": 
            self.filecontent = [
            row for row in self.filecontent
            if not all(value is None or value == '' for value in row.values())
            ]

        elif self.filetype == "json":   
            self.filecontent = [        
                row for row in self.filecontent if not all(value is None or value == '' for value in row.values())
            ]

        self.writeFile()

    def normalizeText(self): 
        for row in self.filecontent:
            for key, value in row.items():
                if(isinstance(row[key], str)):
                    row[key] = value.lower().replace(" ", "")
        self.writeFile() 

    def handleNaNs(self): 
        for row in self.filecontent:
            for key, value in row.items():
                if((value == None or value == '' or str(value).lower() == 'nan') and self.filetype == "csv"):
                    row[key] = '0'
                elif((value == None or str(value).lower() == 'nan') and self.filetype == "json"):
                    row[key] = 0
        self.writeFile() 