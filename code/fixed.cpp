void fn() {
    yield;
}
// use 16kb large fixed size stack for stackfull coroutine
await stackfull[fixed(16*1024)] fn();
