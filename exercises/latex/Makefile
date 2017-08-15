.PHONY: all publish copy-only-all clean

all: create-pdfs

create-pdfs:
	latexmk -pdf cppp_exercises.tex
  
# Build and copy PDF files
publish: create-pdfs cp-only-all

# Copying pdfs to upper directory
cp-only-all: 
	cp cppp_exercises.pdf ..

# cleaning compiled data except for PDF file
clean:
	@echo "Removing unnecessary compilation data..."
	find . -type f -name '*.aux' -delete
	find . -type f -name '*.log' -delete
	find . -type f -name '*.dvi' -delete
	find . -type f -name '*.lof' -delete
	find . -type f -name '*.lot' -delete
	find . -type f -name '*.toc' -delete
	find . -type f -name '*.out' -delete
	find . -type f -name '*.fls' -delete
	find . -type f -name '*.fdb_latexmk' -delete

# clean all created data (incl. PDF file)
clean_all: clean
	rm cppp_exercises.pdf

