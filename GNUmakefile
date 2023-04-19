ASSEMBLY_SOURCES = $(wildcard *.s)

.SUFFIXES : .cc .s .qmd .tmp .html .pdf
.PHONY: clean view html pdf

all: html
html: benchmarking.html
pdf : benchmarking.pdf
	
view: benchmarking.pdf
	open -a Skim benchmarking.pdf

benchmarking.html: benchmarking.qmd $(ASSEMBLY_SOURCES)

benchmarking.pdf: benchmarking.qmd $(ASSEMBLY_SOURCES)

clean:
	rm -f benchmarking.md *.bbl *.bak* indent.log *.fls benchmarking.pdf *.pdf.tmp *.fdb_latexmk *.tex benchmarking.html

.qmd.pdf:
	quarto render $< --to pdf

.qmd.html:
	quarto render $< --to html

