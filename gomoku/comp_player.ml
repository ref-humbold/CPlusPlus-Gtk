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
    | Any

let comp_move m1 m2 =
    match (m1, m2) with
    | (Any, Any) -> 0
    | (Any, _) -> 1
    | (_, Any) -> -1
    | (_, _) -> compare m1 m2;;

let move_queue = ref [Any];;
let last_move = ref (0, 0);;

let gs s sz gmbd =
    let rec gs_ i g acc =
    match g with
    | [] -> List.rev acc
    | rw::rws ->
        if s-i < 0 || s-i > sz+1
        then gs_ (i+1) rws acc
        else gs_ (i+1) rws ((List.nth rw @@ s-i)::acc) in
    gs_ 0 gmbd []
and gd d sz gmbd =
    let rec gd_ i g acc =
    match g with
    | [] -> List.rev acc
    | rw::rws ->
        if i-d < 0 || i-d > sz+1
        then gd_ (i+1) rws acc
        else gd_ (i+1) rws ((List.nth rw @@ i-d)::acc) in
    gd_ 0 gmbd [];;

let get_row r gmbd = (List.nth gmbd r, Row r, 0)
and get_col c gmbd = (List.map (fun lst -> List.nth lst c) gmbd, Column c, 0)
and get_sum sz s gmbd =
    let begrow = if s <= sz+1 then 0 else s-sz-1 in
    (gs s sz gmbd, Sum s, begrow)
and get_diff sz d gmbd =
    let begrow = if d <= 0 then 0 else d in
    (gd d sz gmbd, Diff d, begrow);;

let random_elem lst = List.nth lst @@ Random.int @@ List.length lst;;

let cmp_pos (n1, p1) (n2, p2) =
    let nc = compare n1 n2 in
    if nc = 0
    then compare p1 p2
    else -nc;;

let count_pts lst =
    let rec cnt num lst_ =
        match lst_ with
        | (x1, _)::((x2, _)::_ as xt) ->
            if x1 = x2
            then cnt (num+1) xt
            else (num, x1)::(cnt 1 xt)
        | [(x, _)] -> [(num, x)]
        | [] -> [] in
    List.sort cmp_pos @@ cnt 1 @@ List.sort compare lst;;

let count_nums lst =
    let rec cnt num lst_ =
        match lst_ with
        | x1::(x2::_ as xt) ->
            if x1 = x2
            then cnt (num+1) xt
            else (x1, num)::(cnt 1 xt)
        | [x] -> [(x, num)]
        | [] -> [] in
    List.sort compare @@ cnt 1 @@ List.sort compare lst;;

let get_empties size gameboard =
    let neibs r c =
        let prv = List.nth gameboard (r-1) and same = List.nth gameboard r
        and nxt = List.nth gameboard (r+1) in
        [List.nth prv (c-1); List.nth prv c; List.nth prv (c+1); List.nth same (c-1); List.nth same (c+1); List.nth nxt (c-1); List.nth nxt c; List.nth nxt (c+1)] in
    let check x =
        match x with
        | Some Board.Human | Some Board.Comp -> true
        | Some Board.Blocked | None -> false in
    let is_empt ix rownum elem =
        if ix >= 1 && ix <= size
        then
            match elem with
            | None -> if List.exists check @@ neibs rownum ix then ix else -1
            | Some _ -> -1
        else -1 in
    let map_row f rownum lst =
        let rec map_row_i ix lst_ =
            match lst_ with
            | [] -> []
            | x::xs ->
                let res = (f ix rownum x) in
                if res > 0 then (rownum, res)::(map_row_i (ix+1) xs) else map_row_i (ix+1) xs in
        map_row_i 0 lst in
    let row_empt ix row =
        if ix >= 1 && ix <= size
        then map_row is_empt ix row
        else [] in
    List.concat @@ List.mapi row_empt gameboard;;

let check_win_situation size player (row, col) gameboard =
    let pos_by dir num =
        match dir with
        | Row r -> (r, num)
        | Column c -> (num, c)
        | Sum s -> (num, s-num)
        | Diff d -> (num, num-d) in
    let rec check acc (lst, dir, numrow) =
        match lst with
        | None::Some t1::Some t2::Some t3::Some t4::ps when
            player = t1 && t1 = t2 && t2 = t3 && t3 = t4 ->
                check ((pos_by dir numrow, 5)::acc) (ps, dir, numrow+5)
        | Some t0::None::Some t2::Some t3::Some t4::ps when
            player = t0 && t0 = t2 && t2 = t3 && t3 = t4 ->
                check ((pos_by dir (numrow+1), 5)::acc) (ps, dir, numrow+5)
        | Some t0::Some t1::None::Some t3::Some t4::ps when
            player = t0 && t0 = t1 && t1 = t3 && t3 = t4 ->
                check ((pos_by dir (numrow+2), 5)::acc) (ps, dir, numrow+5)
        | Some t0::Some t1::Some t2::None::Some t4::ps when
            player = t0 && t0 = t1 && t1 = t2 && t2 = t4 ->
                check ((pos_by dir (numrow+3), 5)::acc) (ps, dir, numrow+5)
        | Some t0::Some t1::Some t2::Some t3::None::ps when
            player = t0 && t0 = t1 && t1 = t2 && t2 = t3 ->
                check ((pos_by dir (numrow+4), 5)::acc) (ps, dir, numrow+5)
        | None::Some t1::Some t2::Some t3::ps when
            player = t1 && t1 = t2 && t2 = t3 ->
                check ((pos_by dir numrow, 4)::acc) (ps, dir, numrow+4)
        | Some t0::None::Some t2::Some t3::ps when
            player = t0 && t0 = t2 && t2 = t3 ->
                check ((pos_by dir (numrow+1), 4)::acc) (ps, dir, numrow+4)
        | Some t0::Some t1::None::Some t3::ps when
            player = t0 && t0 = t1 && t1 = t3 ->
                check ((pos_by dir (numrow+2), 4)::acc) (ps, dir, numrow+4)
        | Some t0::Some t1::Some t2::None::ps when
            player = t0 && t0 = t1 && t1 = t2 ->
                check ((pos_by dir (numrow+3), 4)::acc) (ps, dir, numrow+4)
        | _::ps -> check acc (ps, dir, numrow+1)
        | [] -> acc in
    let get_all r c g = [get_row r g; get_col c g; get_sum size (r+c) g; get_diff size (r-c) g] in
    List.concat @@ List.map (check []) @@ get_all row col gameboard;;

let check_board_situation size player gameboard =
    let rec check acc lst =
        match lst with
        | Some t0::Some t1::Some t2::Some t3::Some t4::ps when
            player = t0 && t0 = t1 && t1 = t2 && t2 = t3 && t3 = t4 -> check (5::acc) ps
        | Some t0::Some t1::Some t2::Some t3::ps when
            player = t0 && t0 = t1 && t1 = t2 && t2 = t3 -> check (4::acc) ps
        | Some t0::Some t1::Some t2::ps when player = t0 && t0 = t1 && t1 = t2 -> check (3::acc) ps
        | Some t0::Some t1::ps when player = t0 && t0 = t1 -> check (2::acc) ps
        | _::ps -> check acc ps
        | [] -> acc in
    let get_rows g = g
    and get_cols g = List.mapi (fun i _ -> List.nth g i) g
    and get_sums g =
        let rec get_s s acc =
            if s <= size+size
            then get_s (s+1) @@ (gs s size g)::acc
            else acc in
        get_s 2 []
    and get_diffs g =
        let rec get_d d acc =
            if d <= size-1
            then get_d (d+1) @@ (gd d size g)::acc
            else acc in
        get_d (-size+1) [] in
    let get_all g = List.concat [get_rows g; get_cols g; get_sums g; get_diffs g] in
    count_nums @@ List.concat @@ List.map (check []) @@ get_all gameboard;;

let numbered player situation =
    match count_pts situation with
    | (n, (p1, p2))::_ when n > 1 ->
        begin
            match player with
            | Board.Human -> Human_make_more (p1, p2)
            | Board.Comp -> Comp_make_more (p1, p2)
            | Board.Blocked -> raise @@ Board.Incorrect_player "Comp_player.numbered"
        end
    | _ -> Any;;

let make_five player situation =
    let make_five_list = List.filter (fun (_, t) -> t = 5) situation in
    match make_five_list with
    | _::_ ->
        let ((p1, p2), _) = random_elem make_five_list in
        begin
            match player with
            | Board.Human -> Human_make_five (p1, p2)
            | Board.Comp -> Comp_make_five (p1, p2)
            | Board.Blocked -> raise @@ Board.Incorrect_player "Comp_player.make_five"
        end
    | [] -> Any;;

let make_four player situation =
    let make_four_list = List.filter (fun (_, t) -> t = 4) situation in
    match make_four_list with
    | _::_ ->
        let ((p1, p2), _) = random_elem make_four_list in
        begin
            match player with
            | Board.Human -> Human_make_four (p1, p2)
            | Board.Comp -> Comp_make_four (p1, p2)
            | Board.Blocked -> raise @@ Board.Incorrect_player "Comp_player.make_four"
        end
    | [] -> Any;;

let heura size gameboard =
    let comp_sit = check_board_situation size Board.Comp gameboard
    and human_sit = check_board_situation size Board.Human gameboard in
    let rec diffs n =
        if n = 0
        then []
        else
            let for_comp =
                try List.find (fun e -> fst e = n) comp_sit with
                | Not_found -> (n, 0) in
            let for_human =
                try List.find (fun e -> fst e = n) human_sit with
                | Not_found -> (n, 0) in
            ((snd for_human)-(snd for_comp))::(diffs (n-1)) in
    List.fold_right (fun e a -> (float_of_int e)+.1.5*.a) (diffs 5) 0.0;;

let heuristic_move size gameboard =
    let cmp f (pm, xm) (pa, xa) =
        if f xm xa
        then (pm, xm)
        else if xm = xa
        then if Random.bool ()
            then (pm, xm)
            else (pa, xa)
        else (pa, xa) in
    let rec fwd_move level a b player gmbd =
        if level = 0
        then ((0, 0), heura size gmbd)
        else
            let empty_pos = get_empties size gmbd in
            let rec find_res a_ b_ lst acc =
                match lst with
                | [] -> acc
                | p::ps ->
                    let next_bd = Board.set_move p player gmbd in
                    let chd = (p, snd (fwd_move (level-1) a_ b_ (Board.opponent player) next_bd)) in
                    match player with
                    | Board.Blocked -> raise @@ Board.Incorrect_player "Comp_player.heuristic_move"
                    | Board.Comp ->
                        let nacc = (cmp (>) chd acc) in
                        let na_ = max (snd nacc) a_ in
                        if na_ >= b_
                        then nacc
                        else find_res na_ b_ ps nacc
                    | Board.Human ->
                        let nacc = (cmp (<) chd acc) in
                        let nb_ = min (snd nacc) b_ in
                        if a_ >= nb_
                        then nacc
                        else find_res a_ nb_ ps nacc in
            match player with
            | Board.Blocked -> raise @@ Board.Incorrect_player "Comp_player.heuristic_move"
            | Board.Comp -> find_res a b empty_pos ((0, 0), neg_infinity)
            | Board.Human -> find_res a b empty_pos ((0, 0), infinity) in
    fst @@ fwd_move 4 neg_infinity infinity Board.Comp gameboard;;

let analyze size human_move gameboard =
    let anl player mv =
        let sit = check_win_situation size player mv gameboard in
        [numbered player sit; make_five player sit; make_four player sit] in
    List.sort comp_move @@ (anl Board.Human human_move)@(anl Board.Comp (!last_move));;

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
            begin
                match List.hd (!move_queue) with
                | Any -> heuristic_move size gameboard
                | Comp_make_five (p1, p2) | Human_make_more (p1, p2) | Human_make_five (p1, p2) | Comp_make_more (p1, p2) | Comp_make_four (p1, p2) | Human_make_four (p1, p2) ->
                    begin
                        move_queue := List.tl (!move_queue);
                        (p1, p2)
                    end
            end
        | Comp_make_five (p1, p2) | Human_make_more (p1, p2) | Human_make_five (p1, p2) | Comp_make_more (p1, p2) | Comp_make_four (p1, p2) | Human_make_four (p1, p2) ->
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
    let move_pos = make_move() in
    begin
        last_move := move_pos;
        move_pos
    end;;
