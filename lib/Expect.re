/*
 * Expect
 *
 * Subset of Jest expect API
 */

type expectationFailedProps = {
    actualValue: string,
    expectedValue: string,
};

exception ExpectationFailed(expectationFailedProps);

type comparer('a) = ('a, 'a) => bool;
type printer('a) = ('a) => string;

let invert = (c: comparer('a)) => {
    let ret = (a, b) => !c(a, b);
    ret;
};

let _assertEqual = (c: comparer('a), p: printer('a), actualValue: 'a, expectedValue: 'a) => {

    if(!c(actualValue, expectedValue)) {
        let props: expectationFailedProps = {
            actualValue: p(actualValue),
            expectedValue: p(expectedValue),
        };
        raise(ExpectationFailed(props));
    }

};

type expect('a) = {
  toEqual: 'a => unit,
  toBe: 'a => unit,
  toNotEqual: 'a => unit,
  toNotBe: 'a => unit,
};

let _expect = (c: comparer('a), p: printer('a), v: 'a) => {
  let ret: expect('a) = {
    toEqual: _assertEqual(c, p, v),
    toBe: _assertEqual(c, p, v),
    toNotEqual: _assertEqual(invert(c), p, v),
    toNotBe: _assertEqual(invert(c), p, v),
  };

  ret;
};

let expect = (v: 'a) => {
    let c: comparer('a) = (a, b) => a == b;
    let p: printer('a) = (_a: 'a) => "[object]";
    _expect(c, p, v);
};

module type ExpectCore {
    type t;
    let compare: comparer(t);
    let show: printer(t);
};

module Make = (Core: ExpectCore) => {
    let expect = _expect(Core.compare, Core.show);
};

module FloatExpecter {
    type t = float;
    let compare = (a: float, b: float) => a == b;
    let show = (a: float) => string_of_float(a);
};

module StringExpecter {
    type t = string;
    let compare = (a: string, b: string) => String.equal(a, b);
    let show = (a) => a;
}

module Expect_float = Make(FloatExpecter);
module Expect_string = Make(StringExpecter);


