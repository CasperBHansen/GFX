BASE_DIR=~/Development/GFX
PACKNAME=fvx507

all:
	pdflatex report.tex

clean:
	rm -rf *.{aux,log,toc,o,out,swp}

pack:
	make clean
	cp -r $(BASE_DIR)/src .
	zip fvx507 -r makefile *.tex *.pdf src
	rm -r src

.PHONY: clean pack
