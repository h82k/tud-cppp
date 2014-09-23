# folder containing the exercise folders
SRC			= sources

# determines which files are removed during clean up
# c: remove all nonessential files except dvi, ps and pdf files.
# C: remove all nonessential files including dvi, ps and pdf files.
CLEAN_FLAG	= c

# the folder names of every exercises
EXERCISES	= $(wildcard $(SRC)/tag*/)
# all target names of every exercise
ALL			= $(notdir $(EXERCISES:%/=%))
# clean target names of every exercise
CLEAN_ALL	= $(addprefix clean_,$(ALL))



#
# Compiles every exercise and copies the pdf to the main directory
#
all: $(ALL)

#
# Removes nonessential files from every exercise
#
clean: $(CLEAN_ALL)

#
# Compiles the exercise of the given day and copies it to the main directory
#
# Example:
#	make tag1
#
tag%: $(SRC)/tag%
	cd $< && latexmk -pdf
	cp $</$@.pdf $@.pdf

#
# Removes nonessential files from the exercise of the given day
#
# Example:
#	make clean_tag2
#
clean_tag%: $(SRC)/tag%
	cd $< && latexmk -$(CLEAN_FLAG)

#
# Keeps latexmk running and recompiles the exercise of the given day
# when the input file changes.
# (Close with Ctrl+C, Trigger recompilation with 'X' + ENTER)
#
# Example:
#	make pvc_tag3
#
pvc_tag%: $(SRC)/tag%
	cd $< && latexmk -pvc -pdf
