let step = 24;;

let get_borders size =
  let cols = size/2+1 and half = Gui.ratio 1 2 in
  (half+step*cols, half-step*cols);;

let get_lines_pos size =
  let cols = size/2+1 and half = Gui.ratio 1 2 in
  let rec glp i acc =
    if i+cols >= 0
    then glp (i-1) ((half+step*i)::acc)
    else acc in
  glp cols [];;

let norm size (x, y) =
  let (_, endline) = get_borders size in
  let nrm w = (w-endline+step/2)/step in
  (nrm x, nrm y);;

let display size =
  let pos = get_lines_pos size
  and (pbeg, pend) = get_borders size in
  let rec draw_lines lst =
    match lst with
    | [] -> ()
    | p::ps ->
      begin
        Graphics.set_color Graphics.black;
        Graphics.moveto p pbeg;
        Graphics.lineto p pend;
        Graphics.moveto pbeg p;
        Graphics.lineto pend p;
        draw_lines ps
      end in
  begin
    Gui.clear_window Graphics.cyan;
    draw_lines pos
  end;;

let draw_stone size ply (row, col) =
  let (_, endline) = get_borders size in
  let stone_color =
    match ply with
    | Board.Human -> Graphics.white
    | Board.Comp -> Graphics.black
    | Board.Blocked -> raise @@ Board.Incorrect_player "Game_gui.draw_stone" in
  let (px, py) = (endline+col*step, endline+row*step) in
  begin
    Graphics.set_color stone_color;
    Graphics.fill_circle px py (7*step/16)
  end;;

let rec choose_stone size =
  let (px, py) = norm size @@ Gui.mouse_click () in
  if px >= 1 && px <= size && py >= 1 && py <= size
  then (py, px)
  else choose_stone size;;

let return winner =
  let print_winner () =
    match winner with
    | Board.Human -> Gui.draw_text (Gui.ratio 1 2, Gui.ratio 92 100) "WYGRANA!!! :)" Graphics.blue
    | Board.Comp -> Gui.draw_text (Gui.ratio 1 2, Gui.ratio 92 100) "PRZEGRANA :(" Graphics.red
    | Board.Blocked -> raise @@ Board.Incorrect_player "Game_gui.draw_stone" in
  let rec ret () =
    let mp = Gui.mouse_click () in
    if Gui.check_button_clicked (Gui.ratio 1 2, Gui.ratio 1 16) (160, 30) mp
    then ()
    else ret () in
  begin
    print_winner ();
    Gui.draw_button (Gui.ratio 1 2, Gui.ratio 1 16) (160, 30) "POWROT" Graphics.white;
    ret ()
  end;;
