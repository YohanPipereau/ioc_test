
# Description

In https://lwn.net/Articles/48354/ , it is said that ioctl has a size limit of 2^14 Bytes. This appeared with Arnd Bergmann "use size_t for the broken ioctl numbers" patch.
Since then, this size check has been removed and this aims at showing that there is no more limit.

# How to use

Compile:
> cd kern; make 

> cd ..

> cd user; make

Run as root:
> insmod kern/ioc.ko

> ./user/test
