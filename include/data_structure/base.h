#pragma once

struct fake_type {};

template<class derived>
struct ptr_base
{
	static derived *null;
	operator bool() { return this != null; }
};
template<class _1>
_1 *ptr_base<_1>::null;

template<class derived>
struct crtp {
	derived &self() { return static_cast<derived &>(*this); }
	const derived &self() const { return static_cast<const derived &>(*this); }
};

template<class ...base>
struct bases : base... {};

template<class base_type>
struct baseinfo : base_type {
	using base_type::base_type;
	using base = baseinfo<base_type>;
};

template<class ...base>
struct baseinfos : baseinfo<bases<base...>> {};

template<class _1, template<class> class ...base>
struct arg1s : base<_1>... {};
template<class _1, class _2, template<class, class> class ...base>
struct arg2s : base<_1, _2>... {};

