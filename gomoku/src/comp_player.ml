type direction_t =
  | Row of int
  | Column of int
  | Sum of int
  | Diff of int;;

type move_t =
  | Comp_make_five of int * int
  | Human_make_more of int * int
  | Human_make_five of int * int
  | Comp_make_more of int * int
  | Comp_make_four of int * int
  | Human_make_four of int * int
  | Any;;

let compare_moves m1 m2 =
  match (m1, m2) with
  | (Any, Any) -> 0
  | (Any, _) -> 1
  | (_, Any) -> -1
  | (_, _) -> compare m1 m2;;

let extract_sum_diag sum size gameboard =
  let rec extract_sum i g acc =
    match g with
    | [] -> List.rev acc
    | rw::rws ->
      if sum - i < 0 || sum - i > size + 1
      then extract_sum (i + 1) rws acc
      else extract_sum (i + 1) rws @@ (List.nth rw (sum - i))::acc in
  extract_sum 0 gameboard []
and extract_diff_diag diff size gameboard =
  let rec extract_diff i g acc =
    match g with
    | [] -> List.rev acc
    | rw::rws ->
      if i - diff < 0 || i - diff > size + 1
      then extract_diff (i + 1) rws acc
      else extract_diff (i + 1) rws @@ (List.nth rw (i - diff))::acc in
  extract_diff 0 gameboard []

let move_queue = ref [Any];;
let last_move = ref (0, 0);;

let get_row row gameboard =
  (List.nth gameboard row, Row row, 0)
and get_column col gameboard =
  (List.map (fun lst -> List.nth lst col) gameboard, Column col, 0)
and get_sum_diag size sum gameboard =
  let beg_row = if sum <= size + 1 then 0 else sum - size - 1 in
  (extract_sum_diag sum size gameboard, Sum sum, beg_row)
and get_diff_diag size diff gameboard =
  let beg_row = if diff <= 0 then 0 else diff in
  (extract_diff_diag diff size gameboard, Diff diff, beg_row);;

let random_element lst = List.nth lst @@ Random.int @@ List.length lst;;

let compare_positions (n1, p1) (n2, p2) =
  let nc = compare n1 n2 in
  if nc = 0
  then compare p1 p2
  else -nc;;

let count_points lst =
  let rec cnt num lst' =
    match lst' with
    | (x1, _)::((x2, _)::_ as xt) ->
      if x1 = x2
      then cnt (num + 1) xt
      else (num, x1)::(cnt 1 xt)
    | [(x, _)] -> [(num, x)]
    | [] -> [] in
  List.sort compare_positions @@ cnt 1 @@ List.sort compare lst;;

let count_nums lst =
  let rec cnt num lst' =
    match lst' with
    | x1::(x2::_ as xt) ->
      if x1 = x2
      then cnt (num + 1) xt
      else (x1, num)::(cnt 1 xt)
    | [x] -> [(x, num)]
    | [] -> [] in
  List.sort compare @@ cnt 1 @@ List.sort compare lst;;

let get_empties size gameboard =
  let neighbours row col =
    let prv = List.nth gameboard (row - 1)
    and nxt = List.nth gameboard (row + 1)
    and same = List.nth gameboard row in
    [List.nth prv (col - 1);
     List.nth prv col;
     List.nth prv (col + 1);
     List.nth same (col - 1);
     List.nth same (col + 1);
     List.nth nxt (col - 1);
     List.nth nxt col;
     List.nth nxt (col + 1)] in
  let check field =
    match field with
    | Some (Some _) -> true
    | Some None | None -> false in
  let empty i row_i field =
    if i >= 1 && i <= size
    then
      match field with
      | None ->
        if List.exists check @@ neighbours row_i i
        then i
        else -1
      | Some _ -> -1
    else -1 in
  let map_row f row_i row =
    let rec mapi_row i row' =
      match row' with
      | [] -> []
      | x::xs ->
        let res = f i row_i x in
        if res > 0
        then (row_i, res)::(mapi_row (i + 1) xs)
        else mapi_row (i + 1) xs in
    mapi_row 0 row in
  let row_empty row_i row =
    if row_i >= 1 && row_i <= size
    then map_row empty row_i row
    else [] in
  List.concat @@ List.mapi row_empty gameboard;;

let check_win_situation size player (row, col) gameboard =
  let pos_by dir num =
    match dir with
    | Row r -> (r, num)
    | Column c -> (num, c)
    | Sum s -> (num, s - num)
    | Diff d -> (num, num - d) in
  let rec check acc (lst, dir, numrow) =
    match lst with
    | None::Some t1::Some t2::Some t3::Some t4::ps when
        Some player = t1 && t1 = t2 && t2 = t3 && t3 = t4 ->
      check ((pos_by dir numrow, 5)::acc) (ps, dir, numrow + 5)
    | Some t0::None::Some t2::Some t3::Some t4::ps when
        Some player = t0 && t0 = t2 && t2 = t3 && t3 = t4 ->
      check ((pos_by dir (numrow + 1), 5)::acc) (ps, dir, numrow + 5)
    | Some t0::Some t1::None::Some t3::Some t4::ps when
        Some player = t0 && t0 = t1 && t1 = t3 && t3 = t4 ->
      check ((pos_by dir (numrow + 2), 5)::acc) (ps, dir, numrow + 5)
    | Some t0::Some t1::Some t2::None::Some t4::ps when
        Some player = t0 && t0 = t1 && t1 = t2 && t2 = t4 ->
      check ((pos_by dir (numrow + 3), 5)::acc) (ps, dir, numrow + 5)
    | Some t0::Some t1::Some t2::Some t3::None::ps when
        Some player = t0 && t0 = t1 && t1 = t2 && t2 = t3 ->
      check ((pos_by dir (numrow + 4), 5)::acc) (ps, dir, numrow + 5)
    | None::Some t1::Some t2::Some t3::ps when
        Some player = t1 && t1 = t2 && t2 = t3 ->
      check ((pos_by dir numrow, 4)::acc) (ps, dir, numrow + 4)
    | Some t0::None::Some t2::Some t3::ps when
        Some player = t0 && t0 = t2 && t2 = t3 ->
      check ((pos_by dir (numrow + 1), 4)::acc) (ps, dir, numrow + 4)
    | Some t0::Some t1::None::Some t3::ps when
        Some player = t0 && t0 = t1 && t1 = t3 ->
      check ((pos_by dir ( + 2), 4)::acc) (ps, dir, numrow + 4)
    | Some t0::Some t1::Some t2::None::ps when
        Some player = t0 && t0 = t1 && t1 = t2 ->
      check ((pos_by dir (numrow + 3), 4)::acc) (ps, dir, numrow + 4)
    | _::ps -> check acc (ps, dir, numrow + 1)
    | [] -> acc in
  let get_all r c g = [get_row r g;
                       get_column c g;
                       get_sum_diag size (r + c) g;
                       get_diff_diag size (r - c) g] in
  List.concat @@ List.map (check []) @@ get_all row col gameboard;;

let check_board_situation size player gameboard =
  let rec check acc lst =
    match lst with
    | Some t0::Some t1::Some t2::Some t3::Some t4::ps when
        Some player = t0 && t0 = t1 && t1 = t2 && t2 = t3 && t3 = t4 -> check (5::acc) ps
    | Some t0::Some t1::Some t2::Some t3::ps when
        Some player = t0 && t0 = t1 && t1 = t2 && t2 = t3 -> check (4::acc) ps
    | Some t0::Some t1::Some t2::ps when
        Some player = t0 && t0 = t1 && t1 = t2 -> check (3::acc) ps
    | Some t0::Some t1::ps when
        Some player = t0 && t0 = t1 -> check (2::acc) ps
    | _::ps -> check acc ps
    | [] -> acc in
  let get_rows g = g
  and get_columns g = List.mapi (fun i _ -> List.nth g i) g
  and get_sum_diags g =
    let rec get_s s acc =
      if s <= size + size
      then get_s (s + 1) @@ (extract_sum_diag s size g)::acc
      else acc in
    get_s 2 []
  and get_diff_diags g =
    let rec get_d d acc =
      if d <= size - 1
      then get_d (d + 1) @@ (extract_diff_diag d size g)::acc
      else acc in
    get_d (-size + 1) [] in
  let get_all g = List.concat [get_rows g;
                               get_columns g;
                               get_sum_diags g;
                               get_diff_diags g] in
  count_nums @@ List.concat @@ List.map (check []) @@ get_all gameboard;;

let numbered player situation =
  match count_points situation with
  | (n, (p1, p2))::_ when n > 1 ->
    ( match player with
      | Board.Human -> Human_make_more (p1, p2)
      | Board.Comp -> Comp_make_more (p1, p2)
    )
  | _ -> Any;;

let make_five player situation =
  let make_five_list = List.filter (fun (_, t) -> t = 5) situation in
  match make_five_list with
  | _::_ ->
    let ((p1, p2), _) = random_element make_five_list in
    ( match player with
      | Board.Human -> Human_make_five (p1, p2)
      | Board.Comp -> Comp_make_five (p1, p2)
    )
  | [] -> Any;;

let make_four player situation =
  let make_four_list = List.filter (fun (_, t) -> t = 4) situation in
  match make_four_list with
  | _::_ ->
    let ((p1, p2), _) = random_element make_four_list in
    ( match player with
      | Board.Human -> Human_make_four (p1, p2)
      | Board.Comp -> Comp_make_four (p1, p2)
    )
  | [] -> Any;;

let heura size gameboard =
  let comp_sit = check_board_situation size Board.Comp gameboard
  and human_sit = check_board_situation size Board.Human gameboard in
  let rec diffs n =
    if n = 0
    then []
    else
      let for_player sit =
        try List.find (fun e -> fst e = n) sit with
        | Not_found -> (n, 0) in
      let sit_diff = (snd @@ for_player human_sit) - (snd @@ for_player comp_sit) in
      sit_diff::(diffs @@ n - 1) in
  List.fold_right (fun e a -> (float_of_int e) +. 1.5 *. a) (diffs 5) 0.0;;

let heuristic_move size gameboard =
  let cmp f (pm, xm) (pa, xa) =
    if f xm xa
    then (pm, xm)
    else if xm = xa
    then
      if Random.bool ()
      then (pm, xm)
      else (pa, xa)
    else (pa, xa) in
  let rec forward_move level a b player gameboard' =
    if level = 0
    then ((0, 0), heura size gameboard')
    else
      let empty_pos = get_empties size gameboard' in
      let rec find_res a' b' lst acc =
        match lst with
        | [] -> acc
        | p::ps ->
          let next_gameboard = Board.set_move p player gameboard' in
          let next = forward_move (level - 1) a' b' (Board.opponent player) next_gameboard in
          let nacc = (p, snd next) in
          match player with
          | Board.Comp ->
            let new_acc = cmp (>) nacc acc in
            let new_a = max (snd new_acc) a' in
            if new_a >= b'
            then new_acc
            else find_res new_a b' ps new_acc
          | Board.Human ->
            let new_acc = cmp (<) nacc acc in
            let new_b = min (snd new_acc) b' in
            if a' >= new_b
            then new_acc
            else find_res a' new_b ps new_acc in
      match player with
      | Board.Comp -> find_res a b empty_pos ((0, 0), neg_infinity)
      | Board.Human -> find_res a b empty_pos ((0, 0), infinity) in
  fst @@ forward_move 4 neg_infinity infinity Board.Comp gameboard;;

let analyze size human_move gameboard =
  let analyze' player mv =
    let sit = check_win_situation size player mv gameboard in
    [numbered player sit; make_five player sit; make_four player sit] in
  List.sort compare_moves @@ (analyze' Board.Human human_move)@(analyze' Board.Comp (!last_move));;

let clear () =
  begin
    move_queue := [Any];
    last_move := (0, 0)
  end;;

let move human_move size gameboard =
  let analyzed = analyze size human_move gameboard in
  let choose_pos () =
    match List.hd analyzed with
    | Any ->
      ( match List.hd (!move_queue) with
        | Any -> heuristic_move size gameboard
        | Comp_make_five (p1, p2)
        | Human_make_more (p1, p2)
        | Human_make_five (p1, p2)
        | Comp_make_more (p1, p2)
        | Comp_make_four (p1, p2)
        | Human_make_four (p1, p2) ->
          begin
            move_queue := List.tl (!move_queue);
            (p1, p2)
          end
      )
    | Comp_make_five (p1, p2)
    | Human_make_more (p1, p2)
    | Human_make_five (p1, p2)
    | Comp_make_more (p1, p2)
    | Comp_make_four (p1, p2)
    | Human_make_four (p1, p2) ->
      let non_any = List.filter (fun m -> m <> Any) analyzed in
      begin
        move_queue := List.rev_append non_any (!move_queue);
        (p1, p2)
      end in
  let rec make_move () =
    let pos = choose_pos () in
    if Board.is_free pos gameboard
    then pos
    else make_move () in
  let move_pos = make_move () in
  begin
    last_move := move_pos;
    move_pos
  end;;
