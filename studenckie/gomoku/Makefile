CAMLC = ocamlc
CAMLOPT = ocamlopt
CAMLFLAGS = -w A

GRAPHICS = graphics.cmxa -cclib -lgraphics -cclib -L/usr/X11R6/lib -cclib -lX11

all : gomoku

clean :
	rm -f *.cmi *.cmx *.cmo *.o

gomoku : stat.cmx board.cmx human_player.cmx comp_player.cmx game.cmx gomoku.cmx
	$(CAMLOPT) $(CAMLFLAGS) $(GRAPHICS) stat.cmx board.cmx human_player.cmx comp_player.cmx game.cmx gomoku.cmx -o gomoku

gomoku.cmx : stat.cmx board.cmx human_player.cmx comp_player.cmx game.cmx
	$(CAMLOPT) $(CAMLFLAGS) $(GRAPHICS) -c gomoku.ml -o gomoku.cmx

gui.cmi : gui.mli
	$(CAMLOPT) $(CAMLFLAGS) $(GRAPHICS) -c gui.mli -o gui.cmi

gui.cmx : gui.ml gui.cmi
	$(CAMLOPT) $(CAMLFLAGS) $(GRAPHICS) -c gui.ml -o gui.cmx

menu_gui.cmi : menu_gui.mli gui.cmx
	$(CAMLOPT) $(CAMLFLAGS) $(GRAPHICS) -c menu_gui.mli -o menu_gui.cmi

menu_gui.cmx : menu_gui.ml menu_gui.cmi gui.cmx
	$(CAMLOPT) $(CAMLFLAGS) $(GRAPHICS) -c menu_gui.ml -o menu_gui.cmx

stat.cmi : stat.mli
	$(CAMLOPT) $(CAMLFLAGS) -c stat.mli -o stat.cmi

stat.cmx : stat.ml stat.cmi
	$(CAMLOPT) $(CAMLFLAGS) -c stat.ml -o stat.cmx

stat_gui.cmi : stat_gui.mli stat.cmx gui.cmx
	$(CAMLOPT) $(CAMLFLAGS) $(GRAPHICS) -c stat_gui.mli -o stat_gui.cmi

stat_gui.cmx : stat_gui.ml stat_gui.cmi stat.cmx gui.cmx
	$(CAMLOPT) $(CAMLFLAGS) $(GRAPHICS) -c stat_gui.ml -o stat_gui.cmx

board.cmi : board.mli
	$(CAMLOPT) $(CAMLFLAGS) -c board.mli -o board.cmi

board.cmx : board.ml board.cmi
	$(CAMLOPT) $(CAMLFLAGS) -c board.ml -o board.cmx

board_gui.cmi : board_gui.mli board.cmx gui.cmx
	$(CAMLOPT) $(CAMLFLAGS) $(GRAPHICS) -c board_gui.mli -o board_gui.cmi

board_gui.cmx : board_gui.ml board_gui.cmi board.cmx gui.cmx
	$(CAMLOPT) $(CAMLFLAGS) $(GRAPHICS) -c board_gui.ml -o board_gui.cmx

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
