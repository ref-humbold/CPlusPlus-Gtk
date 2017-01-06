let play () =
    let size = read_int () in
    let (ply, hmoves, cmoves, time) = Game.start size in
    match ply with
    | Board.Human ->
        begin
            Stat.end_game true hmoves cmoves time;
            ply
        end
    | Board.Comp ->
        begin
            Stat.end_game false hmoves cmoves time;
            ply
        end;;

let main () =
    begin
        Gui.new_window ();
        Menu_gui.display ();
        Graphics.loop_at_exit [] (fun _ -> ())
    end;;

main ();;
