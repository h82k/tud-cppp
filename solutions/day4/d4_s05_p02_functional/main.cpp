template<typename InIt, typename OutIt>
OutIt map(InIt first, InIt last, OutIt out_first, int(*func)(int i)) {
	while(first != last) {
        *out_first++ = func(*first++);
    }
	return out_first;
}

template<typename ItType, typename OutIt>
ItType filter(ItType first, ItType last, OutIt out_first, bool(*pred)(int i)) {
	while(first != last) {
        if(pred(*first)) {
			*out_first++ = *first++;
		} else {
			++first;
		}
    }
	return out_first; 
}

template<typename ItType, typename T>
T reduce(ItType first, ItType last, T init, T(*func)(T &i, int j)) {
	while(first != last) {
        init = func(init, *first++);
    }
    return init;
}

int main() {
	return 0;
}
