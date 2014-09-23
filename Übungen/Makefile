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
# Recompiles every exercise sheet and copies the pdf to the main directory
#
# Examples:
#	make -j 6
#
all: $(ALL)

#
# Cleans up (removes) all nonessential files of every exercise
#
clean: $(CLEAN_ALL)

#
# Recompiles exercise sheet for the given day and copies 
# the compiled exercise sheet to the main directory
#
# Examples:
#    make tag1
# 
tag%: $(SRC)/tag%
	cd $< && latexmk -pdf
	cp $</$@.pdf $@.pdf

#
# Keeps latexmk running and recompiles when the input file changes.
# (Close with Ctrl+C, Trigger recompilation with 'X' + ENTER)
#
# Examples:
#    make pvc_tag1
#
pvc_tag%: $(SRC)/tag%
	cd $< && latexmk -pvc -pdf

#
# Cleans up (removes) all nonessential files of the given day
#
clean_tag%: $(SRC)/tag%
	cd $< && latexmk -$(CLEAN_FLAG)
