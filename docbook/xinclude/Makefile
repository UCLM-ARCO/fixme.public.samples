
all: book.pdf

book.pdf: book.xml
	xmllint --xinclude --noout --postvalid $<
	dblatex $<


clean:
	$(RM) book.pdf *~

