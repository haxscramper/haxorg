#include <hstd_cpp_text_layout/textlayouter.hpp>

int main() {
    hstd::layout::BlockStore        blocks;
    hstd::layout::SimpleStringStore strings{&blocks};
    auto                            res = strings.toString(strings.text("S"));

    LOGIC_ASSERTION_CHECK_FMT(res == "S", "Failed: {}", res);

    return 0;
}
