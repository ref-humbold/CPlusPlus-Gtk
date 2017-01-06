let header () = Gui.draw_text (Gui.sc 1 2, Gui.sc 7 8) "GOMOKU!!!" Graphics.green;;

let footer () = Gui.draw_text (Gui.sc 1 2, Gui.sc 1 8) "(C) RAFAL KALETA, WROCLAW 2017" Graphics.black;;

let display () =
    begin
        Gui.clear_window Graphics.blue;
        header ();
        Gui.draw_button (Gui.sc 1 2, Gui.sc 3 4) (400, 100) "NOWA GRA" Graphics.magenta;
        Gui.draw_button (Gui.sc 1 2, Gui.sc 1 2) (400, 100) "STATYSTYKI" Graphics.magenta;
        Gui.draw_button (Gui.sc 1 2, Gui.sc 1 4) (400, 100) "WYJSCIE" Graphics.magenta;
        footer ();
    end;;
