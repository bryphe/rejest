/*
 * TestCollector
 */

type testFunction = unit => unit;

type testContext = {
  name: string,
  level: int,
  test: testFunction,
  parent: option(testContext),
  mutable children: list(testContext),
};

let rootContext: testContext = {
  name: "__root",
  level: 0,
  test: () => (),
  parent: None,
  children: [],
};

let currentContext: ref(testContext) = ref(rootContext);

let runTest = (testFunction: testFunction, context: testContext) => {
  /* Run all beforeEach */
  TestReporter.startTest(context.name);
  testFunction();
  TestReporter.endTest(context.name, Pass);
  /* Run all afterEach */
};

let collectTest = (testName: string, testFunction: testFunction) => {
  let previousContext = currentContext^;

  let newContext: testContext = {
    name: testName,
    test: testFunction,
    level: currentContext^.level + 1,
    parent: Some(currentContext^),
    children: [],
  };

  switch (currentContext^.parent) {
  | Some(p) => p.children = List.append(p.children, [newContext])
  | _ => ()
  };

  currentContext := newContext;

  /* Run current test function */

  runTest(testFunction, newContext);

  currentContext := previousContext;
};
