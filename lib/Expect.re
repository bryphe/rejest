/*
 * Expect
 *
 * Subset of Jest expect API
 */

type expect('a) = {
    toEqual: ('a) => unit,
    toBe: ('a) => unit
};

let expect = (v: 'a) => {
    let ret: expect('a) = {
        toEqual: (_t) => (),
        toBe: (_a) => (),
    };

    ret;
};
