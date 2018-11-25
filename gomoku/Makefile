DUNE = dune
GOMOKU = _build/install/default/bin/gomoku

.PHONY : all clean refresh

all : gomoku

clean :
	rm -f gomoku
	$(DUNE) clean

refresh : clean all

gomoku :
	$(DUNE) build
	@ln -s $(GOMOKU)
