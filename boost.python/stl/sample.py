import Control
actuator = Control.IntRW()
actuator.set(100)
print actuator.get()

d = actuator.refs()
print "get dict:   ", d
print "dict.keys:  ", d.keys()
print "dict.values:", d.values()
print "dict.items: ", d.items()
print "len(dict)): ", len(d)
print "dict[k]:    ", d['foo']
d["other"] = "world"
print "dict[k] = v:", d["other"]
del d["other"]
print "del dict[k]:", d.keys()
print "x in dict:  ", "foo" in d
d.clear()
print "dict.clear: ", d.keys()
try:
    print d["missing"]
except KeyError:
    print "dict[missing]: OK"

v = actuator.all()
print "get list:   ", v
v.append("tree")
print "v.append(x):", list(v)
print "len(v):     ", len(v)
print "v[i]:       ", v[1]
v[1] = "TWO"
print "v[i]=x:     ", list(v)

for i in range(len(v)):
    print v[i]

v.clear()
print "v.clear():  ", list(v), len(v)

try:
    print ':', v[1000]
except IndexError:
    print "v[1000]: OK"
