/*
 * TestReporter
 */

open Types;

type testResultContext = {
  testName: string,
  mutable testResult,
  parent: option(testResultContext),
  mutable children: list(testResultContext),
};

let rootContext: testResultContext = {
  testName: "__root",
  testResult: Pass,
  parent: None,
  children: [],
};

let currentContext: ref(testResultContext) = ref(rootContext);

let startTest = (testName: string) => {
  let newContext: testResultContext = {
    testName,
    testResult: Pass,
    parent: Some(currentContext^),
    children: [],
  };

  currentContext^.children =
    List.append(currentContext^.children, [newContext]);

  currentContext := newContext;
};

let endTest = (_testName: string, result: testResult) => {
  currentContext^.testResult = result;

  switch (currentContext^.parent) {
  | Some(x) => currentContext := x
  | None => ()
  };
};

let printTestResult = (context: testResultContext, level: int) => {
  let padding = String.make(level * 2, ' ');

  switch (context.testResult) {
  | Pass => print_endline(padding ++ " PASS " ++ context.testName)
  | Fail(_) => print_endline(padding ++ " FAIL " ++ context.testName)
  };
};

let rec printContext = (context: testResultContext, level: int) => {
  context.testName == "__root" ? () : printTestResult(context, level);

  List.iter(c => printContext(c, level + 1), context.children);
};

let rec printErrors = (context: testResultContext) => {
  switch (context.testResult) {
  | Fail(x) =>
    print_endline("FAIL: " ++ context.testName);

    switch (x) {
    | ExpectationFailed(_p) =>
      print_endline("Expectation Failed: " ++ Printexc.to_string(x));
      print_endline("Expected: " ++ _p.expectedValue);
      print_endline("Actual: " ++ _p.actualValue);
      print_endline(" Callstack: " ++ _p.callstack);
    | x => print_endline("Unhandled exception: " ++ Printexc.to_string(x))
    };
    print_endline("");
  | _ => ()
  };

  List.iter(c => printErrors(c), context.children);
};

let rec didContextPass = (context: testResultContext) =>
  switch (context.testResult) {
  | Fail(_) => false
  | Pass =>
    true
    && List.fold_left(
         (prev, c) => prev && didContextPass(c),
         true,
         context.children,
       )
  };

let passed = () => didContextPass(rootContext);

let printSummary = () => {
  print_endline("");
  printContext(rootContext, 0);
  print_endline("");

  printErrors(rootContext);
};
