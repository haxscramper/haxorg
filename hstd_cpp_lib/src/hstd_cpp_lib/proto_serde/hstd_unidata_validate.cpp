#include "hstd_unidata_validate.hpp"

hstd::ext::unidata::VerifyResult hstd::ext::unidata::VerifyResult::Ok() {
    return VerifyResult{.is_ok = true};
}

hstd::ext::unidata::VerifyResult hstd::ext::unidata::VerifyResult::Error(
    std::string const& failure) {
    return VerifyResult{.is_ok = false, .message = failure};
}
