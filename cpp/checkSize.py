import os
from tabulate import tabulate
import re

total = {"mega2560": 256 - 8, "atmega328": 32 - 5}
for k in total.keys():
    try:
        used = int(re.search("Total\s*(\d+)", os.popen("avr-size -A .build/{}/firmware.hex".format(k)).read()).group(1))
    except:
        pass
for k, t in total.items():
    total[k] = t * 1000
table = []
for k, t in total.items():
    row = [k, used, t]
    percentage = round((used / float(t) * 100), 2)
    s = "{}%"
    if percentage > 100:
        s = "\033[91m{}\033[0m".format(s)
    row.append(s.format(percentage))
    table.append(row)
print(tabulate(table, headers=["Model", "Used", "Total", "Percentage"], stralign="right"))
