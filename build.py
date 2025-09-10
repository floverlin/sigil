import os
import sys

name = "build"


def exe():
    return f"{name}.exe"


files = os.scandir(".")
files = filter(lambda x: x.name.endswith(".c"), files)
files = map(lambda x: x.name, files)
files = list(files)


def build() -> int:
    return os.system(f"gcc -o {name} {" ".join(files)}")


def run():
    try:
        if build() == 0:
            os.system(exe())
    except KeyboardInterrupt:
        return
    finally:
        os.remove(exe())


def check_flag(flag: str, short: str | None = None) -> bool:
    return (("--" + flag) in sys.argv) or (
        (("-" + short) in sys.argv) if short else False
    )


if check_flag("run", "r"):
    name = "__" + name
    run()
else:
    build()
