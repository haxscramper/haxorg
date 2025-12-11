#pragma once

#include <haxorg/lexbase/Token.hpp>

namespace org::parse {

template <typename K, typename V>
struct TokenGroup {
    using TokenT         = Token<K, V>;
    using IdT            = TokenId<K, V>;
    using StoreT         = hstd::dod::Store<IdT, TokenT>;
    using iterator       = typename StoreT::ContentT::iterator;
    using const_iterator = typename StoreT::ContentT::const_iterator;

    StoreT tokens;

    DESC_FIELDS(TokenGroup, (tokens));

    iterator begin() { return tokens.content.begin(); }
    iterator end() { return tokens.content.end(); }
    iterator rbegin() { return tokens.content.rbegin(); }
    iterator rend() { return tokens.content.rend(); }
    iterator pos_iterator(IdT id) { return begin() + id.getIndex(); }
    iterator rpos_iterator(IdT id) {
        return rbegin() + (tokens.content().size() - id.getIndex() - 1);
    }

    const_iterator begin() const { return tokens.content.begin(); }
    const_iterator end() const { return tokens.content.end(); }
    const_iterator rbegin() const { return tokens.content.rbegin(); }
    const_iterator rend() const { return tokens.content.rend(); }
    const_iterator pos_iterator(IdT id) const {
        return begin() + id.getIndex();
    }
    const_iterator rpos_iterator(IdT id) const {
        return rbegin() + (tokens.content().size() - id.getIndex() - 1);
    }


    TokenGroup() {}
    TokenId<K, V> add(TokenT const& tok) { return tokens.add(tok); }

    hstd::Vec<IdT> add(hstd::Vec<TokenT> const& tok) {
        hstd::Vec<IdT> result;
        for (const auto& t : tok) { result.push_back(tokens.add(t)); }
        return result;
    }

    hstd::Vec<IdT> add(std::span<TokenT> const& tok) {
        hstd::Vec<IdT> result;
        for (const auto& t : tok) { result.push_back(tokens.add(t)); }
        return result;
    }


    TokenT& at(IdT pos) { return tokens.at(pos); }

    std::span<TokenT> at(hstd::HSlice<IdT, IdT> slice) {
        assert(slice.first.getStoreIdx() == slice.last.getStoreIdx());
        tokens.at(slice(slice.first.getIndex(), slice.last.getIndex()));
    }

    int  size() const { return tokens.size(); }
    void resize(int size, TokenT const& value = TokenT()) {
        tokens.resize(size, value);
    }
};


template <typename K, typename V>
struct TokenStore {
    hstd::Vec<TokenGroup<K, V>> groups;
    Token<K, V>&                at(TokenId<K, V> id) {
        return groups.at(id.getStoreIdx());
    }

    std::span<Token<K, V>> at(
        hstd::HSlice<TokenId<K, V>, TokenId<K, V>> slice) {
        assert(slice.first.getStoreIdx() == slice.last.getStoreIdx());
        groups.at(slice.first.getStoreIdx()).at(slice);
    }
};

template <typename K, typename V>
struct Tokenizer {
    TokenGroup<K, V>* out;
    Tokenizer(TokenGroup<K, V>* _out) : out(_out) {}
    hstd::Vec<hstd::Vec<Token<K, V>>*> buffer;
    void                               clearBuffer() { buffer.pop_back(); }
    /// \brief Get reference to token with specified ID
    Token<K, V>& at(TokenId<K, V> id) { return out->at(id); }
    /// \brief Get ID of the last token
    TokenId<K, V> back() const { return out->tokens.back(); }
    int           size() const { return out->size(); }
    void          resize(int size, Token<K, V> value = Token<K, V>()) {
        out->resize(size, value);
    }

    /// \name Add new token element to the list
    ///
    /// \returns ID of the new token or Nil if element is added to the
    /// buffer instead.
    ///
    /// \warning Returns nil IDs or empty list with active buffer!
    ///@{
    TokenId<K, V> push(Token<K, V> const& tok) {
        if (buffer.empty()) {
            return out->add(tok);
        } else {
            buffer.back()->push_back(tok);
            return TokenId<K, V>::Nil();
        }
    }

    hstd::Vec<TokenId<K, V>> push(std::span<Token<K, V>> const& tok) {
        if (buffer.empty()) {
            return out->add(tok);
        } else {
            buffer.back()->append(tok);
            return Vec<TokenId<K, V>>();
        }
    }

    hstd::Vec<TokenId<K, V>> push(hstd::CVec<Token<K, V>> tok) {
        if (buffer.empty()) {
            return out->add(tok);
        } else {
            buffer.back()->append(tok);
            return Vec<TokenId<K, V>>();
        }
    }
    ///@}
};

} // namespace org::parse


template <hstd::StdFormattable K, hstd::StdFormattable V>
struct std::formatter<org::parse::TokenGroup<K, V>>
    : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(
        const org::parse::TokenGroup<K, V>& p,
        FormatContext&                      ctx) {
        std::formatter<std::string> fmt;
        for (const auto& [idx, tok] : p.tokens.pairs()) {
            fmt.format(std::format("{:<16}", idx), ctx);
            fmt.format(" | ", ctx);
            fmt.format(*tok, ctx);
            fmt.format("\n", ctx);
        }

        return fmt.format("", ctx);
    }
};
