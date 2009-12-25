#!/usr/bin/python

import time

class Flyweight(type):
    def __init__(cls, name, bases, dct):
        cls.__instances = {}
        type.__init__(cls, name, bases, dct)

    def __call__(cls, key, *args, **kw):
        instance = cls.__instances.get(key)
        if instance is None:
            instance = type(cls, key, *args, **kw)
            cls.__instances[key] = instance
        return instance


class Astro:
    __metaclass__ = Flyweight

    def __init__(self, key):
        print "Creando la instancia '%s'..." % key
        time.sleep(2)
        print "'%s' creado" % key


a = Astro('luna')
b = Astro('luna')
assert a is b
c = Astro('sol')
