.PHONY: all publish copy-only-all clean

DIRS		= cheatsheet day1 day2 day3 day4 day5 elevator

all: create-pdfs

create-pdfs:
	for d in $(DIRS); do (cd $$d; latexmk -pdf *.tex ); done
	
# Build and copy PDF files
publish: create-pdfs cp-only-all

# Copying pdfs to upper directory
cp-only-all: 
	cp $(wildcard [day,elevator]*/*.pdf) ..

# cleaning compiled data besides pdfs
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

# clean all created data
clean_all: clean
	rm $(wildcard [cheatsheet,day,elevator]*/*.pdf)

