#!/usr/bin/env bash
QUERY=$(echo '' | dmenu -p "Search:")

if [ -n "$QUERY" ]; then
    firefox "http://127.0.0.1:8888/search?q=${QUERY}"
fi
