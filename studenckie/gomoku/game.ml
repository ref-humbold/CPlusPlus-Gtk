let win game ply (row, col) =
    let get_row r g = List.nth g r
    and get_col c g = List.map (fun lst -> List.nth lst c) g
    and get_sum s g =
        let rec gs s_ i g_ acc =
            match g_ with
            | [] -> acc
            | xs::xss ->
                try gs s_ (i+1) xss ((List.nth xs @@ s_-i)::acc) with
                | Failure _ | Invalid_argument _ -> gs s_ (i+1) xss acc in
        gs s 0 g []
    and get_diff d g =
        let rec gd d_ i g_ acc =
            match g_ with
            | [] -> acc
            | xs::xss ->
                try gd d_ (i+1) xss ((List.nth xs @@ i-d_)::acc) with
                | Failure _ | Invalid_argument _ -> gd d_ (i+1) xss acc in
        gd d 0 g [] in
    let rec check lst =
        match lst with
        | p0::p1::p2::p3::p4::p5::p6::ps ->
            begin
                match (p0, p1, p2, p3, p4, p5, p6) with
                | (None, Some t1, Some t2, Some t3, Some t4, Some t5, None) when
                    ply = t1 && t1 = t2 && t2 = t3 && t3 = t4 && t4 = t5 -> true
                | (Some t0, Some t1, Some t2, Some t3, Some t4, Some t5, None) when
                    ply = t1 && t1 = t2 && t2 = t3 && t3 = t4 && t4 = t5 && t1 <> t0 -> true
                | (None, Some t1, Some t2, Some t3, Some t4, Some t5, Some t6) when
                    ply = t1 && t1 = t2 && t2 = t3 && t3 = t4 && t4 = t5 && t1 <> t6 -> true
                | (Some t0, Some t1, Some t2, Some t3, Some t4, Some t5, Some t6) when
                    ply = t1 && t1 = t2 && t2 = t3 && t3 = t4 && t4 = t5 && t1 <> t0 && t1 <> t6 -> true
                | _ -> check @@ p1::p2::p3::p4::p5::p6::ps
            end
        | _ -> false in
    let get_all r c g = [get_row r g; get_col c g; get_sum (r+c) g; get_diff (r-c) g] in
    if List.exists check @@ get_all row col game
    then Some ply
    else None;;

let set_move (row, col) ply game =
    let rec set_col n r =
        match r with
        | [] -> raise Board.Incorrect_gameboard
        | x::xs ->
            if n = 0
            then (Some ply)::xs
            else x::(set_col (n-1) xs) in
    let rec set_row n g =
        match g with
        | [] -> raise Board.Incorrect_gameboard
        | x::xs ->
            if n = 0
            then (set_col col x)::xs
            else x::(set_row (n-1) xs) in
    set_row row game;;

let rec play (mvh, mvc) player game =
    let mpos =
        match player with
        | Board.Human -> print_string "Human\n"; Human_player.move game
        | Board.Comp -> print_string "Comp\n"; Comp_player.move game in
    let ngame = set_move mpos player game in
    let mvnum =
        match player with
        | Board.Human -> (mvh+1, mvc)
        | Board.Comp -> (mvh, mvc+1) in
    match win ngame player mpos with
    | None ->
        begin
            match player with
            | Board.Human -> play mvnum Board.Comp ngame
            | Board.Comp -> play mvnum Board.Human ngame
        end
    | Some ply -> (ply, fst mvnum, snd mvnum);;

let start n =
    let beg_time = Sys.time () in
    let (winner, mvh, mvc) = play (0, 0) Board.Human @@ Board.empty (n+2) in
    let end_time = Sys.time () in
    let tm = int_of_float @@ floor (end_time-.beg_time+.0.5) in
    (winner, mvh, mvc, tm);;
