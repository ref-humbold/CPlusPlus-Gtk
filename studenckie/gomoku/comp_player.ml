let choose size = (1+Random.int (size-1), 1+Random.int (size-1));;

let rec move size gameboard =
    let pos = choose size in
    if Board.is_free pos gameboard
    then pos
    else move size gameboard;;
