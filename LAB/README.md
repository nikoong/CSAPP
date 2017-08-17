# CSAPP_lab

This is CS:APP3e's lab and my solution.


**There may be some errors when you run the code, because of the different versions of Unix.Here are some solutions.**


**error1:**  "skipping incompatible /usr/lib/gcc/x86_64-linux-gnu/4.7/libgcc.a when searching for -lgcc"
or	"skipping incompatible /usr/lib/gcc/x86_64-linux-gnu/4.7/libgcc_s.so when searching for -lgcc_s"


**solution:** sudo apt-get install gcc-4.7-multilib


**error2:**  "/usr/include/features.h:364:25: fatal error: sys/cdefs.h: No such file or directory"

**solution:** sudo apt-get install libc6-dev-i386

___

**remark:**

*if you see something about "DBB checker",forget it.That is a code-testing tool, but we don't have it.*