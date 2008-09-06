
import gtk.glade
import gladewrapper


class A(object):
    pass


class Panel(A):

    __metaclass__ = gladewrapper.GladeWidget
    WIDGET = 'gui.glade:vbox1'

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
