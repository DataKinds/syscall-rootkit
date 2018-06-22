# SYSCALL-ROOTKIT

Ok, maybe it's not a catchy name, haha. This is a simple proof-of-concept kernel module which hooks into a few Linux system calls and acts as a bare-bones "rootkit". It's not intended to be malicious! Use at your own risk, on your own machine, in your own time.

## USING THIS SOFTWARE

1. Make sure you have a sane build environment and updated headers for your Linux distro.
2. Run `make` - this will preprocess and build the rootkit, saving it to rk.ko.
3. `sudo insmod rk.ko`
4. Play with it!
5. `sudo rmmod rk.ko`
6. `make clean` to remove all the temporary files created by the building process.

## TODO

- Make it actually _do_ something with the data collected.
- Filter the data collected from read() to read() from stdin. (Think: sudo passwords, etc).

## LICENSE

GPL
