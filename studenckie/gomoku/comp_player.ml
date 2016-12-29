let choose () = (read_int (), read_int ());;

let move game =
    let p = choose () in
    if Board.free p game
    then p
    else failwith "Field is occuppied."
