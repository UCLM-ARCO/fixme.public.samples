#!/usr/bin/python
# -*- coding:utf-8 -*-

from jinja2 import Environment, FileSystemLoader

class Person:
    def __init__(self, firstname, lastname):
        self.firstname = firstname
        self.lastname = lastname

    def __str__(self):
        return "<Person %s %s>" % (self.firstname, self.lastname)

person = Person("Juan", "Nadie Conocido")

env = Environment(loader=FileSystemLoader('.'))
template = env.get_template('sample.tmpl')
out = template.render(person=person)
print out
