#! /usr/bin/env python3
# Usage:
#   a command script use for power calculation
import argparse
parser = argparse.ArgumentParser()
group = parser.add_mutually_exclusive_group()
group.add_argument("-v", "--verbose", action="store_true")
group.add_argument("-q", "--quiet", action="store_true")
parser.add_argument("x", help="the base", type=int)
parser.add_argument("y", help="the exponent", type=int)
# add positional argument
args = parser.parse_args()
answer = args.x**args.y
if args.quiet:
    print(answer)
if args.verbose:
    print("{} to the power {} equals {}".format(args.x, args.y, answer))
else:
    print("{}^{}=={}".format(args.x, args.y, answer))
