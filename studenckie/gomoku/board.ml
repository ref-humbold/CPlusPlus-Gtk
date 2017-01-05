exception Incorrect_gameboard;;

type player = Human | Comp;;
type pos = int * int;;
type gameboard = player option list list;;

let string_of_player ply =
    match ply with
    | Human -> "Human"
    | Comp -> "Computer";;

let empty n =
    if n >= 17 && n <= 32
    then
        let rec create i v acc =
            if i = 0
            then acc
            else create (i-1) v (v::acc) in
        let rw = create n None [] in
        create n rw []
    else raise Incorrect_gameboard;;

let free (r, c) gm =
    match List.nth (List.nth gm r) c with
    | None -> true
    | Some _ -> false;;

let ply (r, c) gm = List.nth (List.nth gm r) c;;
