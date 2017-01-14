type direction_t =
    | Row of int
    | Column of int
    | Sum of int
    | Diff of int;;

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

let rec positions lst =
    let pos_in_dir dir num =
        match dir with
        | Row r -> (r, num)
        | Column c -> (num, c)
        | Sum s -> (num, s-num)
        | Diff d -> (num, num-d) in
    let rec add_pos lst_ retacc acc =
        match lst_ with
        | [] -> List.rev_append acc retacc
        | (dir, n)::cs -> add_pos cs retacc @@ (pos_in_dir dir n)::acc in
    match lst with
    | [] -> []
    | combs::css -> add_pos combs (positions css) [];;

let cmp_pos (n1, p1) (n2, p2) =
    let nc = compare n1 n2 in
    if nc = 0
    then compare p1 p2
    else -nc;;

let count_items lst =
    let rec cnt num lst_ =
        match lst_ with
        | x1::(x2::_ as xt) ->
            if x1 = x2
            then cnt (num+1) xt
            else (num, x1)::(cnt 1 xt)
        | [x] -> [(num, x)]
        | [] -> [] in
    List.sort cmp_pos @@ cnt 1 @@ List.sort compare lst;;

let check_situation size player (row, col) gameboard =
    let rec check acc (lst, dir, numrow) =
        match lst with
        | None::Some t1::Some t2::Some t3::None::ps when
            player = t1 && t1 = t2 && t2 = t3 ->
                check ((dir, numrow)::(dir, numrow+4)::acc) (ps, dir, numrow+4)
        | Some t0::Some t1::Some t2::Some t3::None::ps when
            player = t1 && t1 = t2 && t2 = t3 && t1 <> t0 ->
                check ((dir, numrow+4)::acc) (ps, dir, numrow+4)
        | None::Some t1::Some t2::Some t3::Some t4::ps when
            player = t1 && t1 = t2 && t2 = t3 && t1 <> t4 ->
                check ((dir, numrow)::acc) (ps, dir, numrow+4)
        | None::Some t1::Some t2::Some t3::Some t4::None::ps when
            player = t1 && t1 = t2 && t2 = t3 && t3 = t4 ->
                check ((dir, numrow)::(dir, numrow+5)::acc) (ps, dir, numrow+5)
        | Some t0::Some t1::Some t2::Some t3::Some t4::None::ps when
            player = t1 && t1 = t2 && t2 = t3 && t3 = t4 && t1 <> t0 ->
                check ((dir, numrow+5)::acc) (ps, dir, numrow+5)
        | None::Some t1::Some t2::Some t3::Some t4::Some t5::ps when
            player = t1 && t1 = t2 && t2 = t3 && t3 = t4 && t1 <> t5 ->
                check ((dir, numrow)::acc) (ps, dir, numrow+5)
        | _::ps -> check acc (ps, dir, numrow+1)
        | [] -> acc in
    let get_all r c g = [get_row r g; get_col c g; get_sum size (r+c) g; get_diff size (r-c) g] in
    positions @@ List.map (check []) @@ get_all row col gameboard;;

let analyze_human size move gameboard =
    let sit = check_situation size Board.Human move gameboard in
    let possibles = count_items sit in
    match possibles with
    | [] -> None
    | (_, pt)::_ -> Some pt;;

let choose size = (1+Random.int (size-1), 1+Random.int (size-1));;

let move human_move size gameboard =
    let defensive = analyze_human size human_move gameboard in
    (*let offensive = analyze_comp size (!last_move) gameboard*)
    let rec random_pos () =
        let pos = choose size in
        if Board.is_free pos gameboard
        then pos
        else random_pos () in
    let choose_pos () =
        match defensive with
        | None -> random_pos ()
        | Some pt -> pt in
    let pos = choose_pos () in
    begin
        last_move := pos;
        pos
    end;;
