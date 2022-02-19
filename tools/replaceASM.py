#!/usr/bin/env python3
import argparse
import time
import os
import re

# replace without changing comments
# Run on multiple files with something like
# grep -lr pal | grep ".asm" | xargs -I {} ./replaceASM.py {}
find = r"palred"
repl = r"(1 << 0) *"

comment = ";"

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("fileName")
    parser.add_argument("-t", "--test", action="store_true")
    args = parser.parse_args()

    with open(args.fileName, "r") as inFile:
        asmFile = inFile.read().split("\n")
    count = 0
    for ln, line in enumerate(asmFile):
        if line:
            line = line.split(comment)
            reline = re.sub(f"([, \(\)]){find}([, \(\)])", f"\\1{repl}\\2", line[0])
            reline = re.sub(f"([, \(\)]){find}$", f"\\1{repl}", reline)
            if reline != line[0]:
                if args.test:
                    print(reline)
                else:
                    count += 1
                    if len(line) > 1:
                        asmFile[ln] = f"{reline}{comment}{comment.join(line[1:])}"
                    else:
                        asmFile[ln] = reline
    if not args.test and count:
        os.remove(args.fileName)
        with open(args.fileName, "w") as outFile:
            for line in asmFile[:-1]:
                outFile.write(f"{line}\n")
            outFile.write(asmFile[-1])
    return 0


start = time.time()
if not main():
    #print(f"Done in: {time.time() - start} seconds")
    pass