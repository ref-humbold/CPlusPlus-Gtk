val window_size : int;;
val sc : int -> int -> int;;
val center_text : (int * int) -> string -> (int * int);;
val new_window : unit -> unit;;
val clear_window : Graphics.color -> unit;;
val draw_text : (int * int) -> string -> Graphics.color -> unit;;
val draw_button : (int * int) -> (int * int) -> string -> Graphics.color -> unit;;
