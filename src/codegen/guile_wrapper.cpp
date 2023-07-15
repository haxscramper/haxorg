#include "guile_wrapper.hpp"

using namespace guile;

SCM guile::eval(const std::string& code) {
    return scm_eval_string(scm_from_utf8_string(code.c_str()));
}

void guile::init() { scm_init_guile(); }

std::ostream& operator<<(std::ostream& os, SCM scm) {
    SCM representation = scm_object_to_string(
        scm, scm_variable_ref(scm_c_lookup("display")));
    char* scm_str = scm_to_locale_string(representation);
    os << scm_str;
    scm_dynwind_free(scm_str);
    return os;
}

SCM guile::eval_file(const std::string& filename) {
    // Use scm_c_primitive_load to load and evaluate the file
    return scm_c_primitive_load(filename.c_str());
}
