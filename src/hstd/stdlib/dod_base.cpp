#include <hstd/stdlib/dod_base.hpp>
#include <hstd/stdlib/strutils.hpp>

namespace hstd::dod::detail {
std::string format_id(
    uint64_t            mask,
    uint64_t            index,
    int                 mask_size,
    FormatConfig const& conf,
    bool                is_nil) {
    std::string result;
    if (conf.name.size() != 0) { result += conf.name + "("; }

    if (conf.withMask) {
        if (0 < mask_size) {
            result += //
                hstd::format_integer_bits(mask, conf.mask_format, conf.mask_pad_to) + ":";
        }
    }

    if (is_nil) {
        result += "<nil>";
    } else {
        result += hstd::format_integer_bits(index, conf.index_format, conf.index_pad_to);
    }

    if (conf.name.size() != 0) { result += ")"; }

    return result;
}

} // namespace hstd::dod::detail
