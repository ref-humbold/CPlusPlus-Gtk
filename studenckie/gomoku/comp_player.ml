type direction_t =
    | Row of int
    | Column of int
    | Sum of int
    | Diff of int;;

type combination_t =
    | Any
    | Both_free of direction_t * int * int
    | Begin_free of direction_t * int
    | End_free of direction_t * int;;

let last_move = ref (0, 0);;

let get_row r gmbd = (List.nth gmbd r, Row r)
and get_col c gmbd = (List.map (fun lst -> List.nth lst c) gmbd, Column c)
and get_sum s gmbd =
    let rec gs s_ i g acc =
        match g with
        | [] -> acc
        | xs::xss ->
            try gs s_ (i+1) xss ((List.nth xs @@ s_-i)::acc) with
            | Failure _ | Invalid_argument _ -> gs s_ (i+1) xss acc in
    (gs s 0 gmbd [], Sum s)
and get_diff d gmbd =
    let rec gd d_ i g acc =
        match g with
        | [] -> acc
        | xs::xss ->
            try gd d_ (i+1) xss ((List.nth xs @@ i-d_)::acc) with
            | Failure _ | Invalid_argument _ -> gd d_ (i+1) xss acc in
    (gd d 0 gmbd [], Diff d);;

let check_four player (row, col) gameboard =
    let rec check begpos (lst, dir) =
        match lst with
        | p0::p1::p2::p3::p4::p5::ps ->
            begin
                match (p0, p1, p2, p3, p4, p5) with
                | (None, Some t1, Some t2, Some t3, Some t4, None) when
                    player = t1 && t1 = t2 && t2 = t3 && t3 = t4 ->
                        Both_free (dir, begpos, begpos+5)
                | (Some t0, Some t1, Some t2, Some t3, Some t4, None) when
                    player = t1 && t1 = t2 && t2 = t3 && t3 = t4 && t1 <> t0 ->
                        End_free (dir, begpos+5)
                | (None, Some t1, Some t2, Some t3, Some t4, Some t5) when
                    player = t1 && t1 = t2 && t2 = t3 && t3 = t4 && t1 <> t5 ->
                        Begin_free (dir, begpos)
                | _ -> check (begpos+1) (p1::p2::p3::p4::p5::ps, dir)
            end
        | _ -> Any in
    let get_all r c g = [get_row r g; get_col c g; get_sum (r+c) g; get_diff (r-c) g] in
    List.map (check 0) @@ get_all row col gameboard;;

let check_three player (row, col) gameboard =
    let rec check begpos (lst, dir) =
        match lst with
        | p0::p1::p2::p3::p4::ps ->
            begin
                match (p0, p1, p2, p3, p4) with
                | (None, Some t1, Some t2, Some t3, None) when
                    player = t1 && t1 = t2 && t2 = t3 -> Both_free (dir, begpos, begpos+5)
                | (Some t0, Some t1, Some t2, Some t3, None) when
                    player = t1 && t1 = t2 && t2 = t3 && t1 <> t0 -> End_free (dir, begpos+5)
                | (None, Some t1, Some t2, Some t3, Some t4) when
                    player = t1 && t1 = t2 && t2 = t3 && t1 <> t4 -> Begin_free (dir, begpos)
                | _ -> check (begpos+1) (p1::p2::p3::p4::ps, dir)
            end
        | _ -> Any in
    let get_all r c g = [get_row r g; get_col c g; get_sum (r+c) g; get_diff (r-c) g] in
    List.map (check 0) @@ get_all row col gameboard;;

let choose size = (1+Random.int (size-1), 1+Random.int (size-1));;

let rec move human_move size gameboard =
    let pos = choose size in
    if Board.is_free pos gameboard
    then
        begin
            last_move := pos;
            print_int (fst human_move);
            print_string ", ";
            print_int (snd human_move);
            print_string " -->> ";
            print_int (fst pos);
            print_string ", ";
            print_int (snd pos);
            print_string "\n";
            pos
        end
    else move human_move size gameboard;;
