let start_gui =
    begin
        Graphics.set_window_title "GOMOKU!";
        Graphics.open_graph " 600x400";
    end;;

let end_gui = Graphics.close_graph ();;

let new_button x y w h lbl clr =
    begin
        Graphics.set_color clr;
        Graphics.draw_rect x y w h;
        Graphics.fill_rect x y w h;
        Graphics.moveto (x+5) (y+5);
        Graphics.draw_string lbl;
    end;;
