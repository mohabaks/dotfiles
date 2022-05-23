#!/usr/bin/env bash
# Uses castnow and provides embedded subtitles.

vtt="$(mktemp).vtt"
ffmpeg -i "$1" -f webvtt -y "$vtt" 2>/dev/null
caffeinate -is castnow "$@" --subtitles "$vtt" \
  --subtitle-color '#FFFFFFFF'
rm "$vtt"
