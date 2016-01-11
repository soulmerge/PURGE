all: ../thesis.pdf

../thesis.pdf: thesis.tex abstract_en.tex abstract_de.tex Introduction/motivation.tex Introduction/question.tex Introduction/approach.tex Related/index.tex Scope/features.tex Scope/engines.tex Scope/usecases.tex Design/renderer.tex Design/relativeorientation.tex Design/defaults.tex Design/loop.tex Design/scenemodification.tex Design/scenegraph.tex Design/windows.tex Implementation/introduction.tex Implementation/renderer.tex Implementation/ogrerenderer.tex Implementation/scenegraph.tex Implementation/loop.tex Evaluation/tests.tex Conclusion.tex thesis.bib
	cd ../out && bibtex thesis; cd ../src
	pdflatex --output-directory ../out thesis.tex
	cd ../out && bibtex thesis; cd ../src
	pdflatex --output-directory ../out thesis.tex
	cp ../out/thesis.pdf ..



.PHONY: clean
clean:
	@find ../out -type f -delete
	@ln -s ../src/thesis.bib ../out/thesis.bib

