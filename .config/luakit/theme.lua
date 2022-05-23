--------------------------
-- Default luakit theme --
--------------------------

local theme = {}

-- Default settings
theme.font = "11px Gohu GohuFont"
theme.fg   = "#a8a8a8"
theme.bg   = "#020202"

-- Genaral colours
theme.success_fg = "#a8a8a8"
theme.loaded_fg  = "#a8a8a8"
theme.error_fg = "#00a8a8"
theme.error_bg = "#020202"

-- Warning colours
theme.warning_fg = "#8e8e8e"
theme.warning_bg = "#a8a8a8"

-- Notification colours
theme.notif_fg = "#a8a8a8"
theme.notif_bg = "#020202"

-- Menu colours
theme.menu_fg                   = "#a8a8a8"
theme.menu_bg                   = "#080808"
theme.menu_selected_fg          = "#f7f7f7"
theme.menu_selected_bg          = "#00a8a8"
theme.menu_title_bg             = "#020202"
theme.menu_primary_title_fg     = "#686868"
theme.menu_secondary_title_fg   = "#8e8e8e"

theme.menu_disabled_fg = "#3d4550"
theme.menu_disabled_bg = theme.menu_bg
theme.menu_enabled_fg = theme.menu_fg
theme.menu_enabled_bg = theme.menu_bg
theme.menu_active_fg =  "#686868"
theme.menu_active_bg =  theme.menu_bg

-- Proxy manager
theme.proxy_active_menu_fg      = '#f7f7f7'
theme.proxy_active_menu_bg      = '#00a8a8'
theme.proxy_inactive_menu_fg    = '#3d4550'
theme.proxy_inactive_menu_bg    = '#080808'

-- Statusbar specific
theme.sbar_fg         = "#a8a8a8"
theme.sbar_bg         = "#080808"

-- Downloadbar specific
theme.dbar_fg         = "#a8a8a8"
theme.dbar_bg         = "#00a8a8"
theme.dbar_error_fg   = "#00a8a8"

-- Input bar specific
theme.ibar_fg           = "#a8a8a8"
theme.ibar_bg           = "#020202"

-- Tab label
theme.tab_fg            = "#a8a8a8"
theme.tab_bg            = "#020202"
theme.tab_hover_bg      = "#00a8a8"
theme.tab_ntheme        = "#a8a8a8"
theme.selected_fg       = "#a8a8a8"
theme.selected_bg       = "#080808"
theme.selected_ntheme   = "#a8a8a8"
theme.loading_fg        = "#a8a8a8"
theme.loading_bg        = "#020202"

theme.selected_private_tab_bg = "#3d295b"
theme.private_tab_bg    = "#22254a"

-- Trusted/untrusted ssl colours
theme.trust_fg          = "#00a8a8"
theme.notrust_fg        = "#3d4550"

-- General colour pairings
theme.ok = { fg = "#a8a8a8", bg = "#020202" }
theme.warn = { fg = "#5d7b5c", bg = "#020202" }
theme.error = { fg = "#00a8a8", bg = "#020202" }

return theme

-- vim: et:sw=4:ts=8:sts=4:tw=80
