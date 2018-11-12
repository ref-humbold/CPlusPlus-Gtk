let buttons = [Gui.Btn {xc=Gui.ratio 1 4; yc=Gui.ratio 3 4;
                        width=200; height=100;
                        label="15 x 15"; colour=Graphics.green};
               Gui.Btn {xc=Gui.ratio 3 4; yc=Gui.ratio 3 4;
                        width=200; height=100;
                        label="17 x 17"; colour=Graphics.green};
               Gui.Btn {xc=Gui.ratio 1 4; yc=Gui.ratio 1 2;
                        width=200; height=100;
                        label="19 x 19"; colour=Graphics.green};
               Gui.Btn {xc=Gui.ratio 3 4; yc=Gui.ratio 1 2;
                        width=200; height=100;
                        label="21 x 21"; colour=Graphics.green};
               Gui.Btn {xc=Gui.ratio 1 4; yc=Gui.ratio 1 4;
                        width=200; height=100;
                        label="23 x 23"; colour=Graphics.green};
               Gui.Btn {xc=Gui.ratio 3 4; yc=Gui.ratio 1 4;
                        width=200; height=100;
                        label="25 x 25"; colour=Graphics.green}];;

let text = Gui.Txt {xc=Gui.ratio 1 2; yc=Gui.ratio 9 10;
                    label="WYBIERZ ROZMIAR PLANSZY"; colour=Graphics.black};;

let display () =
  begin
    Gui.clear_window Graphics.cyan;
    Gui.draw_text text;
    Gui.draw_buttons buttons
  end;;

let rec choose_size () =
  let mouse_pos = Gui.mouse_click () in
  let clicked = List.map (Gui.check_button_clicked mouse_pos) buttons in
  let rec get_size lst size =
    match lst with
    | true::_ -> size
    | false::xs -> get_size xs @@ size + 2
    | [] -> 0 in
  let boardsize = get_size clicked 15 in
  if boardsize > 0
  then boardsize
  else choose_size ();;
