let buttons = [Gui.Btn {xc=Gui.ratio 1 4; yc=Gui.ratio 3 4; width=200; height=100};
               Gui.Btn {xc=Gui.ratio 3 4; yc=Gui.ratio 3 4; width=200; height=100};
               Gui.Btn {xc=Gui.ratio 1 4; yc=Gui.ratio 1 2; width=200; height=100};
               Gui.Btn {xc=Gui.ratio 3 4; yc=Gui.ratio 1 2; width=200; height=100};
               Gui.Btn {xc=Gui.ratio 1 4; yc=Gui.ratio 1 4; width=200; height=100};
               Gui.Btn {xc=Gui.ratio 3 4; yc=Gui.ratio 1 4; width=200; height=100}];;


let display () =
  begin
    Gui.clear_window Graphics.cyan;
    Gui.draw_text (Gui.ratio 1 2, Gui.ratio 9 10) "WYBIERZ ROZMIAR PLANSZY" Graphics.black;
    Gui.draw_button (Gui.ratio 1 4, Gui.ratio 3 4) (200, 100) "15 x 15" Graphics.green;
    Gui.draw_button (Gui.ratio 3 4, Gui.ratio 3 4) (200, 100) "17 x 17" Graphics.green;
    Gui.draw_button (Gui.ratio 1 4, Gui.ratio 1 2) (200, 100) "19 x 19" Graphics.green;
    Gui.draw_button (Gui.ratio 3 4, Gui.ratio 1 2) (200, 100) "21 x 21" Graphics.green;
    Gui.draw_button (Gui.ratio 1 4, Gui.ratio 1 4) (200, 100) "23 x 23" Graphics.green;
    Gui.draw_button (Gui.ratio 3 4, Gui.ratio 1 4) (200, 100) "25 x 25" Graphics.green
  end;;

let rec choose_size () =
  let mp = Gui.mouse_click () in
  let buttons = [(Gui.ratio 1 4, Gui.ratio 3 4); (Gui.ratio 3 4, Gui.ratio 3 4);
                 (Gui.ratio 1 4, Gui.ratio 1 2); (Gui.ratio 3 4, Gui.ratio 1 2);
                 (Gui.ratio 1 4, Gui.ratio 1 4); (Gui.ratio 3 4, Gui.ratio 1 4)] in
  let clk = List.map (fun p -> Gui.check_button_clicked p (200, 100) mp) buttons in
  let rec get_size lst sz =
    match lst with
    | true::_ -> sz
    | false::xs -> get_size xs @@ sz + 2
    | [] -> 0 in
  let boardsize = get_size clk 15 in
  if boardsize > 0
  then boardsize
  else choose_size ();;
