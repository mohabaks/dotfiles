#------------------------------------------------------------------------------
#                               LXD Resources 
#------------------------------------------------------------------------------

#
# Network
#

resource "lxd_network" "lxdbr0" {
  name = "lxdbr0"

  config = {
    "ipv4.address" = "none"
    "ipv4.dhcp" =  "false"
    "ipv4.firewall" =  "false"
    "ipv4.nat" = "false"
    "ipv6.address" = "none"
    "ipv6.dhcp" =  "false"
    "ipv6.firewall" =  "false"
    "ipv6.nat" = "false"
  }

  description = "LAN Network"
}

resource "lxd_network" "lxdbr1" {
  name = "lxdbr1"

  config = {
    "ipv4.address" = "none"
    "ipv4.dhcp" =  "false"
    "ipv4.firewall" =  "false"
    "ipv4.nat" = "false"
    "ipv6.address" = "none"
    "ipv6.dhcp" =  "false"
    "ipv6.firewall" =  "false"
    "ipv6.nat" = "false"
  }

  description = "PWN Network"
}


#
# Profiles
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

resource "lxd_profile" "lan" {
  name = "lan"
  
  description = "LAN Network"

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

resource "lxd_profile" "pwn" {
  name = "pwn"
  
  description = "PWN Network"

  device {
    name = "eth0"
    type = "nic"

    properties = {
      name = "eth0"
      nictype = "bridged"
      parent = "lxdbr1"
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
      path = "/home/var.USER/Downloads"
      source = "/home/var.USER/Downloads"
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
       path = "/home/var.USER/.fonts"
       source = "/home/var.USER/.fonts"
    }
  }

  device {
    name = "gtk-3"
    type = "disk"

    properties = {
       path = "/home/var.USER/.config/gtk-3.0"
       source = "/home/var.USER/.config/gtk-3.0"
    }
  }

  device {
    name = "gtkrc-2.0"
    type = "disk"

    properties = {
       path = "/home/var.USER/.gtkrc-2.0"
       source = "/home/var.USER/.gtkrc-2.0"
    }
  }

  device {
    name = "icons"
    type = "disk"

    properties = {
       path = "/home/var.USER/.icons"
       source = "/home/var.USER/.icons"
    }
  }

  device {
    name = "themes"
    type = "disk"

    properties = {
       path = "/home/var.USER/.themes"
       source = "/usr/share/themes"
    }
  }

  device {
    name = "trolltech"
    type = "disk"

    properties = {
       path = "/home/var.USER/config/Trolltech.conf"
       source = "/home/var.USER/config/Trolltech.conf"
    }
  }
}

resource "lxd_profile" "x11" {
  name = "x11"
  
  config = {
    "environment.DISPLAY" = ":0"
  }

  description = "X11 GUI"

  device {
    name = "X0"
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
    name = "gpu"
    type = "gpu"

    properties = {}
  }
}

resource "lxd_profile" "sys-net" {
  name = "sys-net"

  config = {
    "limits.cpu" =  "1"
    "limits.memory" = "512MiB"
    "security.privileged" = "true"
  }

  description = "System Network"

  device {
    name = "eth0"
    type = "nic"

    properties = {
      name = "eth0"
      parent = "lxdbr0"
      nictype = "bridged"
    }
  }

  device {
    name = "eth1"
    type = "nic"

    properties = {
      name = "eth1"
      parent = "lxdbr1"
      nictype = "bridged"
    }
  }

  device {
    name = "wlan0"
    type = "nic"

    properties = {
      name = "wlan0"
      parent = "wlan0"
      nictype = "physical"
    }
  }
}

#
# Containers
#

resource "lxd_instance" "sys-net" {
  name = "sys-net"
  image = "images:alpine/edge"
  type = "container"
  profiles = ["default", "sys-net"]
}

#
# Virtaul Machines
#

# resource "lxd_container" "whonix-gateway" {
#   name = "whonix-gateway"
#   image = "whonix-gateway"
#   type = "virtual-machine"
#   profiles = ["default", "whonix-gateway"]
# }