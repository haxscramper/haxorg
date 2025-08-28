#include "reflection_visitor.hpp"

std::string hstd::TypeFieldNameRegistry::get_field_name(
    std::type_index type_id,
    std::size_t     field_index) {
    auto& registry = get_registry();
    auto  it       = registry.find(type_id);
    if (it == registry.end()) {
        throw std::runtime_error(
            "Type not registered: " + std::string{type_id.name()});
    }

    if (field_index >= it->second.field_count) {
        throw std::out_of_range(
            "Field index out of range, type "
            + std::string{it->second.type_name} + " has only "
            + std::to_string(it->second.field_count) + " fields.");
    }

    return it->second.field_names[field_index];
}

std::size_t hstd::TypeFieldNameRegistry::get_field_count(
    std::type_index type_id) {
    auto& registry = get_registry();
    auto  it       = registry.find(type_id);
    if (it == registry.end()) {
        throw std::runtime_error(
            "Type not registered: " + std::string{type_id.name()});
    }

    return it->second.field_count;
}
