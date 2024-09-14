#pragma once

#include <hstd/system/aux_utils.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/system/macros.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Span.hpp>
#include <hstd/stdlib/Exception.hpp>

struct ReflPathItem {
    /// \brief Target field is a vector.
    struct SubIndex {
        int index;
        DESC_FIELDS(SubIndex, (index));

        bool operator==(SubIndex const& other) const {
            return index == other.index;
        }
    };

    struct FieldName {
        std::string name;
        DESC_FIELDS(FieldName, (name));

        bool operator==(FieldName const& other) const {
            return name == other.name;
        }
    };

    SUB_VARIANTS(Kind, Data, data, getKind, SubIndex, FieldName);
    Data data;
    bool operator==(ReflPathItem const& it) const {
        return data == it.data;
    }
};

template <>
struct std::hash<ReflPathItem> {
    std::size_t operator()(ReflPathItem const& it) const noexcept {
        std::size_t result = 0;
        hax_hash_combine(result, it.data);
        return result;
    }
};


struct ReflPath {
    Vec<ReflPathItem> path;

    Pair<ReflPathItem, ReflPath> split() const {
        if (path.size() == 1) {
            return {path.front(), {}};
        } else {
            auto span = path.at(slice(1, 1_B));
            return Pair<ReflPathItem, ReflPath>{
                path.front(),
                ReflPath{Vec<ReflPathItem>{span.begin(), span.end()}}};
        }
    }

    ReflPath addFieldName(std::string const& name) const {
        return add(ReflPathItem{ReflPathItem::FieldName{name}});
    }

    ReflPath add(ReflPathItem const& item) const {
        auto res = *this;
        res.path.push_back(item);
        return res;
    }

    bool empty() const { return path.empty(); }

    bool operator==(ReflPath const& other) const {
        return path == other.path;
    }
};

template <>
struct std::hash<ReflPath> {
    std::size_t operator()(ReflPath const& it) const noexcept {
        std::size_t result = 0;
        hax_hash_combine(result, it.path);
        return result;
    }
};


template <typename T>
struct ReflVisitor {};


template <DescribedRecord T>
struct ReflVisitor<T> {
    /// \brief Apply callback to passed value if the path points to it,
    /// otherwise follow the path down the data structure.
    template <typename Func>
    static void visit(
        T const&        value,
        ReflPath const& path,
        Func const&     cb) {
        if (path.empty()) {
            cb(value);
        } else {
            auto [step, nested] = path.split();
            LOGIC_ASSERTION_CHECK(
                step.isFieldName(), "{}", step.getKind());
            for_each_field_value_with_bases<T>(
                [&]<typename F>(char const* name, F const& value) {
                    if (name == step.getFieldName().name) {
                        ReflVisitor<F>::visit(value, nested, cb);
                    }
                });
        }
    }

    static Vec<ReflPath> subitems(T const& value, ReflPath const& parent) {
        Vec<ReflPath> result;
        for_each_field_value_with_bases<T>(
            [&]<typename F>(char const* name, F const& value) {
                result.push_back(parent.addFieldName(name));
            });

        return result;
    }
};
