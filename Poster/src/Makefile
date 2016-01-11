all: ../poster.pdf

../poster.pdf: poster.tex
	#cd ../out && bibtex poster; cd ../src
	pdflatex --output-directory ../out poster.tex
	#cd ../out && bibtex poster; cd ../src
	pdflatex --output-directory ../out poster.tex
	cp ../out/poster.pdf ..



.PHONY: clean
clean:
	@rm -f ../out/* ../poster.pdf

