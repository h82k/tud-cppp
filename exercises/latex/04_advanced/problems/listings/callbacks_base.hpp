template<typename ParamT>
class CallbackBase {
public:
	...
	virtual void call(ParamT t) = 0;
};
