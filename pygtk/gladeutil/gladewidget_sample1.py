#!/usr/bin/python

import gladeutil

class Panel(object):

    __metaclass__ = gladeutil.Widget
    WIDGET = ('gui.glade', 'vbox1')

    def __init__(self, pname):
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

# gladewrapped
print p.wg_entry
print p._Wrapper__glade
