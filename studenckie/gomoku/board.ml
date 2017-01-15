type player_t = Human | Comp | Blocked;;
type gameboard_t = player_t option list list

exception Incorrect_gameboard of string;;
exception Incorrect_player of string;;

let create size =
    let rec crt_row rn i acc =
        if i = 0
        then acc
        else if rn = 1 || rn = size || i = 1 || i = size
        then crt_row rn (i-1) @@ (Some Blocked)::acc
        else crt_row rn (i-1) (None::acc) in
    let rec crt_board rn acc =
        if rn = 0
        then acc
        else crt_board (rn-1) @@ (crt_row rn size [])::acc in
    crt_board size [];;

let set_move (row, col) player game =
    let rec set_col n r =
        match r with
        | [] -> raise @@ Incorrect_gameboard "Board.set_move @ column"
        | x::xs ->
            if n = 0
            then (Some player)::xs
            else x::(set_col (n-1) xs) in
    let rec set_row n g =
        match g with
        | [] -> raise @@ Incorrect_gameboard "Board.set_move @ row"
        | x::xs ->
            if n = 0
            then (set_col col x)::xs
            else x::(set_row (n-1) xs) in
    set_row row game;;

let opponent player =
    match player with
    | Human -> Comp
    | Comp -> Human
    | Blocked -> raise @@ Incorrect_player "Board.opponent";;

let is_free (r, c) gm =
    match List.nth (List.nth gm r) c with
    | None -> true
    | Some _ -> false;;

let get_player (r, c) gm = List.nth (List.nth gm r) c;;
