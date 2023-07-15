#pragma once

extern "C" {
#include <libguile.h>
}

#include <string>
#include <functional>
#include <iostream>


namespace guile {

void init();
SCM  eval(const std::string& code);
SCM  eval_file(const std::string& filename);

} // namespace guile


std::ostream& operator<<(std::ostream& os, SCM scm);
