open Types;

let expect = Expect.expect;

let isRunning = ref(false);

type test = {
    name: string,
    testFunction: testFunction,
};

let tests: ref(list(test)) = ref([])

let test = (name: string, testFunction: testFunction) => {

    /* If not running, queue up test */

    if (!isRunning^) {
        let newTest: test = {name, testFunction};
        tests := List.append(tests^, [newTest]);
    } else {
        /* If running, actually run the test */
        TestCollector.collectTest(name, testFunction);
    }
};

open LTerm_style;
open LTerm_text;

let run = () => {
    /* For each 'queued' test, call the in-aplty named `collectTest` */
    /* How do we wait for all Lwt promises? */

    let runTests = () => {
        isRunning := true;
        List.iter((t) => {
            TestCollector.collectTest(t.name, t.testFunction);
        }, tests^)
        isRunning := false;
        LTerm.printls(eval([B_fg(green), S("PASS"), E_fg, S(" "), S("World!"), E_fg]));
    };

    Lwt_main.run(runTests());
};

print_endline ("Hello, world");
