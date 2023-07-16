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
void print(SCM obj, std::ostream& out, std::string indent = "");

bool is_plist(SCM list);
bool is_alist(SCM list);
void iterate_plist(SCM list, std::function<void(SCM, SCM)> lambda);

} // namespace guile


std::ostream& operator<<(std::ostream& os, SCM scm);
