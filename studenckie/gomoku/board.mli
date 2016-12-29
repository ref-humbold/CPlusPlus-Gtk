exception Incorrect_gameboard;;

type player = Human | Comp;;
type pos = int * int;;
type gameboard = player option list list;;

val string_of_player : player -> string;;
val empty : int -> gameboard;;
val free : pos -> gameboard -> bool;;
val ply : pos -> gameboard -> player option;;
