exception Stat_format_error;;

val filename : string;;
val write : int list -> unit;;
val read : unit -> int list;;
val end_game : bool -> int -> int -> int -> unit;;