#!/usr/bin/env python3
import argparse
import os
import glob
from pathlib import Path

packages = ["dict", "hook", "io", "mem", "parallel", "path", "proc", "queue", "set", "string", "time", "trie", "uid", "vec"]

Path("dist").mkdir(parents=True, exist_ok=True)

def dist():
	tag = "v0"
	amalg = f"dist/absys-{tag}.c"
	cfiles = glob.glob("absys/**/*.c")
	with open(amalg, "a+") as amalgf:
		amalgf.truncate(0)
		for cfile in cfiles:
			with open(cfile, "r") as cfilef:
				amalgf.write(cfilef.read())

parser = argparse.ArgumentParser(prog="absys-dist", description="Distribute absys as a single amalgamated source file")
args = parser.parse_args()

dist()
