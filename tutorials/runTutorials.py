# -*- coding: utf-8 -*-
## \file runTutorials.py
## Script for running all validations cases
## adapted from porousMultiphaseFoam source code, Horgue P. et al. (2014)

# import
from __future__ import with_statement
import os, subprocess, sys

# import list_cases
from tutorialList import tutorials as testCases

class testCase:


    #=============================================================================
    # ROUTINE run
    #=============================================================================
    def __init__(self, category, case):

        self.category = category
        self.case = case
        self.testDir = category+"/"+case

    #=============================================================================
    # ROUTINE run
    #=============================================================================
    def run(self):

        print ""
        print "Test : " + self.category + " " + self.case
        print ""

        refDir=os.getcwd()

        os.chdir(self.testDir)

        ProcessPipe=subprocess.Popen("./run", shell=True, \
                                     stdout=subprocess.PIPE,stderr=subprocess.PIPE)

        stdout, stderr = ProcessPipe.communicate()

        if len(stderr) > 0:

            print "[ ERROR C++ ] " + stderr

        else:

            find_str = "FOAM exiting"
            foamFile = "log."+"hybridPorousInterFoam"
            with open(foamFile, "r") as f:
                f.seek(0, 2)
                fsize = f.tell()
                f.seek (max (fsize-1024, 0), 0)
                lines = f.readlines()

            lines = lines[-3:]

            if find_str + "\n" in lines:

                print "[ ERROR OpenFOAM ] "

            else:

                subprocess.Popen("./clean", shell=True)
        
                print "[ OK ]"

            os.chdir(refDir)

        return 0

#===============================================================================
# PROGRAM Main
#===============================================================================

if __name__ == '__main__':

    print "========================================================"
    print "                   RUNNING TEST CASES                   "
    print "========================================================"

    for case in testCases:
        test = testCase(case["category"],case["case"])
        test.run()

    print " "
    print "========================================================"
    print "                        FINISHED                        "
    print "========================================================"

    sys.exit(0)
