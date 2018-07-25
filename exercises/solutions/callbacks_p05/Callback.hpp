/*
 * Callback.hpp
 */

#ifndef CALLBACK_HPP_
#define CALLBACK_HPP_

#include <memory>

/**
 * Base class for all types of callbacks.
 */
template<typename ParamT>
class CallbackBase {
public:
	virtual ~CallbackBase() {
	}
	
	virtual void call(ParamT t) = 0;
};

/**
 * Callback class that takes a function pointer
 */
template<typename ParamT>
class FunctionCallback: public CallbackBase<ParamT> {
public:
	FunctionCallback(void(*fp)(ParamT)) :
			fp(fp) {
	}
	
	virtual ~FunctionCallback() {
	}
	
	virtual void call(ParamT t) {
		fp(t);
	}
private:
	void (*fp)(ParamT);
};

/**
 * Callback class that takes a functor
 */
template<typename ParamT, typename FunctorT>
class FunctorCallback: public CallbackBase<ParamT> {
public:
	FunctorCallback(FunctorT& fp) :
			fp(fp) {
	}
	
	virtual ~FunctorCallback() {
	}
	
	virtual void call(ParamT t) {
		fp(t);
	}
private:
	FunctorT& fp;
};

/**
 * Callback class that takes an object and a method callback
 */
template<typename ParamT, typename ClassT>
class MethodCallback: public CallbackBase<ParamT> {
public:
	MethodCallback(void(ClassT::*mp)(ParamT), ClassT* obj) :
			mp(mp), obj(obj) {
	}
	
	virtual ~MethodCallback() {
	}
	
	virtual void call(ParamT t) {
		(obj->*mp)(t);
	}
private:
	void (ClassT::*mp)(ParamT);
	ClassT* obj;
};

/**
 * Central callback class that offers a constructor
 * for each type of callback.
 */
template<typename ParamT>
class Callback {
public:
	Callback(void(*fp)(ParamT)) :
			callbackPtr(new FunctionCallback<ParamT>(fp)) {
	}
	
	template<typename FunctorT>
	Callback(FunctorT& fp) :
			callbackPtr(new FunctorCallback<ParamT, FunctorT>(fp)) {
	}
	
	template<typename ClassT>
	Callback(void(ClassT::*mp)(ParamT), ClassT* obj) :
			callbackPtr(new MethodCallback<ParamT, ClassT>(mp, obj)) {
	}
	
	void operator()(ParamT t) {
		callbackPtr->call(t);
	}
private:
	std::shared_ptr<CallbackBase<ParamT> > callbackPtr;
};

#endif /* CALLBACK_HPP_ */
