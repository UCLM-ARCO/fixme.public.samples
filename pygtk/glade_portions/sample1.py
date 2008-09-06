#!/usr/bin/python
import gtk, gtk.glade

class Action:

    def __init__(self, n, name):
        self.glade = gtk.glade.XML('gui.glade', 'action')
        self.glade.signal_autoconnect(self)
        self.gui    = self.glade.get_widget('action')
        self.label  = self.glade.get_widget('label')
        self.button = self.glade.get_widget('button')

        self.label.set_text(str(n))
        self.button.set_label(name)

    def on_button_clicked(self, bt):
        print bt.get_label()


class Application:

    def __init__(self):
        self.glade = gtk.glade.XML('gui.glade', 'window')
        self.glade.signal_autoconnect(self)
        self.box   = self.glade.get_widget('box')
        self.entry = self.glade.get_widget('entry')
        self.n = 0

    def on_window_delete_event(self, event, data=None):
        gtk.main_quit()

    def on_add_clicked(self, bt):
        name = self.entry.get_text()
        if not name: return

        self.entry.set_text('')

        action = Action(self.n, name)
        self.n += 1
        self.box.pack_start(action.gui)

Application()
gtk.main()
