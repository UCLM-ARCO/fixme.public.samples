#!/usr/bin/python

import gtk
import gladeutil

class Panel:

    __metaclass__ = gladeutil.Widget
    WIDGET = ('gui.glade', 'vbox1')

    def __init__(self, pname):
        print "Panel.__init__"
        self.pname = pname

    def hello(self):
        return 'hello!'


p = Panel('side')

print p
print p.__class__
print p.__class__.__bases__
print

# Panel methods
print 'p.pname:     ', p.pname
print 'p.hello():   ', p.hello()

# widget methods
print 'p.name:      ', p.name
print 'p.is_focus():', p.is_focus()
print 'p.visble',      p.get_property('visible')

# gladewrapped
print p.wg_entry
print p.glade

print isinstance(p, gtk.Widget)


#glade = gtk.glade.XML('gui.glade', 'vbox1')
#p = glade.get_widget('vbox1')

print p.get_children()

w = gtk.Window()
w.add(p)
w.show_all()

gtk.main()
