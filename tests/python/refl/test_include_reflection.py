import itertools
from pathlib import Path
from tempfile import gettempdir

from more_itertools import first_true
import py_codegen.proto_lib as pb
from py_codegen.refl_read import include_visit_to_rich_tree
from py_scriptutils.rich_utils import render_rich
from py_scriptutils.script_logging import log
import pytest


@pytest.mark.test_release
def test_standard_library_include(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver
    incl: pb.IncludeVisit = refl_test_driver.get_include_tree(
        {
            "a.hpp": '#include "b.hpp"',
            "b.hpp": '#include "c.hpp"',
            "c.hpp": "",
        },
        main_file_suffix="a.hpp",
        stable_test_dir=stable_test_dir,
    )

    log().info("\n" + render_rich(
        include_visit_to_rich_tree(
            incl,
            absolute_prefix=str(stable_test_dir),
        )))

    assert incl.absolute_path.endswith("a.hpp")
    assert incl.nested[0].relative_path == "b.hpp"
    assert incl.nested[0].include_location_line == 1
    assert incl.nested[0].nested[0].relative_path == "c.hpp"


@pytest.mark.test_release
def test_include_standard_library_header(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver

    incl: pb.IncludeVisit = refl_test_driver.get_include_tree(
        {"main.hpp": "#include <vector>"},
        main_file_suffix="main.hpp",
        stable_test_dir=stable_test_dir,
    )

    std = incl.nested[0]
    assert incl.absolute_path.endswith("main.hpp")
    assert std.relative_path == "vector"
    assert std.include_location_line == 1
    assert std.absolute_path
    assert 0 < std.file_line_count
    assert 0 < std.used_line_count <= std.file_line_count


@pytest.mark.test_release
def test_nested_directory_inclusion(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver

    incl: pb.IncludeVisit = refl_test_driver.get_include_tree(
        {
            "a.hpp": '#include "inc/one/b.hpp"',
            "inc/one/b.hpp": '#include "../two/c.hpp"\nint b;',
            "inc/two/c.hpp": "int c;",
        },
        main_file_suffix="a.hpp",
        stable_test_dir=stable_test_dir,
    )

    b = incl.nested[0]
    c = b.nested[0]

    assert b.relative_path == "inc/one/b.hpp"
    assert b.absolute_path.endswith("inc/one/b.hpp")
    assert b.include_location_line == 1
    assert b.file_line_count == 2
    assert b.used_line_count == 2

    assert c.relative_path == "../two/c.hpp"
    assert c.absolute_path.endswith("inc/two/c.hpp")
    assert c.include_location_line == 1
    assert c.file_line_count == 1
    assert c.used_line_count == 1


@pytest.mark.test_release
def test_duplicate_header_names_in_different_directories(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver

    incl: pb.IncludeVisit = refl_test_driver.get_include_tree(
        {
            "main.hpp": '#include "x/common.hpp"\n#include "y/common.hpp"',
            "x/common.hpp": "int x;",
            "y/common.hpp": "int y;",
        },
        main_file_suffix="main.hpp",
        stable_test_dir=stable_test_dir,
    )

    first = incl.nested[0]
    second = incl.nested[1]

    assert first.relative_path == "x/common.hpp"
    assert first.absolute_path.endswith("x/common.hpp")
    assert first.include_location_line == 1
    assert first.file_line_count == 1
    assert first.used_line_count == 1

    assert second.relative_path == "y/common.hpp"
    assert second.absolute_path.endswith("y/common.hpp")
    assert second.include_location_line == 2
    assert second.file_line_count == 1
    assert second.used_line_count == 1

    assert first.absolute_path != second.absolute_path


@pytest.mark.test_release
def test_skipped_blocks_under_ifdef(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver

    incl: pb.IncludeVisit = refl_test_driver.get_include_tree(
        {
            "main.hpp":
                '#include "cond.hpp"',
            "cond.hpp":
                "\n".join([
                    "#if 0",
                    "int skip1;",
                    "int skip2;",
                    "#endif",
                    "int live;",
                ]),
        },
        main_file_suffix="main.hpp",
        stable_test_dir=stable_test_dir,
    )

    cond = incl.nested[0]
    assert cond.relative_path == "cond.hpp"
    assert cond.include_location_line == 1
    assert cond.file_line_count == 5
    assert cond.used_line_count == 1


@pytest.mark.test_release
def test_include_guard_header_included_twice(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver

    incl: pb.IncludeVisit = refl_test_driver.get_include_tree(
        {
            "main.hpp":
                '#include "guarded.hpp"\n#include "guarded.hpp"',
            "guarded.hpp":
                "#ifndef GUARDED_HPP\n#define GUARDED_HPP\nint guarded;\n#endif",
        },
        main_file_suffix="main.hpp",
        stable_test_dir=stable_test_dir,
    )

    assert len(incl.nested) == 1
    guarded = incl.nested[0]
    assert guarded.relative_path == "guarded.hpp"
    assert guarded.include_location_line == 1
    assert guarded.file_line_count == 4
    assert guarded.used_line_count == 4


@pytest.mark.test_release
def test_deep_nested_include_eventually_reaches_stdlib(stable_test_dir: Path) -> None:
    import tests.python.refl.refl_test_driver as refl_test_driver

    incl: pb.IncludeVisit = refl_test_driver.get_include_tree(
        {
            "a.hpp": '#include "b.hpp"',
            "b.hpp": '#include "dir/c.hpp"\nint b;',
            "dir/c.hpp": '#include "../d.hpp"\nint c;',
            "d.hpp": "#include <string>\nint d;",
        },
        main_file_suffix="a.hpp",
        stable_test_dir=stable_test_dir,
    )

    b = incl.nested[0]
    c = b.nested[0]
    d = c.nested[0]
    std = d.nested[0]

    assert b.relative_path == "b.hpp"
    assert b.include_location_line == 1
    assert b.file_line_count == 2
    assert b.used_line_count == 2

    assert c.relative_path == "dir/c.hpp"
    assert c.include_location_line == 1
    assert c.file_line_count == 2
    assert c.used_line_count == 2

    assert d.relative_path == "../d.hpp"
    assert d.include_location_line == 1
    assert d.file_line_count == 2
    assert d.used_line_count == 2

    assert std.relative_path == "string"
    assert std.absolute_path
    assert 0 < std.file_line_count
    assert 0 < std.used_line_count <= std.file_line_count
