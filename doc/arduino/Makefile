
LANGUAGES = en fr

INSTALL = install

all: $(LANGUAGES:=-build)

install: $(LANGUAGES:=-install)

clean: $(LANGUAGES:=-clean)
	rm *.pdf	

# Default target that call make in each of the directory specified in LANGUAGE
%-build:
	@echo Compiling guides \(lang:$(@:-build=)\)
	${MAKE} -C $(@:-build=)

# Match all targets in xx-install, like those created in the install target.
%-install:
	@echo Installing guides \(lang: $(@:-install=)\)
	PREFIX=.. ${MAKE} -C $(@:-install=) install

%-clean:
	@echo Cleaning guides \(lang: $(@:-clean=)\)
	${MAKE} -C $(@:-clean=) clean


