exception Stat_format_error of string;;

let filename = ".gomoku.stat";;

let str_case () = if Random.bool () then 'A' else 'a';;

let encode_num num =
  let enc num_ res =
    if num_ = 0
    then String.make 1 @@ str_case ()
    else
      let rec enc' num_' res' =
        if num_' = 0
        then res'
        else
          let n = num_' mod 10 in
          let base = Char.code @@ str_case () in
          let newres = (String.make 1 @@ Char.chr @@ 2 * n + base) ^ res' in
          enc' (num_' / 10) newres in
      enc' num_ res in
  enc num "";;

let encode lst =
  let rec cncmap lst_ res =
    match lst_ with
    | [] -> res
    | [x] -> res ^ (encode_num x)
    | (x::xs) ->
      let base = Char.code @@ str_case () in
      let sep = String.make 1 @@ Char.chr @@ 2 * (Random.int 16) + base - 3 in
      cncmap xs @@ res ^ (encode_num x) ^ sep in
  cncmap lst "";;

let decode str =
  let rec split str_ i act res =
    if i = String.length str_
    then (List.rev act)::res
    else
      let cd = (Char.code str_.[i]) mod 32 in
      let cd' =
        if cd mod 2 = 1 && cd < 20
        then Some (cd / 2)
        else None in
      match cd' with
      | None ->
        ( match act with
          | [] -> split str_ (i + 1) [] res
          | _ -> split str_ (i + 1) [] ((List.rev act)::res)
        )
      | Some x -> split str_ (i + 1) (x::act) res in
  let rec dec res lst_ =
    match lst_ with
    | [] -> res
    | x::xs -> dec (res * 10 + x) xs in
  List.map (dec 0) @@ List.rev @@ split str 0 [] [];;

let write lst =
  let text = encode lst in
  let file = open_out filename in
  output_string file text; flush file; close_out file;;

let clear () = write [0; 0; 0; 0; 0; 0; 0];;

let read () =
  let file =
    try open_in filename with
    | Sys_error _ -> begin clear (); open_in filename end in
  let text = input_line file in
  close_in file; decode text;;

let update_data winner hmoves cmoves =
  let data = read () in
  match data with
  | [_; _; twn; tls; thm; tcm; topen] ->
    ( match winner with
      | Board.Human ->
        write [hmoves; cmoves; twn + 1; tls; thm + hmoves; tcm + cmoves; topen]
      | Board.Comp ->
        write [hmoves; cmoves; twn; tls + 1; thm + hmoves; tcm + cmoves; topen]
      | Board.Blocked -> raise @@ Board.Incorrect_player "Stat.end_game"
    )
  | _ -> raise @@ Stat_format_error "Stat.update_data";;

let prepare_data () =
  let data = read () in
  match data with
  | [hm; cm; twn; tls; thm; tcm; topen] ->
    write [hm; cm; twn; tls; thm; tcm; topen + 1]
  | _ -> raise @@ Stat_format_error "Stat.prepare_data";;
