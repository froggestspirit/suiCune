#!/usr/bin/env python3
import argparse
import time

#RET #27531: 2FEC, PC@39:325
#CALL#27531: 209E, PC@39:209E
def main():
    minimum = 4135
    parser = argparse.ArgumentParser()
    parser.add_argument("fileName")
    args = parser.parse_args()

    with open(args.fileName, "r") as inFile:
        logFile = inFile.read().split("\n")
    lines = len(logFile)
    curLine = minimum
    while curLine < lines:
        thisLine = logFile[curLine]
        if (thisLine is None) or (thisLine[:4] != "CALL"):
            logFile[curLine] = None
            curLine += 1
            continue
        print(f"Checking line {curLine + 1}/{lines}")
        callNum = thisLine[5:thisLine.find(":")]
        searchLine = curLine
        while searchLine < lines:
            thisSearchLine = logFile[searchLine]
            if (thisSearchLine is None) or (thisSearchLine[:3] != "RET"):
                searchLine += 1
                continue
            print(f"Sub line {searchLine + 1}/{lines}", end = "\r")
            callSearchNum = thisSearchLine[5:thisSearchLine.find(":")]
            if callNum == callSearchNum:
                logFile[curLine] = None
                logFile[searchLine] = None
                break
            searchLine += 1
        curLine += 1
    with open("output.txt", "w") as outFile:
        for i in logFile:
            if i:
                outFile.write(f"{i}\n")
    return 0


start = time.time()
if not main():
    print(f"Done in: {time.time() - start} seconds")
