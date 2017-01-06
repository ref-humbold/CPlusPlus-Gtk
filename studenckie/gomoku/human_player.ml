let move size gameboard =
    let pos = Game_gui.choose_stone () in
    if Board.free pos gameboard
    then
        begin
            Game_gui.draw_stone size Board.Human pos;
            pos
        end;;
    else move game;;
