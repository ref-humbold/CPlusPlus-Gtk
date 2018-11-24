let buttons = [Gui.Btn {xc=Gui.ratio 1 2; yc=Gui.ratio 3 4;
                        width=400; height=100;
                        label="NOWA GRA"; colour=Graphics.magenta};
               Gui.Btn {xc=Gui.ratio 1 2; yc=Gui.ratio 1 2;
                        width=400; height=100;
                        label="STATYSTYKI"; colour=Graphics.magenta};
               Gui.Btn {xc=Gui.ratio 1 2; yc=Gui.ratio 1 4;
                        width=400; height=100;
                        label="WYJSCIE"; colour=Graphics.magenta}];;

let texts = [Gui.Txt {xc=Gui.ratio 1 2; yc=Gui.ratio 7 8;
                      label=Gui.window_title; colour=Graphics.green};
             Gui.Txt {xc=Gui.ratio 1 2; yc=Gui.ratio 1 8;
                      label="(C) 2017 RAFAL KALETA, MIT LICENSE"; colour=Graphics.black}];;

let display () =
  begin
    Gui.clear_window Graphics.blue;
    Gui.draw_buttons buttons;
    Gui.draw_texts texts
  end;;

let rec click_button () =
  let mouse_pos = Gui.mouse_click () in
  let clicked = List.map (Gui.check_button_clicked mouse_pos) buttons in
  let rec choose_action lst i =
    match lst with
    | true::_ -> i
    | false::xs -> choose_action xs @@ i + 1
    | [] -> -1 in
  let index = choose_action clicked 0 in
  if index >= 0
  then index
  else click_button ();;
