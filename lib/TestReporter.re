/*
 * TestReporter
 */

open Types;

let startTest = (testName: string) => {
    print_endline ("start test: " ++ testName);
};

let endTest = (testName: string, result: testResult) => {
    print_endline ("end test: " ++ testName);
};

let printSummary = () => {
    print_endline ("TODO: Summary");
};
