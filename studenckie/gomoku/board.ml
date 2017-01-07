exception Incorrect_gameboard;;

type player_t = Human | Comp;;
type gameboard_t = player_t option list list

let string_of_player ply =
    match ply with
    | Human -> "Human"
    | Comp -> "Computer";;

let create size =
    let rec crt i v acc =
        if i = 0
        then acc
        else crt (i-1) v (v::acc) in
    let rw = crt size None [] in
    crt (size+2) rw [];;

let is_free (r, c) gm =
    match List.nth (List.nth gm r) c with
    | None -> true
    | Some _ -> false;;

let get_player (r, c) gm = List.nth (List.nth gm r) c;;
