.PHONY: all publish

SRC = $(wildcard day*/day*.tex)
PDF = $(patsubst %.tex, %.pdf, $(notdir $(SRC)))

all: day1.pdf day2.pdf day3.pdf day4.pdf day5.pdf day6.pdf
publish: publish_1 publish_2 publish_3 publish_4 publish_5 publish_6

publish_%: day%.pdf
	cp day$*/$< ..

%.pdf:
	cd $* && latexmk -pdf

pvc_%:
	cd day$* && latexmk -pdf -pvc

