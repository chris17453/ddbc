import argparse
import os
import sys
import datetime
from pprint import pprint
import re
from tpl import tpl

from .functions import build_functions
from .headers import build_headers





if __name__=='__main__':
    parser = argparse.ArgumentParser("languish", usage='%(prog)s [options]', description="""c code generator for language parsing""", epilog="")
    parser.add_argument('-i', help='return headers', action='store_true')
    args = parser.parse_args()
    template="base.def"
    if args.i:
        build_headers(template)
    else:
        build_functions(template)
