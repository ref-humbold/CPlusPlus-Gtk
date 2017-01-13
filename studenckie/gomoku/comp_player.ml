type direction_t =
    | Row of int
    | Column of int
    | Sum of int
    | Diff of int;;

type combination_t =
    | Begin_free of int * direction_t * int
    | End_free of int * direction_t * int;;

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
        | comb::cs ->
            begin
                match comb with
                | Begin_free (t, dir, n) | End_free (t, dir, n) ->
                    add_pos cs retacc @@ (t, pos_in_dir dir n)::acc
            end in
    match lst with
    | [] -> []
    | combs::css -> add_pos combs (positions css) [];;

let count_items lst =
    let cmp (n1, (t1, p1)) (n2, (t2, p2)) =
        let nc = compare n1 n2 and tc = compare t1 t2
        and pc = compare p1 p2 in
        if nc = 0 && tc = 0
        then pc
        else if nc = 0
        then -tc
        else -nc in
    let rec cnt num lst_ =
        match lst_ with
        | x1::(x2::_ as xt) ->
            if x1 = x2
            then cnt (num+1) xt
            else (num, x1)::(cnt 1 xt)
        | [x] -> [(num, x)]
        | [] -> [] in
    List.sort cmp @@ cnt 1 @@ List.sort compare lst;;

let check_four size player (row, col) gameboard =
    let rec check acc (lst, dir, numrow) =
        match lst with
        | p0::p1::p2::p3::p4::p5::ps ->
            begin
                match (p0, p1, p2, p3, p4, p5) with
                | (None, Some t1, Some t2, Some t3, Some t4, None) when
                    player = t1 && t1 = t2 && t2 = t3 && t3 = t4 ->
                        check ((Begin_free (4, dir, numrow))::(Begin_free (4, dir, numrow+5))::acc) (p5::ps, dir, numrow+5)
                | (Some t0, Some t1, Some t2, Some t3, Some t4, None) when
                    player = t1 && t1 = t2 && t2 = t3 && t3 = t4 && t1 <> t0 ->
                        check (End_free (4, dir, numrow+5)::acc) (p5::ps, dir, numrow+5)
                | (None, Some t1, Some t2, Some t3, Some t4, Some t5) when
                    player = t1 && t1 = t2 && t2 = t3 && t3 = t4 && t1 <> t5 ->
                        check (Begin_free (4, dir, numrow)::acc) (p5::ps, dir, numrow+5)
                | _ -> check acc (p1::p2::p3::p4::p5::ps, dir, numrow+1)
            end
        | _ -> acc in
    let get_all r c g = [get_row r g; get_col c g; get_sum size (r+c) g; get_diff size (r-c) g] in
    positions @@ List.map (check []) @@ get_all row col gameboard;;

let check_three size player (row, col) gameboard =
    let rec check acc (lst, dir, numrow) =
        match lst with
        | p0::p1::p2::p3::p4::ps ->
            begin
                match (p0, p1, p2, p3, p4) with
                | (None, Some t1, Some t2, Some t3, None) when
                    player = t1 && t1 = t2 && t2 = t3 ->
                        check ((Begin_free (3, dir, numrow))::(End_free (3, dir, numrow+4))::acc) (p4::ps, dir, numrow+4)
                | (Some t0, Some t1, Some t2, Some t3, None) when
                    player = t1 && t1 = t2 && t2 = t3 && t1 <> t0 ->
                        check (End_free (3, dir, numrow+4)::acc) (p4::ps, dir, numrow+4)
                | (None, Some t1, Some t2, Some t3, Some t4) when
                    player = t1 && t1 = t2 && t2 = t3 && t1 <> t4 ->
                        check (Begin_free (3, dir, numrow)::acc) (p4::ps, dir, numrow+4)
                | _ -> check acc (p1::p2::p3::p4::ps, dir, numrow+1)
            end
        | _ -> acc in
    let get_all r c g = [get_row r g; get_col c g; get_sum size (r+c) g; get_diff size (r-c) g] in
    positions @@ List.map (check []) @@ get_all row col gameboard;;

let analyze_human size move gameboard =
    let fours = check_four size Board.Human move gameboard
    and threes = check_three size Board.Human move gameboard in
    let possibles = count_items @@ fours@threes in
    match possibles with
    | [] -> None
    | (_, (_, pt))::_ -> Some pt;;

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
    let (sgn, pos) = choose_pos () in
    begin
        last_move := pos;
        pos
    end;;
