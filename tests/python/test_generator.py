from python_tools.report_generator.generator import ReportGenerator
import os

def test_generated_file():
    rg = ReportGenerator("tests/python", "output_generate_stats_file.json")
    rg.read_JSON_file()
    rg.handle_empty_values()
    rg.generate_HTML_file()

    html_content = rg.read_HTML_test_file()

    assert html_content == """
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <title>Statistics Report</title>
            <style>
                body { font-family: Arial, sans-serif; margin: 20px; }
                h1 { color: #333; }
                table {
                    border-collapse: collapse;
                    width: 50%;
                    margin-top: 20px;
                }
                th, td {
                    border: 1px solid #ddd;
                    padding: 8px;
                    text-align: left;
                }
                th {
                    background-color: #f2f2f2;
                }
                ul {
                    list-style-type: disc;
                    margin-left: 20px;
                }
                .missing {
                    color: #888;
                    font-style: italic;
                }
            </style>
        </head>
        <body>
            <h1>Statistics Report</h1>

            <p><b>Mean:</b> <span class="">85.0</span></p>
            <p><b>Median:</b> <span class="">86.5</span></p>

            <p><b>Mode(s):</b></p>
            <ul>
                <li>95</li><li>88</li><li>85</li><li>72</li>
            </ul>

            <p><b>Variance:</b> <span class="">69.5</span></p>
            <p><b>Standard Deviation:</b> <span class="">8.336666000266533</span></p>

            <p><b>Frequencies:</b></p>
            <table>
                <tr><th>Value</th><th>Frequency</th></tr>
                <tr><td>72</td><td>1</td></tr><tr><td>85</td><td>1</td></tr><tr><td>88</td><td>1</td></tr><tr><td>95</td><td>1</td></tr>
            </table>
        </body>
        </html>
        """