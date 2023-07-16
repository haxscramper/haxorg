#include "guile_wrapper.hpp"

#include <format>

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

void guile::print(SCM obj, std::ostream& out, std::string indent) {
    if (scm_is_eq(obj, SCM_BOOL_T)) {
        out << indent << "<boolean>: #t\n";
    } else if (scm_is_eq(obj, SCM_BOOL_F)) {
        out << indent << "<boolean>: #f\n";
    } else if (scm_is_true(scm_integer_p(obj))) {
        out << indent << "<integer>: " << scm_to_int(obj) << "\n";
    } else if (scm_is_true(scm_real_p(obj))) {
        out << indent << "<real>: " << scm_to_double(obj) << "\n";
    } else if (scm_is_true(scm_complex_p(obj))) {
        out << indent << "<complex>: "
            << scm_to_locale_string(scm_display(obj, SCM_UNDEFINED))
            << "\n";
    } else if (scm_is_true(scm_char_p(obj))) {
        out << indent << "<character>: " << scm_to_char(obj) << "\n";
    } else if (scm_is_true(scm_string_p(obj))) {
        out << indent << "<string>: " << scm_to_locale_string(obj) << "\n";
    } else if (scm_is_true(scm_symbol_p(obj))) {
        out << indent << "<symbol>: "
            << scm_to_locale_string(scm_symbol_to_string(obj)) << "\n";
    } else if (scm_is_true(scm_vector_p(obj))) {
        out << indent << "<vector>:\n";
        size_t len = scm_c_vector_length(obj);
        for (size_t i = 0; i < len; i++) {
            print(scm_c_vector_ref(obj, i), out, indent + "  ");
        }
    } else if (scm_is_true(scm_list_p(obj))) {
        if (is_plist(obj)) {
            out << indent << "<plist>:\n";
            indent += "  ";
            iterate_plist(obj, [&](SCM key, SCM value) {
                out << indent << scm_symbol_to_string(key) << ":\n";
                print(value, out, indent + "  ");
            });

        } else if (is_alist(obj)) {
            out << indent << "<alist>:\n";
            for (; scm_is_true(scm_pair_p(obj)); obj = scm_cdr(obj)) {
                print(scm_car(obj), out, indent + "  ");
            }

        } else {
            out << indent << "<list>:\n";
            for (; scm_is_true(scm_pair_p(obj)); obj = scm_cdr(obj)) {
                print(scm_car(obj), out, indent + "  ");
            }
        }

    } else if (SCM_INSTANCEP(obj)) {

        // Print the class of the object
        SCM class_of_obj = SCM_CLASS_OF(obj);
        SCM class_name   = scm_class_name(class_of_obj);
        SCM goops_slots  = scm_class_slots(class_of_obj);
        int slot_count   = scm_to_int(scm_length(goops_slots));

        out << indent << "<GOOPS Object> "
            << "Class: " << class_name << " " << slot_count << " slots\n";
        indent += "  ";

        SCM slot_name_fun = scm_variable_ref(
            scm_c_lookup("slot-definition-name"));

        for (int i = 0; i < slot_count; ++i) {
            SCM slot  = scm_list_ref(goops_slots, scm_from_int(i));
            SCM name  = scm_call_1(slot_name_fun, slot);
            SCM value = scm_slot_ref(obj, name);
            out << indent << name << "\n";
            print(value, out, indent + "  ");
        }

    } else if (scm_is_eq(obj, SCM_UNSPECIFIED)) {
        out << indent << "<unspecified>\n";
    } else if (scm_is_true(scm_procedure_p(obj))) {
        out << indent << "<procedure>\n";
    } else if (scm_is_true(scm_port_p(obj))) {
        out << indent << "<port>\n";
    } else if (scm_is_true(scm_promise_p(obj))) {
        out << indent << "<promise>\n";
    } else if (scm_is_true(scm_hash_table_p(obj))) {
        out << indent << "<hash_table>\n";
    } else if (scm_is_true(scm_bytevector_p(obj))) {
        out << indent << "<bytevector>";
        size_t len = scm_c_bytevector_length(obj);
        for (size_t i = 0; i < len; ++i) {
            out << std::format("{:x}", scm_c_bytevector_ref(obj, i))
                << ' ';
        }
        out << '\n';
    } else if (scm_is_true(scm_struct_p(obj))) {
        out << indent << "<struct>";
        SCM vtable = SCM_STRUCT_VTABLE(obj);
        SCM name   = scm_struct_vtable_name(vtable);
        if (scm_is_true(name)) {
            out << " " << name;
        } else {
            if (SCM_VTABLE_FLAG_IS_SET(vtable, SCM_VTABLE_FLAG_VTABLE)) {
                out << "vtable:";
            } else {
                out << "struct:";
            }

            out << std::format("{:x}", SCM_UNPACK(vtable)) << " "
                << SCM_VTABLE_LAYOUT(vtable) << " ";
        }

        auto struct_size = SCM_STRUCT_SIZE(obj);

        out << "\n";
        for (int i = 0; i < struct_size; ++i) {
            if (SCM_STRUCT_FIELD_IS_UNBOXED(obj, i)) {
                SCM field = scm_struct_ref(obj, scm_from_int(i));
                print(field, out, indent + "  ");
            } else {
                SCM field = SCM_STRUCT_SLOT_REF(obj, i);
                print(field, out, indent + "  ");
            }
        }

        out << "\n";
    } else {
        out << indent << "<unknown>\n";
    }
}

bool guile::is_plist(SCM list) {
    while (!scm_is_null(list)) {
        SCM element = scm_car(list);
        if (!scm_is_true(scm_symbol_p(element))) {
            return false;
        } else {
            SCM value = scm_cdr(list);
            if (scm_is_null(value)) {
                return false;
            }
            list = scm_cdr(value);
        }
    }
    return true;
}

bool guile::is_alist(SCM list) {
    while (!scm_is_null(list)) {
        SCM element = scm_car(list);
        if (!scm_is_pair(element)) {
            return false;
        }
        list = scm_cdr(list);
    }
    return true;
}

void guile::iterate_plist(SCM list, std::function<void(SCM, SCM)> lambda) {
    while (!scm_is_null(list)) {
        SCM key   = scm_car(list);
        list      = scm_cdr(list);
        SCM value = scm_car(list);
        list      = scm_cdr(list);
        lambda(key, value);
    }
}
