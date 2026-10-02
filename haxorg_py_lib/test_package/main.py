from haxorg_py_lib import org


def main() -> None:
    parse = org.ParseContext()
    node = parse.parseString("*Text*", "<test_word>")

    assert node.getKind() == org.OrgSemKind.Document
    assert node[0].getKind() == org.OrgSemKind.Paragraph
    assert node[0][0].getKind() == org.OrgSemKind.Bold
    assert node[0][0][0].getKind() == org.OrgSemKind.Word


if __name__ == "__main__":
    main()
