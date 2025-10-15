from python.runfiles import runfiles
import json
import os
import argparse

class ReportGenerator():
    def __init__(self, output_dir):
        self.data = {}
        self.output_dir = output_dir

    def read_JSON_file(self):
        r = runfiles.Create()
        path = r.Rlocation("data_processing_pipeline/libs/math/output.json")

        with open(path) as file:
            self.data = json.load(file)

    def handle_empty_values(self):
        for key in self.data:
            if self.data.get(key) == -1.0 or self.data.get(key) == [] or self.data.get(key) == {}:
                self.data[key] = "Value/s can not be found"

    def generate_HTML_file(self):
        content = f"""
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <title>Statistics Report</title>
            <style>
                body {{ font-family: Arial, sans-serif; margin: 20px; }}
                h1 {{ color: #333; }}
                table {{
                    border-collapse: collapse;
                    width: 50%;
                    margin-top: 20px;
                }}
                th, td {{
                    border: 1px solid #ddd;
                    padding: 8px;
                    text-align: left;
                }}
                th {{
                    background-color: #f2f2f2;
                }}
                ul {{
                    list-style-type: disc;
                    margin-left: 20px;
                }}
                .missing {{
                    color: #888;
                    font-style: italic;
                }}
            </style>
        </head>
        <body>
            <h1>Statistics Report</h1>

            <p><b>Mean:</b> <span class="{'missing' if 'Value/s' in str(self.data['mean']) else ''}">{self.data['mean']}</span></p>
            <p><b>Median:</b> <span class="{'missing' if 'Value/s' in str(self.data['median']) else ''}">{self.data['median']}</span></p>

            <p><b>Mode(s):</b></p>
            <ul>
                {"<li class='missing'>Value/s can not be found</li>" if isinstance(self.data['mode'], str) else
                ''.join(f"<li>{m}</li>" for m in self.data['mode'])}
            </ul>

            <p><b>Variance:</b> <span class="{'missing' if 'Value/s' in str(self.data['variance']) else ''}">{self.data['variance']}</span></p>
            <p><b>Standard Deviation:</b> <span class="{'missing' if 'Value/s' in str(self.data['SD']) else ''}">{self.data['SD']}</span></p>

            <p><b>Frequencies:</b></p>
            <table>
                <tr><th>Value</th><th>Frequency</th></tr>
                {"<tr><td colspan='2' class='missing'>Value/s can not be found</td></tr>" if isinstance(self.data['frequencies'], str) else
                ''.join(f"<tr><td>{k}</td><td>{v}</td></tr>" for k, v in self.data['frequencies'].items())}
            </table>
        </body>
        </html>
        """

        workspace = os.environ.get("BUILD_WORKSPACE_DIRECTORY", "./")

        if not os.path.isabs(self.output_dir):
            self.output_dir = os.path.join(workspace, self.output_dir)
        
        os.makedirs(self.output_dir, exist_ok=True)

        output_file_path = os.path.join(self.output_dir, "report.html")

        with open(output_file_path, "w", encoding="utf-8") as file:
            file.write(content)

def main():
    argparser = argparse.ArgumentParser(description="Parses arguments")
    argparser.add_argument("output_dir", help="Path to output directory")
    args = argparser.parse_args()

    rg = ReportGenerator(args.output_dir)

    rg.read_JSON_file()
    rg.handle_empty_values()
    rg.generate_HTML_file()

if __name__ == "__main__":
    main()