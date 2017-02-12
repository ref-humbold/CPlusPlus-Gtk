let rec check_click () =
    let mp = Gui.mouse_click () in
    if Gui.check_button_clicked (Gui.sc 3 4, Gui.sc 2 16) (160, 50) mp
    then 0
    else if Gui.check_button_clicked (Gui.sc 1 4, Gui.sc 2 16) (160, 50) mp
    then begin Stat.clear (); 1 end
    else check_click ();;

let display () =
    let lst = Stat.read () in
    let print_info ctr str = Gui.draw_text ctr str Graphics.black in
    match lst with
    | [hmoves; cmoves; totwon; totlost; tothmoves; totcmoves; totopen] ->
        begin
            Gui.clear_window Graphics.yellow;
            Graphics.set_color Graphics.black;
            print_info (Gui.sc 1 2, Gui.sc 14 16) "STATYSTYKI:";
            print_info (Gui.sc 1 2, Gui.sc 12 16) @@ "LICZBA URUCHOMIEN PROGRAMU: "^(string_of_int totopen);
            print_info (Gui.sc 1 2, Gui.sc 11 16) @@ "LICZBA ROZEGRANYCH GIER: "^(string_of_int (totwon+totlost));
            print_info (Gui.sc 1 4, Gui.sc 10 16) @@ "WYGRANYCH: "^(string_of_int totwon);
            print_info (Gui.sc 3 4, Gui.sc 10 16) @@ "PRZEGRANYCH: "^(string_of_int totlost);
            print_info (Gui.sc 1 2, Gui.sc 9 16) @@ "CALKOWITA LICZBA RUCHOW: "^(string_of_int (tothmoves+totcmoves));
            print_info (Gui.sc 1 4, Gui.sc 8 16) @@ "TWOICH: "^(string_of_int tothmoves);
            print_info (Gui.sc 3 4, Gui.sc 8 16) @@ "KOMPUTERA: "^(string_of_int totcmoves);
            print_info (Gui.sc 1 2, Gui.sc 6 16) @@ "LICZBA RUCHOW W OSTATNIEJ GRZE: "^(string_of_int (hmoves+cmoves));
            print_info (Gui.sc 1 4, Gui.sc 5 16) @@ "TWOICH: "^(string_of_int hmoves);
            print_info (Gui.sc 3 4, Gui.sc 5 16) @@ "KOMPUTERA: "^(string_of_int cmoves);
            Gui.draw_button (Gui.sc 1 4, Gui.sc 2 16) (160, 50) "WYCZYSC" Graphics.blue;
            Gui.draw_button (Gui.sc 3 4, Gui.sc 2 16) (160, 50) "POWROT" Graphics.red
        end
    | _ -> raise @@ Stat.Stat_format_error "Stat_gui.display";;
