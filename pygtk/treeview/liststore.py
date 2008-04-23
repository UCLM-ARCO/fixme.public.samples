#!/usr/bin/env python

import pygtk
pygtk.require('2.0')
import gtk

class BasicTreeViewExample:

    # Cierra la ventana y el programa
    def delete_event(self, widget, event, data=None):
        gtk.main_quit()


    def __init__(self):
        # Crea una ventana nueva
        self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        self.window.set_size_request(200, 200)
        self.window.connect("delete_event", self.delete_event)

        # Crea un ListStore con una única columna, de tipo cadena
        self.store = gtk.ListStore(str)

        for i in range(4):
            self.store.append(['element %d' % i])

        # Crear una vista para el modelo (self.store)
        self.treeview = gtk.TreeView(self.store)

        # Crea el TreeViewColumn 
        self.tvcolumn = gtk.TreeViewColumn('Column 0')

        # Añadimos tvcolumn al treeview
        self.treeview.append_column(self.tvcolumn)

        # Crea un CellRendererText para representar los datos ('dibujarlos')
        self.cell = gtk.CellRendererText()

        # añade el cellrenderer al tvcolumn
        self.tvcolumn.pack_start(self.cell, True)

        # dice que el cellrenderer tiene que representar la columna 0 del
        # modelo como 'texto'
        self.tvcolumn.add_attribute(self.cell, 'text', 0)

        self.window.add(self.treeview)

        self.window.show_all()


if __name__ == "__main__":
    tvexample = BasicTreeViewExample()
    gtk.main()

