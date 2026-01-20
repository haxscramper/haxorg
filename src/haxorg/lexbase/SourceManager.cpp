#include <haxorg/lexbase/SourceManager.hpp>
#include <hstd/stdlib/Formatter.hpp>

std::string org::parse::SourceManager::getPath(
    const SourceFileId& id) const {
    return path_ids.at_left(id);
}

const std::string& org::parse::SourceManager::getSourceContent(
    const SourceFileId& id) const {
    return store.at(id).content;
}

const std::string& org::parse::SourceManager::getContentTextForPath(
    const std::string& path) const {
    return store.at(getId(path)).content;
}

org::parse::SourceFileId org::parse::SourceManager::addSource(
    const std::string& path,
    const std::string& content) {

    LOGIC_ASSERTION_CHECK_FMT(
        !path_ids.get_right(path).has_value()
            || store.at(path_ids.at_right(path)).content == content,
        "Cannot add source with name '{}' but different content, the "
        "entry is already registered to ID {}",
        path,
        path_ids.at_right(path));

    auto result = store.add(SourceFile{.path = path, .content = content});
    LOGIC_ASSERTION_CHECK_FMT(
        !path_ids.get_left(result).has_value(),
        "ID has already been used, store created duplicate ID {} for path "
        "{}",
        result,
        path);

    path_ids.add_unique(path, result);
    return result;
}

org::parse::SourceFileId org::parse::SourceManager::getId(
    const std::string& path) const {
    return path_ids.at_right(path);
}
