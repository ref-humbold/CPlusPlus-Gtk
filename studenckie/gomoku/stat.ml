exception Stat_format_error;;

let filename = "statistics";;

let encnum num =
    let enc num_ res =
        if num_ = 0
        then if Random.bool () then "A" else "a"
        else let rec enc' num_' res' =
                if num_' = 0
                then res'
                else let n = num_' mod 10 in
                    let newres =
                        if Random.bool ()
                        then (String.make 1 @@ Char.chr @@ 2*n+65)^res'
                        else (String.make 1 @@ Char.chr @@ 2*n+97)^res' in
                    enc' (num_'/10) newres in
            enc' num_ res in
    enc num "";;

let encode lst =
    let rec cncmap lst_ res =
        match lst_ with
        | [] -> res
        | [x] -> res^(encnum x)
        | (x::xs) ->
                let sep =
                    if Random.bool ()
                    then String.make 1 @@ Char.chr @@ 2*(Random.int 15)+64
                    else String.make 1 @@ Char.chr @@ 2*(Random.int 15)+96 in
                cncmap xs @@ res^(encnum x)^sep in
    cncmap lst "";;

let decode str =
    let rec split str_ i act res =
        if i = String.length str_
        then (List.rev act)::res
        else let cd = (Char.code str_.[i]) mod 32 in
                let cd' =
                    if cd mod 2 = 1 && cd < 20
                    then Some (cd/2)
                    else None in
                match cd' with
                | None ->
                    begin
                        match act with
                        | [] -> split str_ (i+1) [] res
                        | _ -> split str_ (i+1) [] ((List.rev act)::res)
                        end
                | Some x -> split str_ (i+1) (x::act) res in
    let rec dec res lst_ =
        match lst_ with
        | [] -> res
        | x::xs -> dec (res*10+x) xs in
    List.map (dec 0) @@ List.rev @@ split str 0 [] [];;

let write lst =
    let text = encode lst in
    let file = open_out filename in
    output_string file text; flush file; close_out file;;

let read () =
    let file = try open_in filename with
        | Sys_error _ -> begin write [0; 0; 0; 0; 0; 0; 0; 0]; open_in filename end in
    let text = input_line file in
    close_in file; decode text;;

let write lst =
    let text = encode lst in
    let file = open_out filename in
    output_string file text; flush file; close_out file;;

let end_game winner hmoves cmoves time =
    let data = read () in
    match data with
    | [_; _; _; twn; tls; thm; tcm; tt] ->
        begin
            match winner with
            | Board.Human -> write [time; hmoves; cmoves; twn+1; tls; thm+hmoves; tcm+cmoves; tt+time]
            | Board.Comp -> write [time; hmoves; cmoves; twn; tls+1; thm+hmoves; tcm+cmoves; tt+time]
        end
    | _ -> raise Stat_format_error;;
