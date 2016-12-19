module type PLAYER =
sig
    type t;;

    val make_move : int * int -> (int * int * t) list -> (int * int * t) list;;
end;;
