let win gameboard size player (row, col) =
  let get_row r g = List.nth g r
  and get_column c g = List.map (fun lst -> List.nth lst c) g
  and get_sum_diag s g =
    let rec gs i g_ acc =
      match g_ with
      | [] -> List.rev acc
      | rw::rws ->
        if s-i < 0 || s-i > size+1
        then gs (i + 1) rws acc
        else gs (i + 1) rws ((List.nth rw @@ s - i)::acc) in
    gs 0 g []
  and get_diff_diag d g =
    let rec gd i g_ acc =
      match g_ with
      | [] -> List.rev acc
      | rw::rws ->
        if i-d < 0 || i-d > size+1
        then gd (i + 1) rws acc
        else gd (i + 1) rws ((List.nth rw @@ i - d)::acc) in
    gd 0 g [] in
  let rec check lst =
    match lst with
    | None::Some t1::Some t2::Some t3::Some t4::Some t5::None::_ when
        player = t1 && t1 = t2 && t2 = t3 && t3 = t4 && t4 = t5 -> true
    | Some t0::Some t1::Some t2::Some t3::Some t4::Some t5::None::_ when
        player = t1 && t1 = t2 && t2 = t3 && t3 = t4 && t4 = t5 && t1 <> t0 -> true
    | None::Some t1::Some t2::Some t3::Some t4::Some t5::Some t6::_ when
        player = t1 && t1 = t2 && t2 = t3 && t3 = t4 && t4 = t5 && t1 <> t6 -> true
    | Some t0::Some t1::Some t2::Some t3::Some t4::Some t5::Some t6::_ when
        player = t1 && t1 = t2 && t2 = t3 && t3 = t4 && t4 = t5 && t1 <> t0 && t1 <> t6 -> true
    | _::ps -> check ps
    | [] -> false in
  let get_all r c g =
    [get_row r g; get_column c g; get_sum_diag (r + c) g; get_diff_diag (r - c) g] in
  if List.exists check @@ get_all row col gameboard
  then Some player
  else None;;

let start_game size =
  begin
    Random.self_init ();
    Comp_player.clear ();
    Game_gui.display size;
    Board.create @@ size + 2
  end;;

let end_game (winner, mvh, mvc) =
  begin
    Stat.update_data winner mvh mvc;
    Game_gui.return winner
  end;;

let play_game size gameboard =
  let rec turn (mvh, mvc) last player gmbd =
    let mpos =
      match player with
      | Board.Human -> Human_player.move size gmbd
      | Board.Comp -> Comp_player.move last size gmbd
      | Board.Blocked -> raise @@ Board.Incorrect_player "Game.play_game" in
    let gmbd' = Board.set_move mpos player gmbd in
    let _ = Game_gui.draw_stone size player mpos in
    let mvnum =
      match player with
      | Board.Human -> (mvh + 1, mvc)
      | Board.Comp -> (mvh, mvc + 1)
      | Board.Blocked -> raise @@ Board.Incorrect_player "Game.play_game" in
    match win gmbd' size player mpos with
    | None -> turn mvnum mpos (Board.opponent player) gmbd'
    | Some player -> (player, fst mvnum, snd mvnum) in
  turn (0, 0) (0, 0) Board.Human gameboard;;

let run size =
  let gameboard = start_game size in
  let game_result = play_game size gameboard in
  end_game game_result;;
