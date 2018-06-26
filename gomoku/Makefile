OCB = ocamlbuild
OCBFLAGS = -use-ocamlfind
BUILD = $(OCB) $(OCBFLAGS)

.PHONY: all clean refresh

all : gomoku.byte gomoku.native

clean :
	$(OCB) -clean

refresh : clean all

gomoku.byte :
	$(BUILD) gomoku.byte

gomoku.native :
	$(BUILD) gomoku.native
