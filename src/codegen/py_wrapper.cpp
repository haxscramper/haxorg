#include "py_wrapper.hpp"

#include <format>

using namespace py;
using namespace pywrap;

py::object get_field(py::object obj, char const* field) {
    if (PyDict_Check(obj.ptr())) { // If it's a dictionary
        return obj[field];
    } else { // Assume it's a general object
        return obj.attr(field);
    }
}

ValueKind get_value_kind(py::object obj) {
    if (obj.ptr() == Py_None) {
        return ValueKind::None;
    } else if (PyBool_Check(obj.ptr())) {
        return ValueKind::Bool;
    } else if (PyObject_IsInstance(
                   obj.ptr(), (PyObject*)&PyBaseObject_Type)) {
        return ValueKind::Obj;
    } else if (PyLong_Check(obj.ptr())) {
        return ValueKind::Long;
    } else if (PyFloat_Check(obj.ptr())) {
        return ValueKind::Float;
    } else if (PyBytes_Check(obj.ptr())) {
        return ValueKind::Bytes;
    } else if (PyUnicode_Check(obj.ptr())) {
        return ValueKind::Unicode;
    } else if (PyList_Check(obj.ptr())) {
        return ValueKind::List;
    } else if (PyTuple_Check(obj.ptr())) {
        return ValueKind::Tuple;
    } else if (PySet_Check(obj.ptr())) {
        return ValueKind::Set;
    } else if (PyDict_Check(obj.ptr())) {
        return ValueKind::Dict;
    } else if (PyCallable_Check(obj.ptr())) {
        return ValueKind::Func;
    } else if (PyModule_Check(obj.ptr())) {
        return ValueKind::Module;
    } else if (PyType_Check(obj.ptr())) {
        return ValueKind::Type;
    } else if (PyComplex_Check(obj.ptr())) {
        return ValueKind::Complex;
    } else if (PyFrozenSet_Check(obj.ptr())) {
        return ValueKind::Frozenset;
    }

    return ValueKind::Unknown;
}


void print(py::object obj, std::ostream& out, std::string indent) {
    // switch (get_value_kind(obj)) {
    //     case ValueKind::TrueLiteral: {
    //        out << indent << "<boolean>: #t\n";
    //        break;
    //    }
    //    case ValueKind::FalseLiteral: {
    //        out << indent << "<boolean>: #f\n";
    //        break;
    //    }
    //    case ValueKind::Integer: {
    //        out << indent << "<integer>: " << scm_to_int(obj) << "\n";
    //        break;
    //    }
    //    case ValueKind::Real: {
    //        out << indent << "<real>: " << scm_to_double(obj) << "\n";
    //        break;
    //    }
    //    case ValueKind::Complex: {
    //        out << indent << "<complex>: "
    //            << scm_to_locale_string(scm_display(obj, SCM_UNDEFINED))
    //            << "\n";
    //        break;
    //    }
    //    case ValueKind::Char: {
    //        out << indent << "<character>: " << scm_to_char(obj) << "\n";
    //        break;
    //    }
    //    case ValueKind::String: {
    //        out << indent << "<string>: " << scm_to_locale_string(obj)
    //            << "\n";
    //        break;
    //    }
    //    case ValueKind::Symbol: {
    //        out << indent << "<symbol>: "
    //            << scm_to_locale_string(scm_symbol_to_string(obj)) <<
    //            "\n";
    //        break;
    //    }
    //    case ValueKind::Vector: {
    //        out << indent << "<vector>:\n";
    //        size_t len = scm_c_vector_length(obj);
    //        for (size_t i = 0; i < len; i++) {
    //            print(scm_c_vector_ref(obj, i), out, indent + "  ");
    //        }
    //        break;
    //    }
    //    case ValueKind::Plist: {
    //        out << indent << "<plist>:\n";
    //        indent += "  ";
    //        iterate_plist(obj, [&](SCM key, SCM value) {
    //            out << indent << scm_symbol_to_string(key) << ":\n";
    //            print(value, out, indent + "  ");
    //        });
    //        break;
    //    }
    //    case ValueKind::Alist: {
    //        out << indent << "<alist>:\n";
    //        for (; scm_is_true(scm_pair_p(obj)); obj = scm_cdr(obj)) {
    //            print(scm_car(obj), out, indent + "  ");
    //        }
    //        break;
    //    }
    //    case ValueKind::List: {
    //        out << indent << "<list>:\n";
    //        for (; scm_is_true(scm_pair_p(obj)); obj = scm_cdr(obj)) {
    //            print(scm_car(obj), out, indent + "  ");
    //        }
    //        break;
    //    }

    //    case ValueKind::GoopsInstance: {

    //        // Print the class of the object
    //        SCM class_of_obj = SCM_CLASS_OF(obj);
    //        SCM class_name   = scm_class_name(class_of_obj);
    //        SCM goops_slots  = scm_class_slots(class_of_obj);
    //        int slot_count   = scm_to_int(scm_length(goops_slots));

    //        out << indent << "<GOOPS Object> "
    //            << "Class: " << class_name << " " << slot_count
    //            << " slots\n";
    //        indent += "  ";

    //        SCM slot_name_fun = scm_variable_ref(
    //            scm_c_lookup("slot-definition-name"));

    //        for (int i = 0; i < slot_count; ++i) {
    //            SCM slot  = scm_list_ref(goops_slots, scm_from_int(i));
    //            SCM name  = scm_call_1(slot_name_fun, slot);
    //            SCM value = scm_slot_ref(obj, name);
    //            out << indent << name << "\n";
    //            print(value, out, indent + "  ");
    //        }
    //        break;
    //    }
    //    case ValueKind::Unspecified: {
    //        out << indent << "<unspecified>\n";
    //        break;
    //    }
    //    case ValueKind::Procedure: {
    //        out << indent << "<procedure>\n";
    //        break;
    //    }
    //    case ValueKind::Port: {
    //        out << indent << "<port>\n";
    //        break;
    //    }
    //    case ValueKind::Promise: {
    //        out << indent << "<promise>\n";
    //        break;
    //    }
    //    case ValueKind::HashTable: {
    //        out << indent << "<hash_table>\n";
    //        break;
    //    }
    //    case ValueKind::ByteVector: {
    //        out << indent << "<bytevector>";
    //        size_t len = scm_c_bytevector_length(obj);
    //        for (size_t i = 0; i < len; ++i) {
    //            out << std::format("{:x}", scm_c_bytevector_ref(obj, i))
    //                << ' ';
    //        }
    //        out << '\n';
    //        break;
    //    }
    //    case ValueKind::Struct: {
    //        out << indent << "<struct>";
    //        SCM vtable = SCM_STRUCT_VTABLE(obj);
    //        SCM name   = scm_struct_vtable_name(vtable);
    //        if (scm_is_true(name)) {
    //            out << " " << name;
    //        } else {
    //            if (SCM_VTABLE_FLAG_IS_SET(
    //                    vtable, SCM_VTABLE_FLAG_VTABLE)) {
    //                out << "vtable:";
    //            } else {
    //                out << "struct:";
    //            }

    //            out << std::format("{:x}", SCM_UNPACK(vtable)) << " "
    //                << SCM_VTABLE_LAYOUT(vtable) << " ";
    //        }

    //        auto struct_size = SCM_STRUCT_SIZE(obj);

    //        out << "\n";
    //        for (int i = 0; i < struct_size; ++i) {
    //            if (SCM_STRUCT_FIELD_IS_UNBOXED(obj, i)) {
    //                SCM field = scm_struct_ref(obj, scm_from_int(i));
    //                print(field, out, indent + "  ");
    //            } else {
    //                SCM field = SCM_STRUCT_SLOT_REF(obj, i);
    //                print(field, out, indent + "  ");
    //            }
    //        }

    //        out << "\n";
    //        break;
    //    }
    //    case ValueKind::Unknown: {
    //        out << indent << "<unknown>\n";
    //        break;
    //    }
    //}
}
