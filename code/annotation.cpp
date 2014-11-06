void fn() {
    yield;
}
await stackfull[] fn(); // execute fn() in a stackfull coroutine
await fn();             // execute fn() in a stackless coroutine
