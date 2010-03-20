
# OK    when lang=en
# wrong when lang=es


book.pdf: book.xml
	dblatex --debug -P latex.unicode.use=1 -P latex.encoding=utf8 $<


clean:
	$(RM) *.aux *.glo *.idx *.out *.toc *.log *.cb* *.pdf *~
