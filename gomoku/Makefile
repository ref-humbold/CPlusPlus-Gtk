GOMOKU = _build/install/default/bin/gomoku

.PHONY : all clean refresh

all : gomoku

clean :
	rm -f gomoku
	dune clean

refresh : clean all

gomoku :
	dune build
	@ln -s $(GOMOKU) gomoku
