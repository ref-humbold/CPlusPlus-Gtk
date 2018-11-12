type button = Btn of {xc: int; yc: int; width: int; height: int};;

let window_size = 800;;

let ratio n d =
  let rec gcd a b =
    if a = 0
    then b
    else if a > b
    then gcd b a
    else gcd (b mod a) a in
  let n' = n / (gcd n d)
  and d' = d / (gcd n d) in
  n' * window_size / d';;

let center_text (xc, yc) text =
  let (xt, yt) = Graphics.text_size text in
  (xc - xt / 2, yc - yt / 2);;

let new_window () =
  begin
    Graphics.open_graph @@ " " ^ (string_of_int window_size) ^ "x" ^ (string_of_int window_size);
    Graphics.set_text_size 15
  end;;

let clear_window colour =
  begin
    Graphics.clear_graph ();
    Graphics.set_color colour;
    Graphics.fill_rect 0 0 window_size window_size
  end;;

let draw_text center_pos text colour =
  let (x, y) = center_text center_pos text in
  begin
    Graphics.set_color colour;
    Graphics.moveto x y;
    Graphics.draw_string text
  end;;

let draw_button (xc, yc) (width, height) label colour =
  begin
    Graphics.set_color colour;
    Graphics.fill_rect (xc - width / 2) (yc - height / 2) width height;
    draw_text (xc, yc) label Graphics.black
  end;;

let mouse_click () =
  let st = Graphics.wait_next_event [Graphics.Button_down] in
  (st.Graphics.mouse_x, st.Graphics.mouse_y);;

let check_button_clicked (xc, yc) (w, h) (mpx, mpy) = abs (mpx - xc) <= w && abs (mpy - yc) <= h;;
