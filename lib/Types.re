/*
 * TestCollector
 */

type testFunction = unit => unit;

type testResult =
  | Pass
  | Fail(exn);

type expectationFailedProps = {
  actualValue: string,
  callstack: string,
  expectedValue: string,
};

exception ExpectationFailed(expectationFailedProps);
