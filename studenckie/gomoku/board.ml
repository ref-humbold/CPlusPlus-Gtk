exception Incorrect_gameboard;;

type player = Human | Comp;;
type pos = int * int;;
type gameboard = player option list list;;

let string_of_player ply =
    match ply with
    | Human -> "Human"
    | Comp -> "Computer";;

let empty n =
    let rec create i v acc =
        if i = 0
        then acc
        else create (i-1) v (v::acc) in
    let rw = create n None [] in
    create n rw [];;

let free (r, c) gm =
    match List.nth (List.nth gm r) c with
    | None -> true
    | Some _ -> false;;

let ply (r, c) gm = List.nth (List.nth gm r) c;;
