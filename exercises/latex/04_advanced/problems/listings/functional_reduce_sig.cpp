template<typename InIt, typename RetT>
RetT reduce(InIt first, InIt last, RetT initialVal, RetT(*func)(RetT i, double j));
