# http://www.daa.com.au/pipermail/pygtk/2001-October/002056.html

'''An example script demonstrating the use of generators to implement
simple coroutines in a pygtk application.'''

from __future__ import generators

import gtk

def coroutine(name=''):
    '''A simple generator to be run as a timeout/idle function,
    demonstrating a way to break an expensive algorithm into small
    chunks that can be processed within the mainloop without having to
    turn all the logic inside out.

    Every time "yield gtk.TRUE" is executed, control is returned to
    the main loop.  A "yield gtk.FALSE" will cancel the idle handler.
    Falling off the end of the generator will print out a (very) small
    stack trace for the StopIteration exception.

    While the same thing could possibly be done by calling
    gtk.main_iteration(), to pass control to the main loop, the
    generator approach allows multiple routines to be run
    concurrently.

    Cancelling the coroutine is as simple as calling
    gtk.timeout_remove() on the id returned by gtk.timeout_add'''
    i = 0
    while 1:
        print name, 'processing:', i
        i = i + 1
        yield gtk.TRUE

def short_coroutine():
    '''Short coroutine/generator that terminates after 10 iterations.'''
    for i in range(10):
        print 'short routine:', i
        yield gtk.TRUE
    print 'short routine terminating.'
    yield gtk.FALSE

# we could also use generators as idle functions ...
id1 = gtk.timeout_add(1000, coroutine('routine 1').next)
id2 = gtk.timeout_add(2000, coroutine('routine 2').next)
id3 = gtk.idle_add(short_coroutine().next)

def quit(widget):
    gtk.main_quit()

def kill1(widget):
    '''Small signal handler that cancels one of the coroutines.'''
    gtk.timeout_remove(id1)

window = gtk.Window()
window.set_title('Co-routine test')
window.connect('destroy', quit)

button = gtk.Button('Kill routine 1')
button.connect('clicked', kill1)
window.add(button)

window.show_all()

gtk.main()
