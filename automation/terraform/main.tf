#------------------------------------------------------------------------------
#                               Providers
#------------------------------------------------------------------------------

terraform{
  required_providers{
    lxd = {
      source = "terraform-lxd/lxd"
    }
   docker = {
     source = "kreuzwerker/docker"
   }
  }
}

provider "lxd"{
}

provider "docker"{
}


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
    "ipv6.address" =  "none"
    "ipv6.dhcp" =  "false"
    "ipv6.firewall" =  "false"
    "ipv6.nat" = "false"
  }

  description = "MAN Network"
}

resource "lxd_network" "lxdbr2" {
  name = "lxdbr2"

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

resource "lxd_network" "lxdbr3" {
  name = "lxdbr3"

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

  description = "WGI Network"
}

resource "lxd_network" "lxdbr4" {
  name = "lxdbr4"

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

  description = "WGE Network"
}


#
# Profiles
#

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
    name = "eth2"
    type = "nic"

    properties = {
      name = "eth2"
      parent = "lxdbr2"
      nictype = "bridged"
    }
  }

  device {
    name = "eth3"
    type = "nic"

    properties = {
      name = "eth3"
      parent = "lxdbr3"
      nictype = "bridged"
    }
  }

  device {
    name = "eth4"
    type = "nic"

    properties = {
      name = "eth4"
      parent = "lxdbr4"
      nictype = "bridged"
    }
  }

  device {
    name = "wlan0"
    type = "nic"

    properties = {
      name = "wlan0"
      parent = "wlp4s0"
      nictype = "physical"
    }
  }
}

resource "lxd_profile" "audio" {
  name = "audio"

  config = {
    "environment.PULSE_SERVER" = "unix:/home/user/pulse-socket"
  }

  description = "Pulseaudio Server"

  device {
    name = "Socket"
    type = "proxy"

    properties = {
      bind = "container"
      connect = "unix:/run/user/1000/pulse/native"
      gid = "1000"
      listen = "unix:/home/user/pulse-socket"
      mode =  "0777"
      "security.gid" = "1000"
      "security.uid" = "1000"
      uid =  "1000"
    }
  }
}

resource "lxd_profile" "default" {
  name = "default"

  description = "Default LXD"

  device {
    name = "root"
    type = "disk"

    properties = {
      path = "/"
      pool = "zroot"
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
      path = "/home/user/Downloads"
      source = "/home/bytebandit/Downloads"
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
       path = "/home/user/.fonts"
       source = "/home/bytebandit/.fonts"
    }
  }

  device {
    name = "gtk-3"
    type = "disk"

    properties = {
       path = "/home/user/.config/gtk-3.0"
       source = "/home/bytebandit/.config/gtk-3.0"
    }
  }

  device {
    name = "gtkrc-2.0"
    type = "disk"

    properties = {
       path = "/home/user/.gtkrc-2.0"
       source = "/home/bytebandit/.gtkrc-2.0"
    }
  }

  device {
    name = "icons"
    type = "disk"

    properties = {
       path = "/home/user/.icons"
       source = "/home/bytebandit/.icons"
    }
  }

  device {
    name = "themes"
    type = "disk"

    properties = {
       path = "/home/user/.themes"
       source = "/usr/share/themes"
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
      parent = "lxdbr2"
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

  device {
    name = "eth1"
    type = "nic"

    properties = {
      name = "eth1"
      nictype = "bridged"
      parent = "lxdbr3"
    }
  }
}

resource "lxd_profile" "whonix-gateway" {
  name = "whonix-gateway"
  
  description = "Whonix-Gateway"

  device {
    name = "eth0"
    type = "nic"

    properties = {
      name = "eth0"
      nictype = "bridged"
      parent = "lxdbr4"
    }
  }

  device {
    name = "eth1"
    type = "nic"

    properties = {
      name = "eth1"
      nictype = "bridged"
      parent = "lxdbr3"
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

#
# Containers
#

resource "lxd_container" "sys-net" {
  name = "sys-net"
  image = "images:alpine/edge"
  type = "container"
  profiles = ["default", "sys-net"]
}

resource "lxd_container" "chosa" {
  name = "chosa"
  image = "images:archlinux"
  type = "container"
  profiles = ["default", "ricer", "dropbox", "x11", "lan", "audio"]

  limits = {
    cpu = "2"
    memory = "4GiB"
  }
}

resource "lxd_container" "sosha" {
  name = "sosha"
  image = "images:ubuntu/jammy"
  type = "container"
  profiles = ["default", "lan", "x11", "audio", "ricer", "dropbox"]

  limits = {
    cpu = "1"
    memory = "2GiB"
  }
}

#
# Virtaul Machines
#

resource "lxd_container" "whonix-gateway" {
  name = "whonix-gateway"
  image = "whonix-gateway"
  type = "virtual-machine"
  profiles = ["default", "whonix-gateway"]
}


#------------------------------------------------------------------------------
#                               Docker Resources 
#------------------------------------------------------------------------------

#
# Networks
#

resource "docker_network" "LAN" {
    name         = "LAN"
    attachable   = false
    driver       = "ipvlan"
    ingress      = false
    internal     = false
    ipam_driver  = "default"
    ipam_options = {}
    ipv6         = false

    options      = {
        "ipvlan_mode" = "l2"
        "parent"      = "lxdbr0"
    }

    ipam_config {
        aux_address = {}
        gateway     = "10.238.20.1"
        ip_range    = "10.238.20.50/28"
        subnet      = "10.238.20.0/24"
    }
}

resource "docker_network" "PWN" {
    name         = "PWN"
    attachable   = false
    driver       = "ipvlan"
    ingress      = false
    internal     = false
    ipam_driver  = "default"
    ipam_options = {}
    ipv6         = false

    options      = {
        "ipvlan_mode" = "l2"
        "parent"      = "lxdbr2"
    }

    ipam_config {
        aux_address = {}
        gateway     = "10.238.50.1"
        ip_range    = "10.238.50.50/28"
        subnet      = "10.238.50.0/24"
    }
}

resource "docker_network" "WGI" {
    name         = "WGI"
    attachable   = false
    driver       = "ipvlan"
    ingress      = false
    internal     = false
    ipam_driver  = "default"
    ipam_options = {}
    ipv6         = false

    options      = {
        "ipvlan_mode" = "l2"
        "parent"      = "lxdbr3"
    }

    ipam_config {
        aux_address = {}
        gateway     = "10.152.152.10"
        ip_range    = "10.152.152.20/28"
        subnet      = "10.152.152.0/18"
    }
}
