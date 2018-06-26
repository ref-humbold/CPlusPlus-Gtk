OCB = ocamlbuild
OCBFLAGS = -use-ocamlfind -I src -cflags -w,A
BUILD = $(OCB) $(OCBFLAGS)

all : gomoku.native

clean :
	$(OCB) -clean

gomoku.native :
	$(BUILD) gomoku.native

gomoku.byte :
	$(BUILD) gomoku.byte
