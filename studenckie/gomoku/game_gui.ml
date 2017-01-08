let step = 24;;

let get_borders size =
    let szn = size/2+1 and half = Gui.sc 1 2 in
    (half+step*szn, half-step*szn);;

let get_lines_pos size =
    let szn = size/2+1 and half = Gui.sc 1 2 in
    let rec glp i acc =
        if i+szn >= 0
        then glp (i-1) ((half+step*i)::acc)
        else acc in
    glp szn [];;

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

let draw_stone size ply (x, y) =
    let (_, endline) = get_borders size in
    let stone_color =
        match ply with
        | Board.Human -> Graphics.white
        | Board.Comp -> Graphics.black in
    let (px, py) = (endline+x*step, endline+y*step) in
    begin
        Graphics.set_color stone_color;
        Graphics.fill_circle px py (7*step/16)
    end;;

let rec choose_stone size =
    let (px, py) = norm size @@ Gui.mouse_click () in
    if px >= 1 && px <= size && py >= 1 && py <= size
    then (px, py)
    else choose_stone size;;

let return () =
    let rec ret () =
        let mp = Gui.mouse_click () in
        if Gui.check_button_clicked (Gui.sc 1 2, Gui.sc 1 10) (160, 30) mp
        then ()
        else ret () in
    begin
        Gui.draw_button (Gui.sc 1 2, Gui.sc 1 10) (160, 30) "POWROT" Graphics.red;
        ret ()
    end;;
