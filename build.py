import os
import sys

name = "build"

files = os.scandir(".")
files = filter(lambda x: x.name.endswith(".c"), files)
files = map(lambda x: x.name, files)
files = list(files)


def build():
    return os.system(f"gcc -o {name} {" ".join(files)}")


def run():
    if build() == 0:
        os.system(f"{name}.exe")


if len(sys.argv) == 2 and sys.argv[1] == "--run":
    run()
else:
    build()
