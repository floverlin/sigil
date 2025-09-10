import os
import sys

name = "build"


def exe(name: str):
    return f"{name}.exe"


files = os.scandir(".")
files = filter(lambda x: x.name.endswith(".c"), files)
files = map(lambda x: x.name, files)
files = list(files)


def build() -> int:
    return os.system(f"gcc -o {name} {" ".join(files)}")


def run():
    if build() == 0:
        try:
            os.system(exe(name))
        except KeyboardInterrupt:
            return
        finally:
            os.remove(exe(name))


def check_flag(flag: str, short: str | None = None) -> bool:
    return (("--" + flag) in sys.argv) or (
        (("-" + short) in sys.argv) if short else False
    )


if check_flag("run", "r"):
    name = "__" + name
    run()
else:
    build()
