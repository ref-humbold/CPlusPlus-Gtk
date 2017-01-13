let win gameboard size player (row, col) =
    let get_row r g = List.nth g r
    and get_col c g = List.map (fun lst -> List.nth lst c) g
    and get_sum s g =
        let rec gs i g_ acc =
            match g_ with
            | [] -> List.rev acc
            | rw::rws ->
                if s-i < 0 || s-i > size+1
                then gs (i+1) rws acc
                else gs (i+1) rws ((List.nth rw @@ s-i)::acc) in
        gs 0 g []
    and get_diff d g =
        let rec gd i g_ acc =
            match g_ with
            | [] -> List.rev acc
            | rw::rws ->
                if i-d < 0 || i-d > size+1
                then gd (i+1) rws acc
                else gd (i+1) rws ((List.nth rw @@ i-d)::acc) in
        gd 0 g [] in
    let rec check lst =
        match lst with
        | p0::p1::p2::p3::p4::p5::p6::ps ->
            begin
                match (p0, p1, p2, p3, p4, p5, p6) with
                | (None, Some t1, Some t2, Some t3, Some t4, Some t5, None) when
                    player = t1 && t1 = t2 && t2 = t3 && t3 = t4 && t4 = t5 -> true
                | (Some t0, Some t1, Some t2, Some t3, Some t4, Some t5, None) when
                    player = t1 && t1 = t2 && t2 = t3 && t3 = t4 && t4 = t5 && t1 <> t0 -> true
                | (None, Some t1, Some t2, Some t3, Some t4, Some t5, Some t6) when
                    player = t1 && t1 = t2 && t2 = t3 && t3 = t4 && t4 = t5 && t1 <> t6 -> true
                | (Some t0, Some t1, Some t2, Some t3, Some t4, Some t5, Some t6) when
                    player = t1 && t1 = t2 && t2 = t3 && t3 = t4 && t4 = t5 && t1 <> t0 && t1 <> t6 -> true
                | _ -> check @@ p1::p2::p3::p4::p5::p6::ps
            end
        | _ -> false in
    let get_all r c g = [get_row r g; get_col c g; get_sum (r+c) g; get_diff (r-c) g] in
    if List.exists check @@ get_all row col gameboard
    then Some player
    else None;;

let set_move (row, col) player game =
    let rec set_col n r =
        match r with
        | [] -> raise @@ Board.Incorrect_gameboard "Game.set_move @ column"
        | x::xs ->
            if n = 0
            then (Some player)::xs
            else x::(set_col (n-1) xs) in
    let rec set_row n g =
        match g with
        | [] -> raise @@ Board.Incorrect_gameboard ("Game.set_move"^string_of_int row)
        | x::xs ->
            if n = 0
            then (set_col col x)::xs
            else x::(set_row (n-1) xs) in
    set_row row game;;

let start_game size =
    begin
        Game_gui.display size;
        Board.create @@ size+2
    end;;

let end_game (winner, mvh, mvc) =
    begin
        Stat.end_game winner mvh mvc;
        Game_gui.return winner
    end;;

let play_game size gameboard =
    let rec turn (mvh, mvc) last player gmbd =
        let mpos =
            match player with
            | Board.Human -> Human_player.move size gmbd
            | Board.Comp -> Comp_player.move last size gmbd
            | Board.Blocked -> raise @@ Board.Incorrect_player "Game.play_game" in
        let gmbd' = set_move mpos player gmbd in
        let _ = Game_gui.draw_stone size player mpos in
        let mvnum =
            match player with
            | Board.Human -> (mvh+1, mvc)
            | Board.Comp -> (mvh, mvc+1)
            | Board.Blocked -> raise @@ Board.Incorrect_player "Game.play_game" in
        match win gmbd' size player mpos with
        | None ->
            begin
                match player with
                | Board.Human -> turn mvnum mpos Board.Comp gmbd'
                | Board.Comp -> turn mvnum mpos Board.Human gmbd'
                | Board.Blocked -> raise @@ Board.Incorrect_player "Game.play_game"
            end
        | Some player -> (player, fst mvnum, snd mvnum) in
    turn (0, 0) (0, 0) Board.Human gameboard;;

let run size =
    let gameboard = start_game size in
    let game_result = play_game size gameboard in
    end_game game_result;;
