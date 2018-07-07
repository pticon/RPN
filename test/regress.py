#!/usr/bin/env python

# Copyright 2018 Pticon
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# # Redistributions of source code must retain the above copyright notice, this
# list of conditions and the following disclaimer.
#
# # Redistributions in binary form must reproduce the above copyright notice,
#  this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
#
# # Neither the name of the copyright holder nor the names of its
# contributors may be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# @desc Quick and dirty script to avoid regressions
#
#


import sys
import os
import subprocess
import shlex
import random
import difflib
import tempfile
from optparse import OptionParser
from scapy.all import *
import time
import os.path
import os
import signal
import platform


PROGNAME="../src/rpn"
TEST_DIR="./"
FILE_DIR=TEST_DIR + "files/"
RESULT_DIR=TEST_DIR + "results/"

# define the config tests list
tests = []

# commodity
NAME=0
OPTIONS=1
FILE=2
RESULT=3

# Fields description
#              name                     options         file                    result
tests.append(["usage",			"-h",		"",		        "usage.result"])
tests.append(["basic",			"",		"basic",	        "basic.result"])
tests.append(["addition",		"",		"addition",	        "addition.result"])
tests.append(["incrementation",		"",		"incrementation",	"incrementation.result"])
tests.append(["substraction",		"",		"substraction",         "substraction.result"])
tests.append(["multiplication",		"",		"multiplication",	"multiplication.result"])
tests.append(["division",		"",		"division",	        "division.result"])
tests.append(["power",		        "",		"power",	        "power.result"])

class bcolors:
        HEADER = '\033[95m'
        OKBLUE = '\033[94m'
        OKGREEN = '\033[92m'
        WARNING = '\033[93m'
        FAIL = '\033[91m'
        ENDC = '\033[0m'
        BOLD = '\033[1m'
        UNDERLINE = '\033[4m'


def exec_test(t):
	"""Execute the given test"""
	print bcolors.BOLD + "%-50s " % t[NAME],
	args = [ PROGNAME, t[OPTIONS], FILE_DIR + t[FILE]]
	p = subprocess.Popen(" ".join(args), shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	result = open(RESULT_DIR + t[RESULT], 'r')
	diff = difflib.ndiff(result.readlines(), p.stdout.readlines())
	ret = p.wait()
	delta = ''.join(x for x in diff if x.startswith('- ') or x.startswith('+ '))
	if delta:
		print bcolors.FAIL + "KO" + bcolors.ENDC
                print " ".join(args)
		print delta
	else:
		print bcolors.OKGREEN + "OK" + bcolors.ENDC


def exec_all_tests():
	"""Execute all of the tests"""
	for t in tests:
		exec_test(t)


def list_tests():
	"""List all of the tests name"""
	print "Tests list :"
	for t in tests:
		print "\t" + t[NAME]


def exec_testname(testname):
	"""Execute the given testname"""
	for t in tests:
		if t[NAME] == testname:
			exec_test(t)
			break


def main():
	"""Main entry point"""
	usage = "usage: %prog [options] <testname>"
	parser = OptionParser(usage)

	parser.add_option("-a", "--all", action="store_true", dest="all",
		help="execute all of the tests")
	parser.add_option("-l", "--list", action="store_true", dest="list",
		help="list all of the tests")

	(options, args) = parser.parse_args()

	if options.list:
		list_tests()
		return

	if options.all:
		exec_all_tests()
		return

	if not len(args):
		parser.error("Not test name provided")
		sys.exit(-1)

	for tname in args:
		exec_testname(tname)


if __name__ == "__main__":
	main()
