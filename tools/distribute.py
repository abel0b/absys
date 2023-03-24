#!/usr/bin/env python3
import argparse
import os
import glob
from pathlib import Path

absys_root = Path(__file__).parent.parent
Path(f"{absys_root}/dist").mkdir(parents=True, exist_ok=True)

def dist(args):
	cfiles = Path(f"{absys_root}/absys").rglob("*.c")
	with open(args.output, "a+") as amalgf:
		amalgf.truncate(0)
		amalgf.write("// Amalgamated absys source\n")
		for cfile in cfiles:
			with open(cfile, "r") as cfilef:
				amalgf.write(cfilef.read())

parser = argparse.ArgumentParser(prog="absys-dist", description="Distribute absys as a single amalgamated source file")
parser.add_argument("--output", "-o", default=f"{absys_root}/dist/absys.c")
args = parser.parse_args()
dist(args)
