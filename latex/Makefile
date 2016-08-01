.PHONY: all publish copy-only-all

# Build PDF files (without copying)
all: create-pdf-day1 create-pdf-day2 create-pdf-day3 create-pdf-day4 create-pdf-day5 create-pdf-day6 create-pdf-elevator 

# Build and copy PDF files
publish: copy-pdf-day1 copy-pdf-day2 copy-pdf-day3 copy-pdf-day4 copy-pdf-day5 copy-pdf-day6 copy-pdf-elevator 

# Copy all files to top-level directory without recompiling
copy-only-all: cponly-day1 cponly-day2 cponly-day3 cponly-day4 cponly-day1 cponly-day6 cponly-elevator

# cponly%: 
# 	cp day$*/day$*.pdf ..
# 
# cp%: pdf%
# 	cp day$*/day$*.pdf ..

create-pdf-%:
	cd $* && latexmk -pdf

# pvc%:
# 	cd $* && latexmk -pdf -pvc

