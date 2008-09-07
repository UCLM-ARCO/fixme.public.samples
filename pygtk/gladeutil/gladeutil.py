# -*- coding: utf-8 -*-

import inspect, functools

import gtk.glade


class Wrapper(object):

    def __init__(self, glade_file, root_widget=None):
        self.glade = gtk.glade.XML(glade_file, root_widget)
        self.glade.signal_autoconnect(self)
        self.get_widget = self.glade.get_widget


    def __getattr__(self, key):
        print 'trying to get', key
        try:
            return object.__getattribute__(self, key)
        except AttributeError, e:
            if not key.startswith("wg_"): raise

            if not hasattr(self, 'glade'):
                raise AttributeError("You must call gladeutil.Wrapper.__init__() in your derived class")

            ret = self.glade.get_widget(key[3:])
            if ret == None:
                raise AttributeError, "'%s' has no widget '%s'" % (self.__class__.__name__, key[3:])

            setattr(self, key, ret)
            return ret



class Widget(type):

    def __call__(cls, *args, **kargs):

        #def getattr(self, key):
        #    print 'Widget.deco:', key
        #    if hasattr(self.decorated, key):
        #        return getattr(self.decorated, key)
        #    else:
        #        return Wrapper.__getattr__(self, key)


        def deco_method(former, *args):
            #print "deco:", former, args
            return former(*args[1:])

        def deco_attr(obj, key):
            return getattr(obj, key)

        #def deco_getchildren(self, *args):
        #    print 'get_children'
        #    return self.decorated.get_children(*args)

        assert hasattr(cls, 'WIDGET'), "gladeutil.Widget users must have a 'WIDGET' attribute"

        gladefile, widgetname = cls.WIDGET

        glade = gtk.glade.XML(gladefile, widgetname)
        widget = glade.get_widget(widgetname)
        widget.realize()

        dct = widget.__dict__.copy()

        #print cls.__dict__.keys()

        #dct = {}

        for k, v in inspect.getmembers(widget):
            if k.startswith('__'): continue
            if callable(v):
                dct[k] = functools.partial(deco_method, v, widget)
            else:
                #print 'attr', k, type(k)
                dct[k] = deco_attr(widget, k)


        for k,v in cls.__dict__.items():
#            if k.startswith('__') and k != '__init__': continue
            print 'attr:', k
            dct[k] = v

        #dct.update(cls.__dict__)

        #dct = dict(cls.__dict__)
        dct['glade'] = glade
        dct['decorated'] = widget
        #dct['__getattr__'] = getattr
        #dct['get_children'] = deco_getchildren



        bases = (widget.__class__, Wrapper) + cls.__bases__

        # widget methods wrapping
        #for atr in dir(widget):
        #    if not atr.startswith('__'): dct[atr] = getattr(widget, atr)

        instance = type(cls.__name__, bases, dct)(*args, **kargs)
        print instance
        widget.__class__.__init__(instance)
        glade.signal_autoconnect(instance)


        print "listo"
        return instance



class Widget2(type):
    def __call__(cls, *args, **kargs):

        assert hasattr(cls, 'WIDGET'), "gladeutil.Widget users must have a 'WIDGET' attribute"

        gladefile, widgetname = cls.WIDGET

        glade = gtk.glade.XML(gladefile, widgetname)
        widget = glade.get_widget(widgetname)

        #for k,v in cls.__dict__.items():
        #    setattr(widget, k, v)

        dct = dict(cls.__dict__)
        bases = (widget.__class__, Wrapper) + cls.__bases__

        instance = type(cls.__name__, bases, dct)(*args, **kargs)
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
