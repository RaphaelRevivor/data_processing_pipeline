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
        self.filename = ""
        self.filetype = ""
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
    :Method to initialize the terminal arguments to call tests
    """
    def initArgs(self):
        self.parser.add_argument("filepath", help = "Path to the input file")
        self.parser.add_argument("--read-file-only", action="store_true", help="Reading a file without cleaning the data")

    """
    Method to read content of file depending on the filetype.
    :param str filepath: filepath to the file which should be read.
    """
    def readFile(self, filepath): 

        workspace = os.environ.get('BUILD_WORKSPACE_DIRECTORY', 'data_processing_pipeline')
        #workspace_root = os.environ.get('BUILD_WORKSPACE_DIRECTORY', "data_processing_pipeline")
        #filepath = os.path.join(workspace_root, filepath)

        data_location = self.r.Rlocation(filepath)

        self.filetype = self.detect_filetype(filepath) 
        
        self.output = filepath.split(".")
        self.output = f"{os.path.splitext(filepath)[0]}_cleaned{os.path.splitext(filepath)[1]}" #<filepath>_cleaned<csv/json>

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
        workspace = os.environ.get('BUILD_WORKSPACE_DIRECTORY', 'data_processing_pipeline')

        #Check if the current output path exists, if not create the directories

        basename, ext = os.path.splitext(os.path.basename(self.filename))
        cleaned_filename = f"{basename}_cleaned.{self.filetype}"

        if self.output_dir: #If outputdir is provided
            output_dir = os.path.join(workspace, self.output_dir)
        else:
            input_dir = os.path.dirname(self.filename)
            output_dir = os.path.join(workspace, input_dir)
        
        os.makedirs(output_dir, exist_ok=True)
        output_path = os.path.join(output_dir, cleaned_filename)

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
    cleaner = DataCleaner()

    if args.read_file_only:
        cleaner.readFile(filepath=args.filepath)
    else:
        cleaner.readFileAndClean(filepath=args.filepath)
    
    return parser.parse_args()

if __name__ == '__main__':
    args = main()
    #cleaner = DataCleaner(args.filepath, output_dir=args.output_dir)