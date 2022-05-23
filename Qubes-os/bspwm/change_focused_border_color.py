#!/usr/bin/env python2
# -*- coding: utf-8 -*-
# pylint: disable=C0103
# vim:set shiftwidth=4 softtabstop=4 expandtab:
'''
Module: change_focused_border_color

Created: 15.Apr.2016
Created by: Morten Hersson, <mhersson@gmail.com>

Description:
    Listens for property change events and checks if active/focused
    window has changed. Then reads the _QUBES_LABEL property and
    sets the focused border color accordingly

Copyright (c) 2016 Morten Hersson
'''
import xpybutil
import xpybutil.event as event
import xpybutil.ewmh as ewmh
import xpybutil.util as util
import xpybutil.window as window
from subprocess import call

COLORS = {0: "#FFFFFF",
          1: "#FF0000",
          2: "#FF5F00",
          3: "#FFFF00",
          4: "#01DF01",
          5: "#848482",
          6: "#2E64FE",
          7: "#7D1B7E",
          8: "#848484"}

current_qlabel = None

def set_border_color():
    """
    Get active window and set border color
    if the _QUBES_LABEL value has changed
    """
    global current_qlabel

    qlabel = 0

    activewin = ewmh.get_active_window().reply()
    if not activewin:
        return

    try:
        prop = util.PropertyCookie(util.get_property(
            activewin, '_QUBES_LABEL')).reply()
    except:
        return
    if prop is not None:
        qlabel = ord(prop)

    if qlabel != current_qlabel:
        color = COLORS.get(qlabel)
        call(["bspc", "config", "focused_border_color", color])
        current_qlabel = qlabel

    xpybutil.conn.flush()


def cb_property_notify(e):
    """
    Event callback for property change.
    Checks that the _NET_ACTIVE_WINDOW atom is the property that has changed.
    Then set border color
    """
    aname = util.get_atom_name(e.atom)
    if aname == '_NET_ACTIVE_WINDOW':
        set_border_color()


if __name__ == '__main__':
    window.listen(xpybutil.root, 'PropertyChange')
    event.connect('PropertyNotify', xpybutil.root, cb_property_notify)

    event.main()
