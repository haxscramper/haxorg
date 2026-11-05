from hstd_py_text_layout.base.wrap import TextLayout


def test_trivial():
    t = TextLayout()
    text = t.text("random")
