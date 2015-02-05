#!/bin/sh
touch NEWS README AUTHORS ChangeLog
autoreconf --force --install -I config -I m4
