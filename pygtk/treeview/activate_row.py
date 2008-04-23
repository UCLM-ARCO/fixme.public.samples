#!/usr/bin/env python

import pygtk
pygtk.require('2.0')
import gtk

class BasicTreeViewExample:

    def __init__(self):
        # Crea una ventana nueva
        self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        self.window.connect("delete_event", self.delete_event)

        # Crea un ListStore con dos columnas, de tipo cadena
        self.store = gtk.ListStore(int, str, str)

        for i in range(4):
            self.store.append([i, 'hello', 'element %d' % i])

        # Crear una vista para el modelo (self.store)
        self.treeview = gtk.TreeView(self.store)
        
        cell = gtk.CellRendererText()
        names = ['number', 'name']
        columns = [0, 2]

        for i in range(2):
            tvcolumn = gtk.TreeViewColumn(names[i], cell, text=columns[i])
            self.treeview.append_column(tvcolumn)
        
        self.treeview.connect('row-activated', self.on_row_activated)

        self.window.add(self.treeview)

        self.window.show_all()


    # Cierra la ventana y el programa
    def delete_event(self, widget, event, data=None):
        gtk.main_quit()


    def on_row_activated(self, treeview, path, tvcolumn, user_data=None):
        print "Activado '%s'" % self.store[path][2]


if __name__ == "__main__":
    tvexample = BasicTreeViewExample()
    gtk.main()

