#!/usr/bin/python3
import sys
import pandas as pd
if len(sys.argv) != 2:
	print ("Must have one argument to exec")
	sys.exit(1)
test = pd.read_csv(sys.argv[1])
tests = test['test.c']
with open("test.txt", "w") as test_output:
	for i in tests:
		if str(i) >= "$>":
			test_output.write(str(i)[3:] + '\n')
			test_output.write("echo $?\n")
#print(test['test.c'])
