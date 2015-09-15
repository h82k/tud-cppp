.PHONY: all publish copy-only-all

# Build PDF files (without copying)
all: pdf1 pdf2 pdf3 pdf4 pdf5 pdf6

# Build and copy PDF files
publish: cp1 cp2 cp3 cp4 cp5 cp6

# Copy all files to top-level directory without recompiling
copy-only-all: cponly1 cponly2 cponly3 cponly4 cponly5 cponly6

cponly%: 
	cp day$*/day$*.pdf ..

cp%: pdf%
	cp day$*/day$*.pdf ..

pdf%:
	cd day$* && latexmk -pdf

pvc%:
	cd day$* && latexmk -pdf -pvc

