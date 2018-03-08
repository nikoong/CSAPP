# CSAPP_lab

 my solutions for CS:APP3e's labs.

* **Because versions of Unix are different,there may be some errors when you run some datalab and archlab. **
* **Here are solutions.**


####datalab:

**error1:**  
"skipping incompatible /usr/lib/gcc/x86_64-linux-gnu/4.7/libgcc.a when searching for -lgcc"
or	"skipping incompatible /usr/lib/gcc/x86_64-linux-gnu/4.7/libgcc_s.so when searching for -lgcc_s"
**solution:** 
sudo apt-get install gcc-4.7-multilib


**error2:** 
"/usr/include/features.h:364:25: fatal error: sys/cdefs.h: No such file or directory"
**solution:** 
sudo apt-get install libc6-dev-i386


####archlab

"ssim.c:20:16: fatal error: tk.h: No such file or directory"
"/usr/bin/ld: cannot find -ltk"
"/usr/bin/ld: cannot find -ltcl"
*solution:* sudo apt-get install tk-dev tcl-dev




___

**remark:**

*if you see something about "DBB checker",forget it. That is a code-testing tool, but we don't have it.*