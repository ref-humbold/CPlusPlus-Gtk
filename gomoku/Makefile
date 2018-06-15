CAMLC = ocamlc
CAMLOPT = ocamlopt
CAMLFLAGS = -w A -I $(OBJ)
CMPL = $(CAMLOPT) $(CAMLFLAGS)
GRAPHICS = graphics.cmxa -cclib -lgraphics -cclib -L/usr/X11R6/lib -cclib -lX11
SRC = src
OBJ = obj

all : prepare gomoku

prepare :
	mkdir -p $(OBJ)

clean :
	rm -rf $(OBJ)

refresh : clean all

gomoku : gui.cmx board.cmx stat.cmx menu_gui.cmx board_gui.cmx stat_gui.cmx game_gui.cmx \
comp_player.cmx human_player.cmx game.cmx gui_runner.cmx gomoku.cmx
	$(CMPL) $(GRAPHICS) $(OBJ)/gui.cmx $(OBJ)/board.cmx $(OBJ)/stat.cmx $(OBJ)/menu_gui.cmx \
	  $(OBJ)/board_gui.cmx $(OBJ)/stat_gui.cmx $(OBJ)/game_gui.cmx $(OBJ)/comp_player.cmx \
	  $(OBJ)/human_player.cmx $(OBJ)/game.cmx $(OBJ)/gui_runner.cmx $(OBJ)/gomoku.cmx -o gomoku

gomoku.cmx : $(SRC)/gomoku.ml
	$(CMPL) $(GRAPHICS) -c $(SRC)/gomoku.ml -o gomoku.cmx
	@mv $(SRC)/gomoku.cmx $(SRC)/gomoku.cmi $(SRC)/gomoku.o $(OBJ)

gui_runner.cmx : $(SRC)/gui_runner.ml
	$(CMPL) $(GRAPHICS) -c $(SRC)/gui_runner.ml -o gui_runner.cmx
	@mv $(SRC)/gui_runner.cmx $(SRC)/gui_runner.cmi $(SRC)/gui_runner.o $(OBJ)

game.cmx : $(SRC)/game.ml
	$(CMPL) -c $(SRC)/game.ml -o game.cmx
	@mv $(SRC)/game.cmx $(SRC)/game.cmi $(SRC)/game.o $(OBJ)

human_player.cmx : $(SRC)/human_player.ml
	$(CMPL) -c $(SRC)/human_player.ml -o human_player.cmx
	@mv $(SRC)/human_player.cmx $(SRC)/human_player.cmi $(SRC)/human_player.o $(OBJ)

comp_player.cmx : $(SRC)/comp_player.ml
	$(CMPL) -c $(SRC)/comp_player.ml -o comp_player.cmx
	@mv $(SRC)/comp_player.cmx $(SRC)/comp_player.cmi $(SRC)/comp_player.o $(OBJ)

game_gui.cmx : $(SRC)/game_gui.ml
	$(CMPL) $(GRAPHICS) -c $(SRC)/game_gui.ml -o game_gui.cmx
	@mv $(SRC)/game_gui.cmx $(SRC)/game_gui.cmi $(SRC)/game_gui.o $(OBJ)

stat_gui.cmx : $(SRC)/stat_gui.ml
	$(CMPL) $(GRAPHICS) -c $(SRC)/stat_gui.ml -o stat_gui.cmx
	@mv $(SRC)/stat_gui.cmx $(SRC)/stat_gui.cmi $(SRC)/stat_gui.o $(OBJ)

board_gui.cmx : $(SRC)/board_gui.ml
	$(CMPL) $(GRAPHICS) -c $(SRC)/board_gui.ml -o board_gui.cmx
	@mv $(SRC)/board_gui.cmx $(SRC)/board_gui.cmi $(SRC)/board_gui.o $(OBJ)

menu_gui.cmx : $(SRC)/menu_gui.ml
	$(CMPL) $(GRAPHICS) -c $(SRC)/menu_gui.ml -o menu_gui.cmx
	@mv $(SRC)/menu_gui.cmx $(SRC)/menu_gui.cmi $(SRC)/menu_gui.o $(OBJ)

stat.cmx : $(SRC)/stat.ml
	$(CMPL) -c $(SRC)/stat.ml -o stat.cmx
	@mv $(SRC)/stat.cmx $(SRC)/stat.cmi $(SRC)/stat.o $(OBJ)

board.cmx : $(SRC)/board.ml
	$(CMPL) -c $(SRC)/board.ml -o board.cmx
	@mv $(SRC)/board.cmx $(SRC)/board.cmi $(SRC)/board.o $(OBJ)

gui.cmx : $(SRC)/gui.ml
	$(CMPL) $(GRAPHICS) -c $(SRC)/gui.ml -o gui.cmx
	@mv $(SRC)/gui.cmx $(SRC)/gui.cmi $(SRC)/gui.o $(OBJ)
