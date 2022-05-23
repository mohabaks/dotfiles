# dwmblocks
Modular status bar for dwm written in c.
# usage
To use dwmblocks first run 'make' and then install it with 'sudo make install'.
After that you can put dwmblocks in your xinitrc or other startup script to have it start with dwm.
# modifying blocks
The statusbar is made from text output from commandline programs.
Blocks are added and removed by editing the blocks.h header file.
By default the blocks.h header file is created the first time you run make which copies the default config from blocks.def.h.
This is so you can edit your status bar commands and they will not get overwritten in a future update.
# patches
Here are some patches to dwmblocks that add features that I either don't want to merge in, or that require a dwm patch to work.
I do not maintain these but I will take pull requests to update them.
<br>
<a href=https://gist.github.com/IGeraGera/e4a5583b91b3eec2e81fdceb44dea717>dwmblocks-statuscmd-b6b0be4.diff</a>
