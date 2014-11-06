void fn() {
    yield;
}
// use segmented stack (grows on demand)
// with inital size of 16kb for stackfull coroutine
await stackfull[segmented(16*1024)] fn();
