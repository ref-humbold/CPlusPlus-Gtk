let main () =
  begin
    Stat.prepare_data ();
    Gui.new_window ();
    Gui_runner.run_menu ();
    Graphics.close_graph ();
  end;;

let _ = main ();;
