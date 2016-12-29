CAMLC = ocamlc
CAMLOPT = ocamlopt
CAMLFLAGS = -w A

all : gomoku

clean :
	rm -f *.cmi *.cmx *.cmo *.o

gomoku : stat.cmx board.cmx human_player.cmx comp_player.cmx game.cmx gomoku.cmx
	$(CAMLOPT) $(CAMLFLAGS) stat.cmx board.cmx human_player.cmx comp_player.cmx game.cmx gomoku.cmx -o gomoku

gomoku.cmx : stat.cmx board.cmx human_player.cmx comp_player.cmx game.cmx
	$(CAMLOPT) $(CAMLFLAGS) -c gomoku.ml -o gomoku.cmx

stat.cmi : stat.mli
	$(CAMLOPT) $(CAMLFLAGS) -c stat.mli -o stat.cmi

stat.cmx : stat.ml stat.cmi
	$(CAMLOPT) $(CAMLFLAGS) -c stat.ml -o stat.cmx

board.cmi : board.mli
	$(CAMLOPT) $(CAMLFLAGS) -c board.mli -o board.cmi

board.cmx : board.ml board.cmi
	$(CAMLOPT) $(CAMLFLAGS) -c board.ml -o board.cmx

human_player.cmi : human_player.mli board.cmx
	$(CAMLOPT) $(CAMLFLAGS) -c human_player.mli -o human_player.cmi

human_player.cmx : human_player.ml human_player.cmi board.cmx
	$(CAMLOPT) $(CAMLFLAGS) -c human_player.ml -o human_player.cmx

comp_player.cmi : comp_player.mli board.cmx
	$(CAMLOPT) $(CAMLFLAGS) -c comp_player.mli -o comp_player.cmi

comp_player.cmx : comp_player.ml comp_player.cmi board.cmx
	$(CAMLOPT) $(CAMLFLAGS) -c comp_player.ml -o comp_player.cmx

game.cmi : game.mli board.cmx human_player.cmx comp_player.cmx
	$(CAMLOPT) $(CAMLFLAGS) -c game.mli -o game.cmi

game.cmx : game.ml game.cmi board.cmx human_player.cmx comp_player.cmx
	$(CAMLOPT) $(CAMLFLAGS) -c game.ml -o game.cmx
