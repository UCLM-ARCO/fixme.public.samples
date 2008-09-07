#!/usr/bin/python
import sys, gtk
sys.path.append('gladeutil')
import gladeutil

class Action(object):

    __metaclass__ = gladeutil.Widget
    WIDGET = ('gui.glade', 'action')

    def __init__(self, n, name):
        self.wg_label.set_text(str(n))
        self.wg_button.set_label(name)

    def on_button_clicked(self, bt):
        print bt.get_label()


class Application(gladeutil.Wrapper):

    def __init__(self):
        gladeutil.Wrapper.__init__(self, 'gui.glade', 'window')
        self.n = 0

    def on_window_delete_event(self, event, data=None):
        gtk.main_quit()

    def on_add_clicked(self, bt):
        name = self.wg_entry.get_text()
        if not name: return

        self.wg_entry.set_text('')

        action = Action(self.n, name)
        action.show_all()
        print action.get_children()

        self.n += 1
        self.wg_box.pack_start(action)


Application()
gtk.main()
