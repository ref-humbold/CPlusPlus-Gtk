let choose () = (read_int (), read_int ());;

let move game =
    let pos = choose () in
    begin
        Game_gui.draw_stone size Board.Comp pos;
        pos
    end;;
