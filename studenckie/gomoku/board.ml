type player_t = Human | Comp | Blocked;;
type gameboard_t = player_t option list list

exception Incorrect_gameboard;;
exception Incorrect_player;;

let string_of_player player =
    match player with
    | Human -> "Human"
    | Comp -> "Computer"
    | Blocked -> raise @@ Incorrect_player;;

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

let is_free (r, c) gm =
    match List.nth (List.nth gm r) c with
    | None -> true
    | Some _ -> false;;

let get_player (r, c) gm = List.nth (List.nth gm r) c;;
