template<typename SeqT, typename RetT>
RetT reduce(SeqT &seq, RetT initialVal, RetT(*func)(RetT &i, double j));
