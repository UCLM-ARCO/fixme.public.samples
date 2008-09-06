# -*- coding: utf-8 -*-

import gtk.glade


class Wrapper(object):

    def __init__(self, glade_file, root_widget=None):
        self.glade = gtk.glade.XML(glade_file, root_widget)
        self.glade.signal_autoconnect(self)


    def get_widget(self, name):
        return self.glade.get_widget(name)


    def __getattr__(self, key):
        print 'trying to get', key
        try:
            #return self.glade.get_widget(key[3:])
            #return getattr(self, key)
            #return self.__dict__[key]
            return object.__getattribute__(self, key)

        except AttributeError, e:
            if key.startswith("wg_"):
                try:
                    ret = self.glade.get_widget(key[3:])
                except AttributeError:
                    raise AttributeError("You must call gladeutil.Wrapper.__init__() in your derived class")

                if ret:
                    setattr(self, key, ret)
                    #self.__dict__[key] = ret
                    return ret

            raise AttributeError, "%s: %s" % (str(self.__class__), e)


class Widget(type):


    def init(self):
        Wrapper.__init__(self)

    def __call__(cls, *args, **kargs):

        assert hasattr(cls, 'WIDGET'), "'gladeutil.Widget users must have a 'WIDGET' attribute"
        gladefile, widget = cls.WIDGET

        glade = gtk.glade.XML(gladefile, widget)
        widget = glade.get_widget(widget)

        dct = dict(cls.__dict__)
        bases = (widget.__class__, Wrapper)
        if not object in cls.__bases__:
            bases += cls.__bases__

        # widget methods wrapping
        for atr in dir(widget):
            if not atr.startswith('__'): dct[atr] = getattr(widget, atr)

        instance = type(cls.__name__, bases, dct)(*args, **kargs)

        # simulate Wrapper initialize
        instance.glade = glade
        glade.signal_autoconnect(instance)

        print "listo"
        return instance


# alternate implementation
#
#class Widget2(type):
#
#    def __call__(cls, *args):
#
#        def getattribute(self, name):
#            print '__invocando', name
#
#            if name != 'widget' and name in dir(self.widget):
#                return object.__getattribute__(self.widget, name)
#
#            return object.__getattribute__(self, name)
#
#
#        glade = gtk.glade.XML(cls.gladefile, cls.widget)
#        widget = glade.get_widget(cls.widget)
#
#        dct = dict(cls.__dict__)
#        dct['widget'] = widget
#        dct['__getattribute__'] = getattribute
#
#        return type(cls.__name__, (widget.__class__,), dct)(args)
