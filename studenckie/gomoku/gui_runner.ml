let run_menu () =
    begin
        Menu_gui.display ();
        List.nth [run_board; run_stat; Graphics.close_graph] (Menu_gui.click_button ()) @@ ()
    end;;

let run_stat () =
    begin
        Stat_gui.display ();
        Stat_gui.return ();
        run_menu ()
    end;;

let run_game size =
    begin
        run_menu ();
    end;;

let run_board () =
    begin
        Board_gui.display ();
        run_game @@ Board_gui.choose_size ()
    end;;
