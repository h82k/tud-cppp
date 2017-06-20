void foo(struct Point *p) {
...
}

int main(void) {
	struct Point point;
	foo(&point);
}
