.PHONY: all publish

all: pdf1 pdf2 pdf3 pdf4 pdf5 pdf6
publish: cp1 cp2 cp3 cp4 cp5 cp6

cp%: pdf%
	cp day$*/day$*.pdf ..

pdf%:
	cd day$* && latexmk -pdf

pvc%:
	cd day$* && latexmk -pdf -pvc

