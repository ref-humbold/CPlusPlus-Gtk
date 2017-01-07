let rec move size gameboard =
    let pos = Game_gui.choose_stone size in
    if Board.is_free pos gameboard
    then pos
    else move size gameboard;;
