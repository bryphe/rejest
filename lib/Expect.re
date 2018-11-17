/*
 * Expect
 *
 * Subset of Jest expect API
 */

type expect('a) = {
  toEqual: 'a => unit,
  toBe: 'a => unit,
  toNotEqual: 'a => unit,
  toNotBe: 'a => unit,
};

let expect = (v: 'a) => {
  let ret: expect('a) = {
    toEqual: t => assert(v == t),
    toBe: a => assert(v == a),
    toNotEqual: t => assert(t !== v),
    toNotBe: t => assert(t !== v),
  };

  ret;
};
