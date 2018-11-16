open Types;

let test = (name: string, testFunction: testFunction) => {

    /* If not running, queue up test */

    /* If running, actually run the test */
    TestCollector.collectTest(name, testFunction);
};


let run = () => {
    /* For each 'queued' test, call the in-aplty named `collectTest` */
    /* How do we wait for all Lwt promises? */

    Lwt_main.run(Lwt.return());
};

print_endline ("Hello, world");
