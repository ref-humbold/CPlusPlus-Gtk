let play =
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

print_string @@ Board.string_of_player play^"wins!!\n";;