/*
 * TestCollector
 */

type testFunction = unit => unit;

type testResult =
  | Pass
  | Fail(exn);
