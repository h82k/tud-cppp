Diese Seite enthält eine Sammlung der typischen Fragen, die während des Praktikums auftauchen.

## Warum müssen Templates immer im Header implementiert werden? ##

Siehe [hier](http://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file/495048#495048)

## Non-const reference to temporary objects forbidden ##

```
class C {};
void methodTakingReference(C &aRef) {}

void testNonConstRefToTemporaryObject() {
	methodTakingReference(C());
}
```

Der Code produziert folgenden Fehler:
> error: invalid initialization of non-const reference of type 'C&' from an rvalue of type 'C'

Eine gute Erklärung findet sich [hier auf Stackoverflow](http://stackoverflow.com/questions/84427/is-it-legal-to-pass-a-newly-constructed-object-by-reference-to-a-function/1152218#1152218).
