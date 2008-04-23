#!/usr/bin/python

import pygtk
pygtk.require('2.0')
import gtk, gtk.glade

class Programa:

   def __init__(self):
      self.glade = gtk.glade.XML("hola.glade2")
      self.glade.signal_autoconnect(self)

   
   def on_window_hola_delete_event(self, event, data=None):
      gtk.main_quit()
      

   def on_button_hola_clicked(self, widget):
      print "hola mundos!"

   

if __name__ == '__main__':
   p = Programa()
   gtk.main()
