CAMLC = ocamlc
CAMLOPT = ocamlopt
CAMLFLAGS = -w A

GRAPHICS = graphics.cmxa -cclib -lgraphics -cclib -L/usr/X11R6/lib -cclib -lX11

all : gomoku

clean :
	rm -f *.cmi *.cmx *.cmo *.o

gomoku :
	$(CAMLOPT) $(CAMLFLAGS) $(GRAPHICS) -o gomoku

gomoku.cmx : gui.cmx
	$(CAMLOPT) $(CAMLFLAGS) $(GRAPHICS) -c gomoku.ml -o gomoku.cmx

stat.cmx : stat.ml
	$(CAMLOPT) $(CAMLFLAGS) -c stat.ml -o stat.cmx

stat_gui.cmx : stat_gui.ml
	$(CAMLOPT) $(CAMLFLAGS) $(GRAPHICS) -c stat_gui.ml -o stat_gui.cmx

menu_gui.cmx : menu_gui.ml
	$(CAMLOPT) $(CAMLFLAGS) $(GRAPHICS) -c menu_gui.ml -o menu_gui.cmx

board.cmx : board.ml
	$(CAMLOPT) $(CAMLFLAGS) -c board.ml -o board.cmx

board_gui.cmx : board_gui.ml
	$(CAMLOPT) $(CAMLFLAGS) $(GRAPHICS) -c board_gui.ml -o board_gui.cmx

game_gui.cmx : game_gui.ml
	$(CAMLOPT) $(CAMLFLAGS) $(GRAPHICS) -c game_gui.ml -o game_gui.cmx

game.cmx : game.ml game_gui.cmx
	$(CAMLOPT) $(CAMLFLAGS) -c game.ml -o game.cmx

human_player.cmx : human_player.ml
	$(CAMLOPT) $(CAMLFLAGS) -c human_player.ml -o human_player.cmx

comp_player.cmx : comp_player.ml
	$(CAMLOPT) $(CAMLFLAGS) -c comp_player.ml -o comp_player.cmx

gui.cmx : gui.ml
	$(CAMLOPT) $(CAMLFLAGS) $(GRAPHICS) -c gui.ml -o gui.cmx
