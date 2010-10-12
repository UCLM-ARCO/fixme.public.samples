SOURCE=$(wildcard *.tex)

all: $(SOURCE:%.tex=%.pdf)

%.pdf: %.tex
	rubber --pdf $<

clean:
	rubber --pdf --clean $(SOURCE)
	$(RM) *~
