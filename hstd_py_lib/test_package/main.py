from hstd_py_lib import algorithm


def main() -> None:
    value = algorithm.cond(True, 1, 2)
    assert value == 1


if __name__ == "__main__":
    main()
