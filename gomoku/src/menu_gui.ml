let display () =
  begin
    Gui.clear_window Graphics.blue;
    Gui.draw_text (Gui.ratio 1 2, Gui.ratio 7 8) "GOMOKU!!!" Graphics.green;
    Gui.draw_button (Gui.ratio 1 2, Gui.ratio 3 4) (400, 100) "NOWA GRA" Graphics.magenta;
    Gui.draw_button (Gui.ratio 1 2, Gui.ratio 1 2) (400, 100) "STATYSTYKI" Graphics.magenta;
    Gui.draw_button (Gui.ratio 1 2, Gui.ratio 1 4) (400, 100) "WYJSCIE" Graphics.magenta;
    Gui.draw_text (Gui.ratio 1 2, Gui.ratio 1 8) "(C) RAFAL KALETA, MIT LICENSE" Graphics.black
  end;;

let rec click_button () =
  let mp = Gui.mouse_click () in
  let buttons = [Gui.ratio 3 4; Gui.ratio 1 2; Gui.ratio 1 4] in
  let clk = List.map (fun y -> Gui.check_button_clicked (Gui.ratio 1 2, y) (400, 100) mp) buttons in
  let rec choose_action lst i =
    match lst with
    | true::_ -> i
    | false::xs -> choose_action xs @@ i + 1
    | [] -> -1 in
  let index = choose_action clk 0 in
  if index >= 0
  then index
  else click_button ();;
