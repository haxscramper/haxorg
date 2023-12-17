module;

#include <boost/describe.hpp>

export module boost.describe;

export namespace boost::describe {
	using ::boost::describe::describe_bases;
	using ::boost::describe::describe_enumerators;
	using ::boost::describe::describe_members;
	using ::boost::describe::modifiers;
	using ::boost::describe::has_describe_members;
	constexpr ::boost::describe::modifiers mod_any_access_exp = ::boost::describe::mod_any_access;
}