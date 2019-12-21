#pragma once

struct null_t {};

template <class _component_t, class _parent_component_t, bool _is_unique>
struct _component_identifier
{
	typedef _component_t current_component_t;
	typedef _parent_component_t parent_component_t;

	enum { is_unique = _is_unique };
};

template <class _component_t>
struct is_unique_component
{
	typedef typename _component_t::component_identifier_t	identifier_t;
	typedef typename identifier_t::parent_component_t		parent_t;

	enum
	{
		value = std::conditional<identifier_t::is_unique, std::true_type, is_unique_component<parent_t>>::type::value
	};
};
template <>
struct is_unique_component<null_t>
{
	enum { value = false };
};

template <class _component_t>
struct get_unique_component
{
	typedef typename _component_t::component_identifier_t	identifier_t;
	typedef typename identifier_t::parent_component_t		parent_t;

	typedef typename std::conditional<identifier_t::is_unique, _component_t, typename get_unique_component<parent_t>::type>::type type;
};
template <>
struct get_unique_component<null_t>
{
	typedef null_t type;
};

template <class _component_t>
struct get_component
{
	typedef typename std::conditional<
		is_unique_component<_component_t>::value,
		typename get_unique_component<_component_t>::type, _component_t>::type type;
};

#define DEFINE_COMPONENT(component_name, parent_component_name, unique_component) \
	public: \
		typedef _component_identifier<component_name, parent_component_name, unique_component> component_identifier_t; \
		static size_t getComponentId(void) { return reinterpret_cast<size_t>(&identifier); } \
		virtual const char* getComponentName_(void) { return #component_name; } \
		static const char* getComponentName(void) { return #component_name; } \
	private: \
		static component_identifier_t identifier; \

#define DECLARE_COMPONENT(component_name) \
	component_name::component_identifier_t component_name::identifier;

