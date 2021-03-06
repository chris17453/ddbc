import argparse
import os
import sys
import datetime
from pprint import pprint
import re
from .tpl import tpl

from .functions import build_functions
from .headers import build_headers
from .engine_template import build_engine, build_defines





if __name__=='__main__':
    parser = argparse.ArgumentParser("languish", usage='%(prog)s [options]', description="""c code generator for language parsing""", epilog="")
    parser.add_argument('-i', help='return headers', action='store_true')
    parser.add_argument('-e', help='return defines', action='store_true')
    args = parser.parse_args()
    template_dir="definitions/"
    if args.i:
        build_headers(template_dir)
    elif args.e:
        build_defines(template_dir)
    else:
        #build_functions(template_dir)
        build_engine(template_dir)
