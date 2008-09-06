# -*- coding: utf-8 -*-

import gtk.glade

class GladeWrapper(object):

    def __init__(self, glade_file, root_widget=None):
        self.__glade = gtk.glade.XML(glade_file, root_widget)
        self.__glade.signal_autoconnect(self)


    def get_widget(self, name):
        return self.__glade.get_widget(name)


    def __getattr__(self, name):
        try:
            return self.__dict__[name]
        except KeyError, e:
            if name.startswith("wg_"):
                try:
                    ret = self.__glade.get_widget(name[3:])
                except AttributeError:
                    raise AttributeError("You must call GladeWrapper.__init__() in your derived class")

                if ret:
                    self.__dict__[name] = ret
                    return ret

            raise AttributeError, "%s: %s" % (str(self.__class__), e)


class GladeWidget(type):

    def __call__(cls, *args, **kargs):

        assert hasattr(cls, 'WIDGET'), "'GladeWidget users must have a 'WIDGET' attribute"
        gladefile, widget = cls.WIDGET.split(':')

        glade = gtk.glade.XML(gladefile, widget)
        widget = glade.get_widget(widget)

        dct = dict(cls.__dict__)
        
        # widget methods wrapping
        for atr in dir(widget):
            if not atr.startswith('__'): dct[atr] = getattr(widget, atr)

        instance =  type(cls.__name__,
                         (widget.__class__, GladeWrapper) + cls.__bases__,
                         dct)(*args, **kargs)

        # simulate GladeWrapper initialize
        instance._GladeWrapper__glade = glade
        glade.signal_autoconnect(instance)

        return instance


#class GladeWidget2(type):
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
