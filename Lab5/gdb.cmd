target extended-remote localhost:3333
set arm abi APCS
monitor reset halt
file ./gcc/timers.axf
load
