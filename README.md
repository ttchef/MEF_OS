# MEF_OS
---

For qemu testing get qemu with:
```sudo apt install qemu-system-arm```

Then run:
```./run_qemu.sh```

---
If you have a TTL wire you can use screen to see the output of UART (works only on real hardware)
```sudo screen /dev/ttyUSB0 115200```

# DEBUGGEN:
---
Dependency:
sudo apt install gdb-multiarch

1. run ./run_qemu_debug.sh
2. in a second terminal run ./gdb_start.sh
3. type command (in gdb): layout asm
4. type command (in gdb): target remote localhost:1234

then you can do normal gdb debugging

add breakpoints with: break main or break 0xXXXXXXX (memory address)
you can see values of variables with p (VARIABLE_NAME)
run the code till the next breakpoint with: continue

---
BTW the project requires specific hardware so dont even try to run it xD


NOTE that QUEMU doesnt work anymore for new commits (only for very old ones) because it doesnt 
support the features used in this os as emulation

