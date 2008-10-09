import Control
actuator = Control.IntRW()
actuator.set(100)
print actuator.get()


# print actuator.all()  # error

a = Control.wrap_factory()
print a.all()
