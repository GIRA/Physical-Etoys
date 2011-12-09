
LANGUAGE=fr

TARGET=arduino.tex

PREFIX?=.

INSTALL=install

all: arduino

arduino: $(TARGET) $(TARGET:.tex=.gls) 

	TEXFONTS=:../shared/fonts TEXINPUTS=:../shared/fonts pdflatex $(TARGET)

%.gls: %.tex
	TEXFONTS=:../shared/fonts TEXINPUTS=:../shared/fonts pdflatex $(<)
	makeglossaries $(<:.tex=)

install: $(TARGET:.tex=.pdf)
	$(INSTALL) -T --mode=644 $< $(PREFIX)/$(TARGET:.tex=-$(LANGUAGE).pdf) 

clean:
	rm -f *.aux *.log *.snm *.out *.toc *.nav *intermediate *~ *.glo *.ist

distclean: clean
	rm -f $(TARGET:.tex=.pdf)
