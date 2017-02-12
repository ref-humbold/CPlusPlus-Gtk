let window_size = 800;;

let sc n d =
    let rec gcd a b =
        if a = 0
        then b
        else if a > b
        then gcd b a
        else gcd (b mod a) a in
    let n' = n/(gcd n d) and d' = d/(gcd n d) in
    n'*window_size/d';;

let center_text (xc, yc) str =
    let (xt, yt) = Graphics.text_size str in
    (xc-xt/2, yc-yt/2);;

let new_window () =
    begin
        Graphics.open_graph @@ " "^(string_of_int window_size)^"x"^(string_of_int window_size);
        Graphics.set_text_size 15
    end;;

let clear_window clr =
    begin
        Graphics.clear_graph ();
        Graphics.set_color clr;
        Graphics.fill_rect 0 0 window_size window_size
    end;;

let draw_text ctr txt clr =
    let (x, y) = center_text ctr txt in
    begin
        Graphics.set_color clr;
        Graphics.moveto x y;
        Graphics.draw_string txt
    end;;

let draw_button (xc, yc) (w, h) lbl clr =
    begin
        Graphics.set_color clr;
        Graphics.fill_rect (xc-w/2) (yc-h/2) w h;
        draw_text (xc, yc) lbl Graphics.black
    end;;

let mouse_click () =
    let st = Graphics.wait_next_event [Graphics.Button_down] in
    (st.mouse_x, st.mouse_y);;

let check_button_clicked (xc, yc) (w, h) (mpx, mpy) = abs (mpx-xc) <= w && abs (mpy-yc) <= h;;
