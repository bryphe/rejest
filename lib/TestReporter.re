/*
 * TestReporter
 */

open LTerm_style;
open LTerm_text;

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

  let%lwt _ =
    switch (context.testResult) {
    | Pass =>
      LTerm.printls(
        eval([
          S(padding),
          B_bold(true),
          B_bg(green),
          S(" PASS "),
          E_bg,
          E_bold,
          S(" "),
          S(context.testName),
          E_fg,
        ]),
      )
    | Fail =>
      LTerm.printls(
        eval([
          S(padding),
          B_bold(true),
          B_bg(red),
          S(" FAIL "),
          E_bg,
          E_bold,
          S(" "),
          S(context.testName),
          E_fg,
        ]),
      )
    };
  Lwt.return();
};

let rec printContext = (context: testResultContext, level: int) => {
  let%lwt _ =
    context.testName == "__root" ?
      Lwt.return() : printTestResult(context, level);

  Lwt_list.iter_s(c => printContext(c, level + 1), context.children);
};

let printSummary = () => {
  let%lwt () = LTerm.printls(eval([S("\n")]));
  let%lwt () = printContext(rootContext, 0);
  let%lwt () = LTerm.printls(eval([S("\n")]));
  Lwt.return();
};
