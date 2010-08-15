#!/usr/bin/python
# -*- mode:python; coding:utf-8 -*-

import sys
import pyinotify as inotify

class EventHandler(inotify.ProcessEvent):
    def process_IN_CREATE(self, event):
        print "Create:", event.pathname

    def process_IN_DELETE(self, event):
        print "Delete:", event.pathname

    def process_IN_MODIFY(self, event):
        print "Modify:", event.pathname


wm = inotify.WatchManager()
wm.add_watch(sys.argv[1],
             inotify.IN_MODIFY | inotify.IN_CREATE | inotify.IN_DELETE,
             rec=True)

notifier = inotify.Notifier(wm, EventHandler())
notifier.loop()
