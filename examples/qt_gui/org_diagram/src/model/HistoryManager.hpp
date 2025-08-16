#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <haxorg/sem/ImmOrg.hpp>


struct HistoryManager {
    struct AstEdit {
        struct Deleted {
            org::imm::ImmUniqId id;
            DESC_FIELDS(Deleted, (id));
        };
        struct Added {
            org::imm::ImmUniqId id;
            DESC_FIELDS(Added, (id));
        };
        struct Changed {
            org::imm::ImmUniqId prev;
            org::imm::ImmUniqId next;
            DESC_FIELDS(Changed, (prev, next));
        };

        enum class Kind : unsigned short int
        {
            Deleted,
            Added,
            Changed
        };
        static_assert(
            std ::is_enum<Kind>::value,
            "BOOST_DESCRIBE_NESTED_ENUM should only be used with enums");
        __attribute__((unused)) friend inline auto boost_enum_descriptor_fn(
            Kind**) {
            return boost ::describe ::detail ::enum_descriptor_fn_impl(
                0,
                [] {
                    struct _boost_desc {
                        static constexpr auto value() noexcept {
                            return Kind ::Deleted;
                        }
                        static constexpr auto name() noexcept {
                            return "Deleted";
                        }
                    };
                    return _boost_desc();
                }(),
                [] {
                    struct _boost_desc {
                        static constexpr auto value() noexcept {
                            return Kind ::Added;
                        }
                        static constexpr auto name() noexcept {
                            return "Added";
                        }
                    };
                    return _boost_desc();
                }(),
                [] {
                    struct _boost_desc {
                        static constexpr auto value() noexcept {
                            return Kind ::Changed;
                        }
                        static constexpr auto name() noexcept {
                            return "Changed";
                        }
                    };
                    return _boost_desc();
                }());
        };
        using Data = std ::variant<Deleted, Added, Changed>;
        Deleted& getDeleted() {
            return ::hstd ::get_sub_variant<
                Deleted,
                std ::remove_cvref_t<decltype(*this)>>(data);
        }
        Deleted const& getDeleted() const {
            return ::hstd ::get_sub_variant<
                Deleted,
                std ::remove_cvref_t<decltype(*this)>>(data);
        }
        bool isDeleted() const {
            return std ::holds_alternative<Deleted>(data);
        }
        Added& getAdded() {
            return ::hstd ::get_sub_variant<
                Added,
                std ::remove_cvref_t<decltype(*this)>>(data);
        }
        Added const& getAdded() const {
            return ::hstd ::get_sub_variant<
                Added,
                std ::remove_cvref_t<decltype(*this)>>(data);
        }
        bool isAdded() const {
            return std ::holds_alternative<Added>(data);
        }
        Changed& getChanged() {
            return ::hstd ::get_sub_variant<
                Changed,
                std ::remove_cvref_t<decltype(*this)>>(data);
        }
        Changed const& getChanged() const {
            return ::hstd ::get_sub_variant<
                Changed,
                std ::remove_cvref_t<decltype(*this)>>(data);
        }
        bool isChanged() const {
            return std ::holds_alternative<Changed>(data);
        }
        static Kind getKind(Data const& __input) {
            return std ::visit(
                ::hstd ::overloaded{
                    [](Deleted const&) -> Kind { return Kind ::Deleted; },
                    [](Added const&) -> Kind { return Kind ::Added; },
                    [](Changed const&) -> Kind { return Kind ::Changed; },
                },
                __input);
        }
        Kind getKind() const { return getKind(data); }
        using variant_enum_type = Kind;
        using variant_data_type = Data;
        Kind        sub_variant_get_kind() const { return getKind(); }
        Data const& sub_variant_get_data() const { return data; }
        char const* sub_variant_get_name() const { return "data"; };
        Data data;
        /// \brief Parent node for the edit operations.
        hstd::Opt<org::imm::ImmUniqId> lhsParent;
        hstd::Opt<org::imm::ImmUniqId> rhsParent;
        DESC_FIELDS(AstEdit, (data, lhsParent, rhsParent));
    };

    HistoryManager();

    org::imm::ImmAstContext::Ptr       context;
    hstd::Vec<org::imm::ImmAstVersion> history;
    int                                active = 0;

    void addHistory(org::imm::ImmAstVersion const&);

    /// Set the current version of the document -- this will push a new
    /// history element, so the undo/redo sequence remaints intact.
    void setDocument(std::string const& document);

    org::imm::ImmAdapter getActiveRoot() const {
        return history.at(active).getRootAdapter();
    }

    org::imm::ImmAdapter getRoot(int index) const {
        return history.at(index).getRootAdapter();
    }

    hstd::Vec<AstEdit> getDifference(int lhsVer, int rhsVer) const;
};
