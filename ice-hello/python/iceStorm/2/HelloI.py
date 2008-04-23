import UCLM

class HelloI(UCLM.Hello):
    def puts(self, msg, current=None):
        print "SERVER: Se recibio el valor: '%s'" % msg

    def shutdown(self,current):
        print "Shutting down..."
        current.adapter.getCommunicator().shutdown()
