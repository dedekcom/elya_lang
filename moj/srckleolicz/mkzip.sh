#!/bin/bash

zip -r elibs.zip libs/ advlibs/ gameobjs/ templates/
if [ $# -gt 0 ];then
	scp elibs.zip dedek@muza.org:./public_html/
fi
