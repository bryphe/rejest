/*
 * Expect
 *
 * Subset of Jest expect API
 */

module Expect_exn = Expect.Expect_exn;

type fn('a) = unit => 'a;

type expectFunction('a) = {toThrow: exn => unit};

let _assertThrows = (f: fn('a), expectedException: exn) => {
  let _ =
    try (f()) {
    | x => Expect_exn.expect(x).toEqual(expectedException)
    };
  ();
};

let expect = (f: fn('a)) => {
  let ret: expectFunction('a) = {toThrow: _assertThrows(f)};

  ret;
};
