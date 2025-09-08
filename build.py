import os

name = "build"

files = os.scandir(".")
files = filter(lambda x: x.name.endswith(".c"), files)
files = map(lambda x: x.name, files)
files = list(files)

os.system(f"gcc -o {name} {" ".join(files)}")
