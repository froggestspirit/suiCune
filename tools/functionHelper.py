#!/usr/bin/env python3
import argparse
import time
import os
import re

tab = "    "
toolDir = os.path.dirname(os.path.realpath(__file__))
functionsFile = f"{toolDir}/../functions.h"
redirectedFuncs = []
containedFuncs = []
convertedFuncs = []


def analyze(fileName):
    printFile = f"{fileName}\n"
    with open(fileName, "r") as inFile:
        asmFile = inFile.read().replace(tab, "\t").split("\n")
    currentFunc = None
    currentFuncs = []
    fallthrough = False
    for line in asmFile:
        if line:
            if line[:4] == "void":
                currentFunc = line.split("(")[0][5:]
                currentFuncs.append(currentFunc)
                fallthrough = False
            elif line[0] == "}":
                if not fallthrough:
                    for cFunc in currentFuncs:
                        
                        if cFunc not in containedFuncs and cFunc not in convertedFuncs and cFunc in redirectedFuncs:
                            print(f"{printFile}\t{cFunc}")
                            printFile = ""
                            containedFuncs.append(cFunc)
                    currentFunc = None
                    currentFuncs = []
                    fallthrough = False
            elif line[:7] == "\treturn" and "[" not in line and currentFunc not in convertedFuncs and currentFunc in redirectedFuncs:
                fallthrough = True
            elif line[0] == "\t":
                op = line.strip("\t").split("(")[0].split(" ")[0]
                if op in ("CALL", "CALL_Z", "CALL_NZ", "CALL_C", "CALL_NC",
                          "JP", "JP_Z", "JP_NZ", "JP_C", "JP_NC",
                          "JR", "JR_Z", "JR_NZ", "JR_C", "JR_NC", "RST"):
                    routine = line.split(";")[0].replace(op, "", 1).strip("\t() ")[1:]
                    if routine not in containedFuncs and routine not in convertedFuncs:
                        currentFunc = None
                        currentFuncs = []
                        fallthrough = False
                elif op in ("JP_hl", "JP_hl;", "return", "return;",
                            "FARCALL", "CALLFAR", "HOMECALL", "PREDEF", "PREDEF_JUMP"):
                    currentFunc = None
                    currentFuncs = []
                    fallthrough = False


def update(fileName):
    printFile = f"{fileName}\n"
    with open(fileName, "r") as inFile:
        asmFile = inFile.read().replace(tab, "\t").split("\n")
    for lineNum, line in enumerate(asmFile):
        if line:
            lastLine = lineNum + 1
    asmFile = asmFile[:lastLine]
    currentFunc = None
    with open(fileName, "w") as outFile:
        for lineNum, line in enumerate(asmFile):
            skipLine = False
            if line:
                if line[:3] == "int":
                    currentFunc = line.split("(")[0][4:]
                elif line[0] == "}":
                    currentFunc = None
                elif line[0] == "\t":
                    op = line.strip("\t").split("(")[0].split(" ")[0]
                    if op == "SET_PC":
                        if currentFunc in containedFuncs or currentFunc in convertedFuncs:
                            skipLine = True
                    elif op in ("CALL", "CALL_Z", "CALL_NZ", "CALL_C", "CALL_NC",
                                "JP", "JP_Z", "JP_NZ", "JP_C", "JP_NC",
                                "JR", "JR_Z", "JR_NZ", "JR_C", "JR_NC", "RST"):
                        routine = line.split(";")[0].replace(op, "", 1).strip("\t() ")[1:]
                        condition = ""
                        op = op.split("_")
                        if len(op) == 2:
                            condition = f"IF_{op[1]} "
                        op = op[0]
                        comment = f"{';'.join(line.split(';')[1:])}"
                        if routine in convertedFuncs:
                            if currentFunc in containedFuncs or currentFunc in convertedFuncs:
                                if len(op) > 2:  # Op is either call or rst
                                    line = f"\t{condition}{routine}();{comment}"
                                else:
                                    line = f"\t{condition}return {routine}();{comment}"
                                print(f"{printFile}{lineNum + 1}: {line}")
                                printFile = ""
                        elif routine in containedFuncs:
                            if len(op) > 2:  # Op is either call or rst
                                line = f"\t{condition}CCALL(a{routine});{comment}"
                            else:
                                line = f"\t{condition}return {routine}();{comment}"
                            print(f"{printFile}{lineNum + 1}: {line}")
                            printFile = ""
            if not skipLine:
                outFile.write(line.replace('\t', tab))
                outFile.write("\n")
            skipLine = False


def main():
    global redirectedFuncs
    global containedFuncs
    global convertedFuncs
    parser = argparse.ArgumentParser()
    parser.add_argument("fileName")
    #parser.add_argument("-a", "--analyze", dest="analyze", action="store_true", help="Check file for contained functions, and update list")
    #parser.add_argument("-u", "--update", dest="update", action="store_true", help="Update calls/jumps to contained/converted functions in C file")
    args = parser.parse_args()
    
    if os.path.exists(functionsFile):
        with open(functionsFile, "r") as inFile:
            funcsFile = inFile.read().split("\n")
        for line in funcsFile:
            line = line.split("//")[0]
            if re.search("(CONVERTED|REDIRECT)", line):
                regex = re.search(r"REDIRECT_1\(.*\);", line)
                if regex:
                    redirectedFuncs.append(regex.group(0)[10:].strip("\(\);"))
                regex = re.search(r"REDIRECT_2\(.*\);", line)
                if regex:
                    containedFuncs.append(regex.group(0)[10:].strip("\(\);"))
                regex = re.search(r"CONVERTED\(.*\);", line)
                if regex:
                    convertedFuncs.append(regex.group(0)[10:].strip("\(\);"))
        while len(funcsFile[-1]) < 2:  # Trim the end of the file, including the closing }
            funcsFile.pop()

        analyze(args.fileName)

        for i, line in enumerate(funcsFile):
            line = line.split("//")[0]
            if re.search("(CONVERTED|REDIRECT)", line):
                regex = re.search(r"(CONVERTED|REDIRECT_[12])\(.*\);", line)
                if regex:
                    func = regex.group(0)[10:].strip("\(\);")
                    if func in containedFuncs:
                        funcsFile[i] = f"{tab}REDIRECT_2({func});"
                    if func in convertedFuncs:
                        funcsFile[i] = f"{tab}CONVERTED({func});"
        if os.path.exists(functionsFile):
            os.remove(functionsFile)
            with open(functionsFile, "w") as fFile:
                for line in funcsFile:
                    fFile.write(f"{line}\n")
                fFile.write(f"}}\n")

    return 0


start = time.time()
if not main():
    pass
    #print(f"Done in: {time.time() - start} seconds")
