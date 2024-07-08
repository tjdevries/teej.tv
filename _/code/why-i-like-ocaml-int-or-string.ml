type t =
  | String of string
  | Int of int
  | Float of float
  | Bool of bool

let string (s : string) -> t = String s
let int (i : int) -> t = Int i
let float (f : float) -> t = Float f
let bool (b : bool) -> t = Bool b
