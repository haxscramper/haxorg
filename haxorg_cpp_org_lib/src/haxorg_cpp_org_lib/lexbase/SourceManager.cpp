#include <haxorg_cpp_org_lib/lexbase/SourceManager.hpp>
#include <hstd_cpp_lib/stdlib/formatting/Formatter.hpp>

std::string org::parse::SourceManager::getPath(SourceFileId const& id) const {
    LOGIC_ASSERTION_CHECK_FMT(
        path_ids.contains_right(id), "Cannot get file path for ID {}", id);
    return path_ids.at_left(id);
}

const std::string& org::parse::SourceManager::getSourceContent(
    SourceFileId const& id) const {
    return store.at(id).content;
}

const std::string& org::parse::SourceManager::getContentTextForPath(
    std::string const& path) const {
    return store.at(getId(path)).content;
}

org::parse::SourceFileId org::parse::SourceManager::addSource(
    std::string const& path,
    std::string const& content) {

    LOGIC_ASSERTION_CHECK_FMT(
        !path_ids.get_right(path).has_value()
            || store.at(path_ids.at_right(path)).content == content,
        "Cannot add source with name '{}' but different content, the "
        "entry is already registered to ID {}",
        path,
        path_ids.at_right(path));

    if (auto id = path_ids.get_right(path); id.has_value()) {
        return id.value();
    } else {
        auto result = store.add(SourceFile{.path = path, .content = content});
        LOGIC_ASSERTION_CHECK_FMT(
            !path_ids.get_left(result).has_value(),
            "ID has already been used, store created duplicate ID {} for "
            "path "
            "{}",
            result,
            path);

        path_ids.add_unique(path, result);
        return result;
    }
}

org::parse::SourceFileId org::parse::SourceManager::getId(std::string const& path) const {
    return path_ids.at_right(path);
}

#if ORG_BUILD_WITH_PROTOBUF

void hstd::serde::proto_serde<orgproto::SourceManager, org::parse::SourceManager>::read(
    orgproto::SourceManager const& in,
    org::parse::SourceManager*     out) {}

void hstd::serde::proto_serde<orgproto::SourceManager, org::parse::SourceManager>::write(
    orgproto::SourceManager*         out,
    org::parse::SourceManager const& in) {
    for (auto const& [file_id, file_content] : in.store.pairs()) {
        auto p = out->add_path_ids();
        p->set_content(file_content->content);
        p->set_source_name(file_content->path);
        p->mutable_file_id()->set_id(file_id.value);
    }
}

#endif
