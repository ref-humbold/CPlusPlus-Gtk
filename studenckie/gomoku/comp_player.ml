type direction_t =
    | Row of int
    | Column of int
    | Sum of int
    | Diff of int;;

type move_t =
    | Four_comp of int * int
    | More_human of int * int
    | Four_human of int * int
    | More_comp of int * int
    | Three_comp of int * int
    | Three_human of int * int
    | Any

let comp_move m1 m2 =
    match (m1, m2) with
    | (Any, Any) -> 0
    | (Any, _) -> 1
    | (_, Any) -> -1
    | (_, _) -> compare m1 m2;;

let last_move = ref (0, 0);;

let get_row r gmbd = (List.nth gmbd r, Row r, 0)
and get_col c gmbd = (List.map (fun lst -> List.nth lst c) gmbd, Column c, 0)
and get_sum sz s gmbd =
    let begrow = if s <= sz+1 then 0 else s-sz-1 in
    let rec gs i g acc =
        match g with
        | [] -> List.rev acc
        | rw::rws ->
            if s-i < 0 || s-i > sz+1
            then gs (i+1) rws acc
            else gs (i+1) rws ((List.nth rw @@ s-i)::acc) in
    (gs 0 gmbd [], Sum s, begrow)
and get_diff sz d gmbd =
    let begrow = if d <= 0 then 0 else d in
    let rec gd i g acc =
        match g with
        | [] -> List.rev acc
        | rw::rws ->
            if i-d < 0 || i-d > sz+1
            then gd (i+1) rws acc
            else gd (i+1) rws ((List.nth rw @@ i-d)::acc) in
    (gd 0 gmbd [], Diff d, begrow);;

let random_elem lst = List.nth lst @@ Random.int @@ List.length lst;;

let cmp_pos (n1, p1) (n2, p2) =
    let nc = compare n1 n2 in
    if nc = 0
    then compare p1 p2
    else -nc;;

let count lst =
    let rec cnt num lst_ =
        match lst_ with
        | (x1, _, _)::((x2, _, _)::_ as xt) ->
            if x1 = x2
            then cnt (num+1) xt
            else (num, x1)::(cnt 1 xt)
        | [(x, _, _)] -> [(num, x)]
        | [] -> [] in
    List.sort cmp_pos @@ cnt 1 @@ List.sort compare lst;;

let check_situation size player (row, col) gameboard =
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
                check ((pos_by dir numrow, 4, dir)::acc) (ps, dir, numrow+5)
        | Some t0::None::Some t2::Some t3::Some t4::ps when
            player = t0 && t0 = t2 && t2 = t3 && t3 = t4 ->
                check ((pos_by dir (numrow+1), 4, dir)::acc) (ps, dir, numrow+5)
        | Some t0::Some t1::None::Some t3::Some t4::ps when
            player = t0 && t0 = t1 && t1 = t3 && t3 = t4 ->
                check ((pos_by dir (numrow+2), 4, dir)::acc) (ps, dir, numrow+5)
        | Some t0::Some t1::Some t2::None::Some t4::ps when
            player = t0 && t0 = t1 && t1 = t2 && t2 = t4 ->
                check ((pos_by dir (numrow+3), 4, dir)::acc) (ps, dir, numrow+5)
        | Some t0::Some t1::Some t2::Some t3::None::ps when
            player = t0 && t0 = t1 && t1 = t2 && t2 = t3 ->
                check ((pos_by dir (numrow+4), 4, dir)::acc) (ps, dir, numrow+5)
        | None::Some t1::Some t2::Some t3::ps when
            player = t1 && t1 = t2 && t2 = t3 ->
                check ((pos_by dir numrow, 3, dir)::acc) (ps, dir, numrow+4)
        | Some t0::None::Some t2::Some t3::ps when
            player = t0 && t0 = t2 && t2 = t3 ->
                check ((pos_by dir (numrow+1), 3, dir)::acc) (ps, dir, numrow+4)
        | Some t0::Some t1::None::Some t3::ps when
            player = t0 && t0 = t1 && t1 = t3 ->
                check ((pos_by dir (numrow+2), 3, dir)::acc) (ps, dir, numrow+4)
        | Some t0::Some t1::Some t2::None::ps when
            player = t0 && t0 = t1 && t1 = t2 ->
                check ((pos_by dir (numrow+3), 3, dir)::acc) (ps, dir, numrow+4)
        | _::ps -> check acc (ps, dir, numrow+1)
        | [] -> acc in
    let get_all r c g = [get_row r g; get_col c g; get_sum size (r+c) g; get_diff size (r-c) g] in
    List.concat @@ List.map (check []) @@ get_all row col gameboard;;

let numbered player situation =
    match count situation with
    | (n, (p1, p2))::_ when n > 1 ->
        begin
            match player with
            | Board.Human -> More_human (p1, p2)
            | Board.Comp -> More_comp (p1, p2)
            | Board.Blocked -> raise @@ Board.Incorrect_player "Comp_player.numbered"
        end
    | _ -> Any;;

let fours player situation =
    let fours_list = List.filter (fun (_, t, _) -> t = 4) situation in
    match fours_list with
    | _::_ ->
        let ((p1, p2), _, _) = random_elem fours_list in
        begin
            match player with
            | Board.Human -> Four_human (p1, p2)
            | Board.Comp -> Four_comp (p1, p2)
            | Board.Blocked -> raise @@ Board.Incorrect_player "Comp_player.fours"
        end
    | [] -> Any;;

let threes player situation =
    let threes_list = List.filter (fun (_, t, _) -> t = 3) situation in
    match threes_list with
    | _::_ ->
        let ((p1, p2), _, _) = random_elem threes_list in
        begin
            match player with
            | Board.Human -> Three_human (p1, p2)
            | Board.Comp -> Three_comp (p1, p2)
            | Board.Blocked -> raise @@ Board.Incorrect_player "Comp_player.threes"
        end
    | [] -> Any;;

let analyze size human_move gameboard =
    let anl player mv =
        let sit = check_situation size player mv gameboard in
        [numbered player sit; fours player sit; threes player sit] in
    List.hd @@ List.sort comp_move @@ (anl Board.Human human_move)@(anl Board.Comp (!last_move));;

let random_choose size = (1+Random.int (size-1), 1+Random.int (size-1));;

let move human_move size gameboard =
    let analyzed = analyze size human_move gameboard in
    let rec random_pos () =
        let pos = random_choose size in
        if Board.is_free pos gameboard
        then pos
        else random_pos () in
    let choose_pos () =
        match analyzed with
        | Any -> random_pos ()
        | Four_comp (p1, p2) | More_human (p1, p2) | Four_human (p1, p2) | More_comp (p1, p2) | Three_comp (p1, p2) | Three_human (p1, p2) -> (p1, p2) in
    let pos = choose_pos () in
    begin
        last_move := pos;
        pos
    end;;
