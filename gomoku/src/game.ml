let win gameboard size player (row, col) =
  let get_row row' gameboard' =
    List.nth gameboard' row'
  and get_column col' gameboard' =
    List.map (fun lst -> List.nth lst col') gameboard'
  and get_sum_diag sum gameboard' =
    let rec gs i gameboard'' acc =
      match gameboard'' with
      | [] -> List.rev acc
      | row'::rows' ->
        if sum - i < 0 || sum - i > size + 1
        then gs (i + 1) rows' acc
        else gs (i + 1) rows' @@ (List.nth row' @@ sum - i)::acc in
    gs 0 gameboard' []
  and get_diff_diag diff gameboard' =
    let rec gd i gameboard'' acc =
      match gameboard'' with
      | [] -> List.rev acc
      | row'::rows' ->
        if i - diff < 0 || i - diff > size + 1
        then gd (i + 1) rows' acc
        else gd (i + 1) rows' @@ (List.nth row' @@ i - diff)::acc in
    gd 0 gameboard' [] in
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
  let get_all row' col' gameboard' =
    [get_row row' gameboard';
     get_column col' gameboard';
     get_sum_diag (row' + col') gameboard';
     get_diff_diag (row' - col') gameboard'] in
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
  let rec turn (mvh, mvc) last player gameboard' =
    let move_pos =
      match player with
      | Board.Human -> Human_player.move size gameboard'
      | Board.Comp -> Comp_player.move last size gameboard'
      | Board.Blocked -> raise @@ Board.Incorrect_player "Game.play_game" in
    let move_nums =
      match player with
      | Board.Human -> (mvh + 1, mvc)
      | Board.Comp -> (mvh, mvc + 1)
      | Board.Blocked -> raise @@ Board.Incorrect_player "Game.play_game" in
    let new_gameboard = Board.set_move move_pos player gameboard' in
    begin
      Game_gui.draw_stone size player move_pos;
      match win new_gameboard size player move_pos with
      | None -> turn move_nums move_pos (Board.opponent player) new_gameboard
      | Some player -> (player, fst move_nums, snd move_nums)
    end in
  turn (0, 0) (0, 0) Board.Human gameboard;;

let run size =
  let gameboard = start_game size in
  let game_result = play_game size gameboard in
  end_game game_result;;
