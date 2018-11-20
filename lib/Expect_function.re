/*
 * Expect
 *
 * Subset of Jest expect API
 */


type fn('a) = unit => 'a;

type expectFunction('a) = {
  toThrow: exn => unit
};

let _assertThrows = (f: fn('a), expectedException: exn) => {

    let _ = try(f()) {
    | x => x == expectedException ? print_endline ("Exception matches!") : print_endline ("Exception does not match");
    }

}

let expect = (f: fn('a)) => {
  let ret: expectFunction('a) = {
    toThrow: _assertThrows(f),
  };

  ret;
};
