open Rejest;

exception MyTestException(string);

test("Expect_function", () => {
  test("toThrow", () => {
        test("Works with an exception", () => {
            let fn = () => raise(MyTestException("Hello2"));

            Expect_function.expect(fn).toThrow(MyTestException("Hello"));
        })
    });
});
