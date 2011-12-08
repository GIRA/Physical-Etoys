TARGET=arduino.tex

all: arduino

arduino: $(TARGET)

	TEXFONTS=:./fonts TEXINPUTS=:./fonts pdflatex $(TARGET)

clean:
	rm -f *.aux *.log *.snm *.out *.toc *.nav *intermediate *~ *.glo *.ist

distclean: clean
	rm -f $(TARGET:.tex=.pdf)
