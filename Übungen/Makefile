tag%:
	cd sources/tag$* && latexmk -pdf
	cp sources/$@/$@.pdf $@.pdf

pvc_tag%:
	cd sources/tag$* && latexmk -pvc -pdf

clean_tag%:
	cd sources/tag$* && latexmk -c

clean-all_tag%: 
	cd sources/tag$* && latexmk -C
