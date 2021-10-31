#!/usr/bin/env python3

import argparse
import datetime
import os


class Feature:
    EMPTY = []
    TIMESTAMP = "timestamp"
    FILE_IO = "file-io"
    TC_FORMAT = "tc-format"
    PROBLEM_HEADER = "train-header"
    USE_CLASS = "class"


FEATURES = [Feature.EMPTY, Feature.TIMESTAMP, Feature.FILE_IO, Feature.TC_FORMAT,
            Feature.PROBLEM_HEADER]  # , Feature.USE_CLASS]


def main():
    parser = argparse.ArgumentParser(description='Generate my competitive programming template')
    parser.add_argument('filename', type=str, help='name of file to create, should end in ".cpp"')
    parser.add_argument('features', nargs='*', help='list of features to include in template', choices=FEATURES)

    args = parser.parse_args()
    filename = args.filename
    if not filename.endswith(".cpp"):
        if input("Filename does not end in .cpp. Append .cpp? ").lower() in ['y', 'yes']:
            filename += ".cpp"
    if os.path.isfile(filename):
        if input("Replace existing file? y/n: ").lower() not in ['y', 'yes']:
            return
        else:
            print("Replacing file")

    features = args.features

    comment = f"\n//{filename} created at {datetime.datetime.now().strftime('%D %T')}\n"
    basename = filename.rsplit('.', maxsplit=1)[0]

    if Feature.TIMESTAMP in features:
        if Feature.PROBLEM_HEADER in features:
            comment = gen_train_header(basename) + '\n' + comment
        with open(filename, 'w') as prog:
            prog.write(comment.strip() + '\n\n')
        return
    header = comment + HEADER
    if Feature.PROBLEM_HEADER in features:
        header = gen_train_header(filename) + '\n' + header

    IO = gen_file_io(basename if Feature.FILE_IO in features else "")

    if Feature.TC_FORMAT in features:
        main_func = """
void solve(int testcase) {


    cout << "Case #" << testcase << ": " << ' ' << '\\n';
}

""" + MAIN
    else:
        main_func = """
void solve(int testcase) {

}

""" + MAIN

    parts = [header, DEFINE, TYPEDEF, FUNC, GEO, DEBUG, IO, CONST, main_func]
    file = '\n\n'.join([part.strip() for part in parts])

    with open(filename, 'w') as prog:
        prog.write(file)


def gen_train_header(problem_name):
    return f"""
/*
ID: zhongbr1
TASK: {problem_name}
LANG: C++14
*/"""


template_path = "/Users/qpwoeirut/CompetitiveProgramming/templates/"

with open(template_path + "header.cpp") as header_file, open(template_path + "define.cpp") as define_file,\
        open(template_path + "typedef.cpp") as typedef_file, open(template_path + "func.cpp") as func_file,\
        open(template_path + "geo.cpp") as geo_file, open(template_path + "debug.cpp") as debug_file, \
        open(template_path + "const.cpp") as const_file, open(template_path + "main.cpp") as main_file:
    HEADER = header_file.read()
    DEFINE = define_file.read()
    TYPEDEF = typedef_file.read()
    FUNC = func_file.read()
    GEO = geo_file.read()
    DEBUG = debug_file.read()
    CONST = const_file.read()
    MAIN = main_file.read()


def gen_file_io(basename):
    return f"""void setIO(const string& filename = "{basename}") """ + """{
    if (filename.size() > 0) {
        freopen((filename + ".in").c_str(), "r", stdin);
        freopen((filename + ".out").c_str(), "w", stdout);
    }
    cin.tie(0)->sync_with_stdio(0);
    // cout << fixed << setprecision(?);
}
"""


if __name__ == "__main__":
    main()
