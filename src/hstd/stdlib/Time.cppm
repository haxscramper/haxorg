module;

import hstd.stdlib.Variant;
import hstd.system.aux_utils;
#include <absl/time/civil_time.h>
#include <absl/time/time.h>
import hstd.stdlib.Str;

export module hstd.stdlib.Time;

export {
struct UserTime {
    DECL_DESCRIBED_ENUM(Alignment, Year, Month, Day, Hour, Minute, Second);
    Str toString() const { return absl::FormatTime(time, zone); }

    absl::Time     time;
    absl::TimeZone zone;
    Alignment      align;
    BOOST_DESCRIBE_CLASS(UserTime, (), (time, zone, align), (), ());
};
}
