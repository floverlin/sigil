import os
import sys

NAME = "build"


def exe(name: str):
    return f"{name}.exe"


files = os.scandir(".")
files = filter(lambda x: x.name.endswith(".c"), files)
files = map(lambda x: x.name, files)
files = list(files)


def build() -> int:
    return os.system(f"gcc -o {NAME} {" ".join(files)}")


def run(args: list[str]):
    if build() == 0:
        try:
            os.system(exe(NAME) + " " + " ".join(args))
        except KeyboardInterrupt:
            return
        finally:
            os.remove(exe(NAME))


def check_flag(flag: str, short: str | None = None) -> bool:
    return (("--" + flag) in sys.argv) or (
        (("-" + short) in sys.argv) if short else False
    )


def find_flag_index(flag: str, short: str | None = None) -> int:
    index = None
    try:
        index = sys.argv.index("--" + flag)
    except ValueError:
        index = sys.argv.index("-" + short)
    return index


if check_flag("run", "r"):
    name = "__" + NAME
    idx = find_flag_index("run", "r")
    run(sys.argv[idx + 1 :])
else:
    build()
