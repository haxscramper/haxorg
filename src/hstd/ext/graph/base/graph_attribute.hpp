#pragma once

#include "graph_common.hpp"

namespace hstd::ext::graph {

class IAttributeObject;

/// \brief Base class for all attributes associated with vertices. The
/// attribute might be an individual value, or a complex composite object,
/// depending on the use case.
struct IAttribute {
  public:
    virtual ~IAttribute() = default;

    virtual std::string getRepr() const = 0;

    template <typename T>
    bool isInstance() const {
        return dynamic_cast<T const*>(this) != nullptr;
    }

#if ORG_BUILD_WITH_PROTOBUF
    virtual void writeSerial(proto::IAttribute* out, IGraph const* graph) const = 0;
    virtual void readSerial(
        proto::IAttribute const*   in,
        IGraph const*              graph,
        IGraphSerialReaderFactory* factory,
        IAttributeObject const*    vertex) = 0;
#endif
};

/// \brief Base class for trackers implementing reverse lookup for
/// attribute values.
class IAttributeTracker {
  public:
    virtual void                trackVertex(VertexID const& vertex)   = 0;
    virtual void                untrackVertex(VertexID const& vertex) = 0;
    virtual hstd::Vec<VertexID> getVertices(IAttribute const& prop)   = 0;
    virtual AttributeTrackerID  getTrackerID() const                  = 0;
};

class IAttributeObject {
  public:
    virtual hstd::Vec<hstd::SPtr<IAttribute>> getAttributes() const            = 0;
    virtual void addAttribute(hstd::SPtr<IAttribute> const& attr)              = 0;
    virtual void setAttributes(hstd::Vec<hstd::SPtr<IAttribute>> const& attrs) = 0;


    hstd::Vec<hstd::Str> getAttributeRepr() const;

    /// \brief Get first instance of the attribute with dynamic type `T`.
    template <typename T>
        requires std::derived_from<T, IAttribute>
    hstd::Opt<hstd::SPtr<T>> getOptionalAttribute() const {
        for (auto const& attr : getAttributes()) {
            if (attr->isInstance<T>()) { return std::dynamic_pointer_cast<T>(attr); }
        }

        return std::nullopt;
    }

    template <typename T>
        requires std::derived_from<T, IAttribute>
    bool hasOptionalAttribute() const {
        return getOptionalAttribute<T>().has_value();
    }

    /// \brief Get all attributes with dynamic type T
    template <typename T>
        requires std::derived_from<T, IAttribute>
    hstd::Vec<hstd::SPtr<T>> getAllAttributes() const {
        hstd::Vec<hstd::SPtr<T>> result;
        for (auto const& attr : getAttributes()) {
            if (attr->isInstance<T>()) {
                result.push_back(std::dynamic_pointer_cast<T>(attr));
            }
        }

        return result;
    }

    /// \brief Get one attribute with dynamic type T, the attribute is
    /// expected to be unique.
    template <typename T>
        requires std::derived_from<T, IAttribute>
    hstd::SPtr<T> getUniqueAttribute(std::string const& err_ctx = "") const {
        hstd::SPtr<T> result;
        for (auto const& attr : getAttributes()) {
            if (attr->isInstance<T>()) {
                if (result == nullptr) {
                    result = std::dynamic_pointer_cast<T>(attr);
                } else {
                    throw graph_error::init(
                        hstd::fmt(
                            "Graph object is expected to have exactly one "
                            "attribute of type {}, but found two. {}",
                            hstd::value_metadata<T>::typeName(),
                            err_ctx));
                }
            }
        }

        if (result == nullptr) {
            throw graph_error::init(
                hstd::fmt(
                    "Graph object is expected to have exactly one "
                    "attribute of type {}, but found none. {}. Has "
                    "attributes {}.",
                    hstd::value_metadata<T>::typeName(),
                    err_ctx,
                    getAttributeRepr()));
        }

        return result;
    }

    template <typename T = IAttribute>
        requires std::derived_from<T, IAttribute>
    void addUniqueAttribute(hstd::SPtr<T> const& attr, std::string const& err_ctx = "") {
        for (auto const& existing : getAttributes()) {
            if (typeid(attr.get()) == typeid(existing.get())) {
                throw graph_error::init(
                    hstd::fmt(
                        "Graph object is required to have only one "
                        "attribute of type {}, but the code is attempting "
                        "to add a new instance. {}",
                        typeid(attr.get()).name(),
                        err_ctx));
            }
        }

        addAttribute(attr);
    }

    template <typename T = IAttribute>
        requires std::derived_from<T, IAttribute>
    void addOrResetUniqueAttribute(hstd::SPtr<T> const& attr) {
        hstd::Vec<hstd::SPtr<IAttribute>> new_list;
        for (auto const& existing : getAttributes()) {
            if (typeid(attr.get()) == typeid(existing.get())) {
                new_list.push_back(attr);
            } else {
                new_list.push_back(existing);
            }
        }
        setAttributes(new_list);
    }

#if ORG_BUILD_WITH_PROTOBUF
    void writeSerial(
        ::google::protobuf::RepeatedPtrField<::hstd::ext::graph::proto::IAttribute>* out,
        IGraph const* graph) const;

    void readSerial(
        ::google::protobuf::RepeatedPtrField<::hstd::ext::graph::proto::IAttribute> const*
                                   in,
        IGraph const*              graph,
        IGraphSerialReaderFactory* factory,
        IAttributeObject const*    vertex);
#endif
};

class TrivialAttributeObject : public virtual IAttributeObject {
  public:
    hstd::Vec<hstd::SPtr<IAttribute>> attrs;

    hstd::Vec<hstd::SPtr<IAttribute>> getAttributes() const override { return attrs; }

    void addAttribute(hstd::SPtr<IAttribute> const& attr) override {
        attrs.push_back(attr);
    }

    void setAttributes(hstd::Vec<hstd::SPtr<IAttribute>> const& attrs) override {
        this->attrs = attrs;
    }
};


} // namespace hstd::ext::graph
