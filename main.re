open Printf

/*
 * Print a file to stdout
 */
let cat = (str) => try {
  // open the fie
  let fd = Unix.openfile(str, [Unix.O_RDONLY], 0)

  // fstat to know how big the file is
  let buffer_size = Unix.fstat(fd).st_size
  let buffer = Bytes.create(buffer_size)

  switch (Unix.read(fd, buffer, 0, buffer_size)) {
  | 0 => ()
  | r => ignore(Unix.write(Unix.stdout, buffer, 0, r))
  }

  Unix.close(fd)
} {
| Unix.Unix_error(Unix.ENOENT, _, str) => printf("cat: %s: No such a file or directory\n", str)
| Unix.Unix_error(Unix.EISDIR, _, _) => printf("cat: %s: Is a directory\n", str)
| _ => printf("cat: %s: Unknown error\n", str)
}

let main = {
  // drop the first argument from Sys.argv
  let args = Sys.argv |> Array.to_list |> List.tl

  // cat concatenates multiple files
  List.iter(cat, args)
  exit(0)
}
