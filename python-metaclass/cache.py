#!/usr/bin/python

import time

class Cache(type):
    def __init__(cls, name, bases, dct):
        cls.__instances = {}
        type.__init__(cls, name, bases, dct)

    def __call__(cls, key, *args, **kw):
        instance = cls.__instances.get(key)
        if instance is None:
            instance = type.__call__(cls, key, *args, **kw)
            cls.__instances[key] = instance
        return instance

class A:
    __metaclass__ = Cache

    def __init__(self, key):
        print "Building instance", key
        time.sleep(2)


a = A('i1')
b = A('i1')
assert a == b
c = A('i2')
