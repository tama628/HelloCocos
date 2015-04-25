#pragma once

// デリゲート
template< class T, class Func >
class Delegate {

public:

	Delegate( T &t, Func func ) : _t(t), _func(func) {
	}

	~Delegate() {
	}

	template<typename... Params>
	void operator()(Params... params) {
		return (_t.*_func)(params);
	}

private:

	T &_t;
	Func const _func;

};
