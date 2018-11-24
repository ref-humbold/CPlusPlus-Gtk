type stat_info = St of {hmoves: int; cmoves: int;
                        won: int; lost: int;
                        thmoves: int; tcmoves: int;
                        opened: int}

exception Stat_format_error of string;;

let filename = ".gomoku.stat";;

let str_case () = if Random.bool () then 'A' else 'a';;

let encode_num num =
  let enc num' res =
    if num' = 0
    then String.make 1 @@ str_case ()
    else
      let rec enc' num'' res' =
        if num'' = 0
        then res'
        else
          let n = num'' mod 10 in
          let base = Char.code @@ str_case () in
          let newres = (String.make 1 @@ Char.chr @@ 2 * n + base) ^ res' in
          enc' (num'' / 10) newres in
      enc' num' res in
  enc num "";;

let encode stat_rcd =
  let stat_to_list (St {hmoves; cmoves; won; lost; thmoves; tcmoves; opened}) =
    [hmoves; cmoves; won; lost; thmoves; tcmoves; opened] in
  let rec cncmap lst res =
    match lst with
    | [] -> res
    | [x] -> res ^ (encode_num x)
    | (x::xs) ->
      let base = Char.code @@ str_case () in
      let sep = String.make 1 @@ Char.chr @@ 2 * (Random.int 16) + base - 3 in
      cncmap xs @@ res ^ (encode_num x) ^ sep in
  cncmap (stat_to_list stat_rcd) "";;

let decode str =
  let rec split str' i act res =
    if i = String.length str'
    then (List.rev act)::res
    else
      let cd = (Char.code str'.[i]) mod 32 in
      let cd' =
        if cd mod 2 = 1 && cd < 20
        then Some (cd / 2)
        else None in
      match cd' with
      | None ->
        ( match act with
          | [] -> split str' (i + 1) [] res
          | _ -> split str' (i + 1) [] @@ (List.rev act)::res
        )
      | Some x -> split str' (i + 1) (x::act) res in
  let rec make_int res lst =
    match lst with
    | [] -> res
    | x::xs -> make_int (res * 10 + x) xs in
  let stat_from_list lst =
    match lst with
    | [hmoves_num; cmoves_num; won_num; lost_num;
       thmoves_num; tcmoves_num; opened_num] ->
      St {hmoves=(make_int 0 hmoves_num); cmoves=(make_int 0 cmoves_num);
          won=(make_int 0 won_num); lost=(make_int 0 lost_num);
          thmoves=(make_int 0 thmoves_num); tcmoves=(make_int 0 tcmoves_num);
          opened=(make_int 0 opened_num)}
    | _ -> raise @@ Stat_format_error "Stat.read" in
  stat_from_list @@ List.rev @@ split str 0 [] [];;

let write stat_rcd =
  let text = encode stat_rcd in
  let file = open_out filename in
  begin
    output_string file text;
    flush file;
    close_out file
  end;;

let clear () = write @@ St {hmoves=0; cmoves=0;
                            won=0; lost=0;
                            thmoves=0; tcmoves=0;
                            opened=0};;

let read () =
  let file =
    try open_in filename with
    | Sys_error _ ->
      begin
        clear ();
        open_in filename
      end in
  let text = input_line file in
  begin
    close_in file;
    decode text
  end;;

let update_data winner human_moves comp_moves =
  match read () with
  | St {won; lost; thmoves; tcmoves; opened; _} ->
    ( match winner with
      | Board.Human ->
        write @@ St {hmoves=human_moves; cmoves=comp_moves;
                     won=(won + 1); lost;
                     thmoves=(thmoves + human_moves);
                     tcmoves=(tcmoves + comp_moves);
                     opened}
      | Board.Comp ->
        write @@ St {hmoves=human_moves; cmoves=comp_moves;
                     won; lost=(lost + 1);
                     thmoves=(thmoves + human_moves);
                     tcmoves=(tcmoves + comp_moves);
                     opened}
      | Board.Blocked -> raise @@ Board.Incorrect_player "Stat.end_game"
    );;

let prepare_data () =
  match read () with
  | St rcd -> write @@ St {rcd with opened=(rcd.opened + 1)}
