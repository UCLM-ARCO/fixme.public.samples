import sys, Ice
Ice.loadSlice('hello.ice')
import UCLM

import gtk

class Gui:
    def __init__(self, app):
        window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        window.resize(200,100)
        button = gtk.Button("pulsa")
        window.add(button)
        window.show_all()
        button.connect('clicked', self.on_button_clicked)
        window.connect('destroy', self.main_quit)


    def on_button_clicked(self, wd):
        app.send_hello()

    def main_quit(self, obj):
        gtk.main_quit()



class Client (Ice.Application):
    def run(self, argv):
        obj = self.communicator().stringToProxy(argv[1])

        self.hello = UCLM.HelloPrx.checkedCast(obj)
        if not self.hello:
            raise RuntimeError("Invalid proxy")

        gtk.main()
          
    def send_hello(self):
        self.hello.puts("Hello World!")
        

app = Client()
gui = Gui(app)
app.main(sys.argv, 'config')
