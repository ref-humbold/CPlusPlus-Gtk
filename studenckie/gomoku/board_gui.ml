let step = 24;;

let get_lines_pos size =
    let szn = size/2+1 and half = Gui.sc 1 2 in
    let rec glp i acc =
        print_int i;
        if i+szn >= 0
        then glp (i-1) ((half+step*i)::acc)
        else acc in
    (glp szn [], half+step*(size/2+1), half-step*(size/2+1));;

let display_sizemenu () =
    begin
        Gui.clear_window Graphics.cyan;
        Gui.draw_text (Gui.sc 1 2, Gui.sc 9 10) "WYBIERZ ROZMIAR PLANSZY" Graphics.black;
        Gui.draw_button (Gui.sc 1 4, Gui.sc 3 4) (200, 100) "15 x 15" Graphics.green;
        Gui.draw_button (Gui.sc 3 4, Gui.sc 3 4) (200, 100) "17 x 17" Graphics.green;
        Gui.draw_button (Gui.sc 1 4, Gui.sc 1 2) (200, 100) "19 x 19" Graphics.green;
        Gui.draw_button (Gui.sc 3 4, Gui.sc 1 2) (200, 100) "21 x 21" Graphics.green;
        Gui.draw_button (Gui.sc 1 4, Gui.sc 1 4) (200, 100) "23 x 23" Graphics.green;
        Gui.draw_button (Gui.sc 3 4, Gui.sc 1 4) (200, 100) "25 x 25" Graphics.green
    end;;

let display_stone ply (x, y) =
    let stone_color =
        match ply with
        | Board.Human -> Graphics.white
        | Board.Comp -> Graphics.black in
    begin
        Graphics.set_color stone_color;
        Graphics.fill_circle x y (7*step/16)
    end

let display_board size =
    let (pos, pbeg, pend) = get_lines_pos size in
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