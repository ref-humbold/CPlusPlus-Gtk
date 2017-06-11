let rec run_menu () =
  begin
    Menu_gui.display ();
    List.nth [run_board; run_stat; exit] (Menu_gui.click_button ()) @@ ()
  end
and run_stat () =
  begin
    Stat_gui.display ();
    List.nth [run_menu; run_stat] (Stat_gui.check_click ()) @@ ();
    run_menu ()
  end
and run_game size =
  begin
    Game.run size;
    run_menu ()
  end
and run_board () =
  begin
    Board_gui.display ();
    run_game @@ Board_gui.choose_size ()
  end
and exit () = ();;
