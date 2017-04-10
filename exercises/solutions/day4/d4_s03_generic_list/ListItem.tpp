
template<typename T>
ListItem<T>::ListItem(ListItem<T> *prev, ListItem<T> *next, const T &content):
	previous(prev), next(next), content(content)
{
	if (previous) {
		previous->next = this;
	}
	if (next) {
		next->previous = this;
	}
}

template<typename T>
ListItem<T>::~ListItem() {
	if (previous) {
		previous->next = next;
	}
	if (next) {
		next->previous = previous;
	}
}


template<typename T>
T& ListItem<T>::getContent() {
	return content;
}

template<typename T>
ListItem<T>* ListItem<T>::getNext() {
	return next;
}

template<typename T>
ListItem<T>* ListItem<T>::getPrevious() {
	return previous;
}
