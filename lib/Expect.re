/*
 * Expect
 *
 * Subset of Jest expect API
 */

type expectationFailedProps = {
    actualValue: Obj.t,
    expectedValue: Obj.t,
};

exception ExpectationFailed(expectationFailedProps);

let _assertEqual = (actualValue: 'a, expectedValue: 'a) => {

    if(actualValue != expectedValue) {
        let props: expectationFailedProps = {
            actualValue: Obj.repr(actualValue),
            expectedValue: Obj.repr(expectedValue),
        };
        raise(ExpectationFailed(props));
    }

};

let _assertNotEqual = (_actualValue: 'a, _expectedValue: 'a) => {
 /* TODO */
    ();
};

type expect('a) = {
  toEqual: 'a => unit,
  toBe: 'a => unit,
  toNotEqual: 'a => unit,
  toNotBe: 'a => unit,
};

let expect = (v: 'a) => {
  let ret: expect('a) = {
    toEqual: t => _assertEqual(v, t),
    toBe: a => _assertEqual(v, a),
    toNotEqual: t => _assertNotEqual(v, t),
    toNotBe: t => _assertNotEqual(v, t),
  };

  ret;
};
