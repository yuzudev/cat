open Printf

(**
 * Print a file to stdout
 *)
let cat str = try
        let fd = Unix.openfile str [Unix.O_RDONLY] 0 in
        let buffer_size = (Unix.fstat fd).st_size in
        let buffer = Bytes.create buffer_size in

        match Unix.read fd buffer 0 buffer_size with
        | 0 -> ()
        | r -> ignore (Unix.write Unix.stdout buffer 0 r);
        Unix.close fd;
with
| Unix.Unix_error(Unix.ENOENT, _, str) -> printf "cat: %s: No such file or directory\n" str
| Unix.Unix_error(Unix.EISDIR, _, _) -> printf "cat: %s: Is a directory\n" str
| _ -> printf "cat: %s: Unknown error\n" str

let rec drop n lst = match lst with
| [] -> []
| x :: xs -> if n > 0 then drop (n - 1) xs else lst

let main = begin
        let args = Sys.argv |> Array.to_list |> drop 1 in

        List.iter cat args;
        exit 0;
end
