.PHONY: all clean cleanall

all: tp1-scheduling

tp1-scheduling: tpScheduling.tex
	pdflatex tpScheduling.tex #> /dev/null
	pdflatex tpScheduling.tex #> /dev/null

	rm -f *.aux *.log *.nav *.out *.snm *.toc *.vrb

clean:
	rm -f *.aux *.log *.nav *.out *.snm *.toc *.vrb

cleanall:
	rm -f tpScheduling.pdf
	rm -f *.aux *.log *.nav *.out *.snm *.toc *.vrb
