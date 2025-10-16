import csv
import json
import os
import argparse

from python.runfiles import runfiles


class DataCleaner: 
    """
    Class to read, clean and write the content of csv or json files.
    :attribute str filename: Name of the file being processed.
    :attribute str filetype: csv or json depending on filenames ending.
    :attribute list filecontent: empty list representeing the content of the file being read.
    :attribute runfiles r: Object which enables file reading in bazel environments.
    """
    def __init__(self, output_dir=None):
        self.filename = None
        self.filetype = None
        self.output_dir = output_dir
        self.filecontent = []
        self.r = runfiles.Create()

    """
    :Method to detect if the read file is a csv or json file. 
    :param str filepath: filepath which filetype should be determined
    :return str filetype: csv or json depending on which filetype is read 
    """
    def detect_filetype(self, filepath):
        file_ending = filepath.split(".")[1]
        if(file_ending == "csv"):
            return "csv"
        elif(file_ending == "json"):
            return "json"
        else: 
            raise ValueError("Unsupported filetype")
        
    """
    Method to read content of file depending on the filetype.
    :param str filepath: filepath to the file which should be read.
    """
    def readFile(self, filepath): 
        data_location = self.r.Rlocation(f"_main/{filepath}")
        self.filename = filepath
        self.filetype = self.detect_filetype(filepath)

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


    """
    Method to write the content of self.filecontent to a filepath.
    """
    def writeFile(self):
        workspace = os.environ.get('BUILD_WORKSPACE_DIRECTORY', "./")

        basename, ext = os.path.splitext(os.path.basename(self.filename)) # -> ('tests/python/example1', '.csv')
        cleaned_filename = f"{basename}_cleaned{ext}" # -> 'tests/python/example1_cleaned.csv'

        if self.output_dir is None:
            print("No output directory passed \n")
        
        if self.output_dir:
            #If output_dir is absolute, use it as is, else, join with workspace
            output_dir = self.output_dir if os.path.isabs(self.output_dir) else os.path.join(workspace, self.output_dir) # This creates a output like: cwd/output/cleaned/     
        
        os.makedirs(output_dir, exist_ok=True) #Makes dir as specified above
        output_path = os.path.join(output_dir, cleaned_filename) # -> '<workspace>/output/cleaned/tests/python/example1_cleaned.csv, Hmm still results in -> <workspace>/output/cleaned/tests/python/_cleaned 

         

        if(self.filetype == "csv"):
            with(open(output_path, mode='w')) as file:
                csv_writer = csv.DictWriter(file, fieldnames=self.filecontent[0].keys())
                csv_writer.writeheader()
                csv_writer.writerows(self.filecontent)

        elif(self.filetype == "json"):
            with(open(output_path, mode='w')) as file:
                json.dump(self.filecontent, file)
    
    """
    Method to allow for users to override the path which the class writes to.
    """
    def overrideOutput(self, output):
        self.output = output

    """
    Method to drop a row if it contains any NaN, none or Null values.
    """
    def handleNaNs(self): 
        if self.filetype == "csv": 
            self.filecontent = [
                row for row in self.filecontent
                if not any(value is None or value == '' for value in row.values())
            ]

        elif self.filetype == "json":   
            self.filecontent = [        
                row for row in self.filecontent 
                if not any(value == None for value in row.values())
            ]

    """
    Method to normalize text in a row, lower case and remove white space 
    """
    def normalizeText(self): 
        for row in self.filecontent:
            for key, value in row.items():
                if(isinstance(row[key], str)):
                    row[key] = value.lower().replace(" ", "")

    """
    Method to do a complete reading and cleaning of a file.
    :param str filepath: filepath to the file which will be cleaned.
    """
    def readFileAndClean(self, filepath):   
        self.readFile(filepath)
        self.normalizeText()
        self.handleNaNs()
        self.writeFile()

"""
Method which enables the pytest_test bazel macro to access the methods readFile() and readFileAndClean() through the terminal. 
"""
def main():
    parser = argparse.ArgumentParser(description="Clean CSV/JSON files")
    parser.add_argument("filepath", help="Path to the input file")
    parser.add_argument("--read-file-only", action="store_true", help="Only read the file and not clean")
    parser.add_argument("--output-dir", default=None, help="Optional directory to write cleaned ouput files to (default: same directory as input)")
    args = parser.parse_args()
    cleaner = DataCleaner(output_dir=args.output_dir) # Pass the output_dir here

    if args.read_file_only:
        cleaner.readFile(filepath=args.filepath)
    else:
        cleaner.readFileAndClean(filepath=args.filepath)
    
    return args

if __name__ == '__main__':
    args = main()