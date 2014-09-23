#
# Recompiles exercise sheet for the given day and copies 
# the compiled exercise sheet to the main directory
#
# Examples:
#    make tag1
#    make pvc_tag1
# 
tag%:
	cd sources/tag$* && latexmk -pdf
	cp sources/$@/$@.pdf $@.pdf

#
# Keeps latexmk running and recompiles when the input file changes.
# (Close with Ctrl+C, Trigger recompilation with 'X' + ENTER)
#
pvc_tag%:
	cd sources/tag$* && latexmk -pvc -pdf

clean_tag%:
	cd sources/tag$* && latexmk -c

clean-all_tag%: 
	cd sources/tag$* && latexmk -C
