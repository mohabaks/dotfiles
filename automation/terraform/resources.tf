#
# Network
#

resource "lxd_network" "lxdbr0" {
  name = "lxdbr0"
  description = "PWN Network"

  config = {
    "ipv4.address" = "auto"
    "ipv4.dhcp" =  true  
    "ipv4.firewall" =  true
    "ipv4.nat" =  true 
    "ipv6.address" = "none"
    "ipv6.dhcp" =  false
    "ipv6.firewall" =  false
  }
}

# resource "lxd_network" "lxdbr1" {
#   name = "lxdbr1"

#   config = {
#     "ipv4.address" = "none"
#     "ipv4.dhcp" =  "false"
#     "ipv4.firewall" =  "false"
#     "ipv4.nat" = "false"
#     "ipv6.address" = "none"
#     "ipv6.dhcp" =  "false"
#     "ipv6.firewall" =  "false"
#     "ipv6.nat" = "false"
#   }

#   description = "MLW Network"
# }


#
# Profile
#

resource "lxd_profile" "default" {
  name = "default"

  description = "Default LXD"

  device {
    name = "root"
    type = "disk"

    properties = {
      path = "/"
      pool = "default"
    }
  }
}

resource "lxd_profile" "pwn" {
  name = "pwn"
  
  description = "PWN Network"

  device {
    name = "eth0"
    type = "nic"

    properties = {
      name = "eth0"
      nictype = "bridged"
      parent = "lxdbr0"
    }
  }
}

resource "lxd_profile" "dropbox" {
  name = "dropbox"

  description = "Shared Folders"

  device {
    name = "downloads"
    type = "disk"

    properties = {
      path = "/home/${var.USER}/Downloads"
      source = "/home/${var.USER}/Downloads"
      shift = "true"
    }
}
}

resource "lxd_profile" "tools" {
  name = "tools"

  description = "Additional Tools"

  device {
    name = "tools"
    type = "disk"

    properties = {
      path = "/opt/tools"
      source = "/opt/tools"
      shift = "true"
    }
}
}

resource "lxd_profile" "ricer" {
  name = "ricer"

  description = "Uniform Look for Qt/GTK Apps"

  device {
    name = "fonts"
    type = "disk"

    properties = {
       path = "/home/${var.USER}/.fonts"
       source = "/home/${var.USER}/.fonts"
       shift = "true"
    }
  }

  device {
    name = "gtk-3"
    type = "disk"

    properties = {
       path = "/home/${var.USER}/.config/gtk-3.0"
       source = "/home/${var.USER}/.config/gtk-3.0"
       shift = "true"
       shift = "true"
    }
  }

  device {
    name = "gtk-2.0"
    type = "disk"

    properties = {
       path = "/home/${var.USER}/.config/gtk-2.0"
       source = "/home/${var.USER}/.config/gtk-2.0"
       shift = "true"
       shift = "true"
    }
  }

  device {
    name = "xsettingsd"
    type = "disk"

    properties = {
       path = "/home/${var.USER}/.config/xsettingsd"
       source = "/home/${var.USER}/.config/xsettingsd"
       shift = "true"
       shift = "true"
    }
  }

  device {
    name = "nwg-look"
    type = "disk"

    properties = {
       path = "/home/${var.USER}/.config/nwg-look"
       source = "/home/${var.USER}/.config/nwg-look"
       shift = "true"
       shift = "true"
    }
  }

  device {
    name = "gtkrc-2.0"
    type = "disk"

    properties = {
       path = "/home/${var.USER}/.gtkrc-2.0"
       source = "/home/${var.USER}/.gtkrc-2.0"
       shift = "true"
    }
  }

  device {
    name = "icons"
    type = "disk"

    properties = {
       path = "/home/${var.USER}/.icons"
       source = "/home/${var.USER}/.icons"
       shift = "true"
    }
  }

  device {
    name = "themes"
    type = "disk"

    properties = {
       path = "/home/${var.USER}/.themes"
       source = "/usr/share/themes"
       shift = "true"
    }
  }

  device {
    name = "trolltech"
    type = "disk"

    properties = {
       path = "/home/${var.USER}/.config/Trolltech.conf"
       source = "/home/${var.USER}/.config/Trolltech.conf"
       shift = "true"
    }
  }
}

resource "lxd_profile" "gui" {
  name = "gui"
  
  config = {
    "environment.DISPLAY" = ":0"
  }

  description = "Wayland/Xorg applications"

  device {
    name = "Xsocket"
    type = "proxy"

    properties = {
       bind = "container"
       connect = "unix:@/tmp/.X11-unix/X0"
       listen = "unix:@/tmp/.X11-unix/X0"
       "security.gid" = "1000"
       "security.uid" = "1000"
    }
  }

  device {
    name = "Waylandsocket"
    type = "proxy"

    properties = {
      bind = "container"
      connect = "unix:/run/user/1000/wayland-1"
      listen =  "unix:/mnt/wayland/wayland-0"
      uid = "1000"
      gid = "1000"
      "security.gid" = "1000"
      "security.uid" = "1000"
      mode = "0777"
    }
  }

  device {
    name = "mygpu"
    type = "gpu"

    properties = {}
  }
}

#
# Storage
#

resource "lxd_storage_pool" "docker" {
  name   = "docker"
  driver = "btrfs"
  config = {
    source = "/var/lib/lxd/disks/docker.img"
    size = "10GiB"
  }
}

#
# Volume
#

resource "lxd_volume" "blackarch" {
  name = "blackarch"
  pool = "${lxd_storage_pool.docker.name}"
}

#
# Container
#

resource "lxd_instance" "blackarch" {
  name = "blackarch"
  image = "images:archlinux"
  type = "container"
  profiles = ["default", "pwn", "gui", "ricer", "dropbox"]

  config = {
     "security.nesting" = true 
     "security.syscalls.intercept.mknod" = true 
     "security.syscalls.intercept.setxattr" = true
  }

  device {
    name = "docker"
    type = "disk"

    properties = {
      path = "/var/lib/docker"
      source = "${lxd_volume.blackarch.name}"
      pool = "${lxd_storage_pool.docker.name}"
    }
  }

  limits = {
    cpu = 4
    memory = "8GiB"
  }
}

#
# Virtaul Machine
#

# resource "lxd_container" "whonix-gateway" {
#   name = "whonix-gateway"
#   image = "whonix-gateway"
#   type = "virtual-machine"
#   profiles = ["default", "whonix-gateway"]
# }