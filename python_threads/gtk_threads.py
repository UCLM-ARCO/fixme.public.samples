#!/usr/bin/env python

import time, random
import thread
import gtk, gobject


def inc(sb):
    i = 0
    while 1:
        #gtk.gdk.threads_enter()
        #sb.set_value(i)
        #gtk.gdk.threads_leave()
        gobject.idle_add(sb.set_value, i)
        i += 1
        time.sleep(random.random()/2)


class ThreadExample:

    # Cierra la ventana y el programa
    def delete_event(self, widget, event, data=None):
        gtk.main_quit()


    def __init__(self):
        # Crea una ventana nueva
        self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        self.window.set_size_request(850, 500)
        self.window.connect("delete_event", self.delete_event)

        t = gtk.Table(20, 10)
        self.window.add(t)

        for i in range(20):
            for j in range(10):
                adj = gtk.Adjustment(1.0, 1.0, 1000000.0, 1.0, 5.0, 0.0)
                sb = gtk.SpinButton(adj, 0, 0)
                t.attach(sb, j, j+1, i, i+1)
                thread.start_new_thread(inc, (sb,))


        self.window.show_all()


if __name__ == "__main__":
    example = ThreadExample()
    gtk.gdk.threads_init()
    gtk.gdk.threads_enter()
    gtk.main()
    gtk.gdk.threads_leave()
