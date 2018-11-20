open Rejest;

module Expect_function_test = Expect_function_test;

test("hello world test", () => {
  expect(1).toEqual(1);
  expect("Hello").toNotEqual("World");
});

test("expect", () =>
  test("string: equal comparison", () =>
    ()
  )
);

Rejest.run();
