# CSAPP_lab

 Here are my solutions for CS:APP3e's labs.

*Because of different versions of Unix , there may be some errors when you run some datalab and archlab.*
*These Tips may help you*



### For datalab:

**error1:**  
"skipping incompatible /usr/lib/gcc/x86_64-linux-gnu/4.7/libgcc.a when searching for -lgcc"
or	"skipping incompatible /usr/lib/gcc/x86_64-linux-gnu/4.7/libgcc_s.so when searching for -lgcc_s"
**Tip:** 
sudo apt-get install gcc-4.7-multilib

**error2:** 
"/usr/include/features.h:364:25: fatal error: sys/cdefs.h: No such file or directory"
**Tip:** 
sudo apt-get install libc6-dev-i386


#### For archlab

**error1:**
"ssim.c:20:16: fatal error: tk.h: No such file or directory"
"/usr/bin/ld: cannot find -ltk"
"/usr/bin/ld: cannot find -ltcl"
**Tip:** 
sudo apt-get install tk-dev tcl-dev




___

**remark:**

*if you see something about "DBB checker", please forget it. That is a code-testing tool, but we don't have it.*
