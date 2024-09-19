Installation
-----------

For `polybar` , `i3-gaps` and `rofi` installation read [this](https://github.com/fepitre/qubes-rofi/issues/1#issuecomment-667303259).

> you should not install packages in `dom0` unless you know what your doing.

For the current (R4.2) setup the following are packages installed to have a working bspwm, i3lock, polybar, dunst, rofi and dmenu.

Using `untrusted` qube download the zip archive for this [repo](https://github.com/mohabaks/dotfiles)

From `dom0` install required packages and transfer the downloaded `dotfiles-master.zip` from `untrusted` qube and copy required files.

```
$ sudo qubes-dom0-update xss-lock i3lock polybar rofi dmenu lxappearance scrot dunst bspwm sxhkd picom
$ qvm-run --pass-io untrusted 'cat /home/user/Downloads/dotfiles-master.zip' > dotfiles-master.zip
$ unzip dotfiles-master.zip
$ cp -r dotfiles-master/Qubes-os/polybar $HOME/.config
$ cp -r dotfiles-master/Qubes-os/rofi $HOME/.config
$ cp -r dotfiles-master/Qubes-os/bspwm $HOME/.config
$ cp -r dotfiles-master/Qubes-os/sxhkd $HOME/.config
$ cp -r dotfiles-master/Qubes-os/picom $HOME/.config
$ cp -r dotfiles-master/Qubes-os/dunst $HOME/.config
$ cp -r dotfiles-master/Qubes-os/.xinitrc $HOME/
$ sudo cp dotfiles-master/Qubes-os/i3-settings-qubes/qubes-i3-sensible-terminal /usr/bin/sensible-terminal
```

Screenshots
-----------
### Current

`bspwm`
![bspwm](https://imgur.com/vjXsacH.png)

`dwm`
[dwm](https://i.imgur.com/fv5zxNK.png)

### Previous
`Laptop (On)` `Dual Monitors (Off)`

![minimal](https://i.redd.it/95c11eibqpo61.jpg)


`Laptop (Off)` `Dual Monitors (On)`

![quarantine](https://i.redd.it/63p44yk5xkn41.png)

![dex](https://i.redd.it/m4hg5n7dibb61.png)
