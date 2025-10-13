from python.runfiles import runfiles
import json

def main():
    r = runfiles.Create()
    path = r.Rlocation("data_processing_pipeline/libs/math/output.json")
    print(f"Reading: {path}")

    with open(path) as f:
        data = json.load(f)
    print(data)

if __name__ == "__main__":
    main()