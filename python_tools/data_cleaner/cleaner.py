import csv
import json

class DataCleaner: 

    def __init__(self, filename):
        self.filename = filename
        self.filetype = self.detect_filetype()
        self.filecontent = [list[dict]]
        pass

    def detect_filetype(self):
        file_ending = self.filename.split(".")[1]
        if(file_ending == "csv"):
            return "csv"
        elif(file_ending == "json"):
            return "json"

    def readFile(self):

        if(self.filetype == "csv"):
            with(open(self.filename, mode='r', newline='')) as file:
                csv_reader = csv.DictReader(file)
                self.filecontent = [row for row in csv_reader]

        elif(self.filetype == "json"):
            with(open(self.filename, mode = 'r')) as file:
                self.filecontent = json.load(file)

        else:
            raise ValueError("Unsupported file type")

    def writeFile(self):

        if(self.filetype == "csv"):
            with(open(self.filename, mode ='w')) as file:
                csv_writer = csv.DictWriter(file, fieldnames=self.filecontent[0].keys())
                csv_writer.writeheader()
                csv_writer.writerows(self.filecontent)

        elif(self.filetype == "json"):
            with(open(self.filename, mode ='w')) as file:
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