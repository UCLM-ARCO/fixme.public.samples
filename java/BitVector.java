class BitVector {
    public final byte MAX_EVENTS = 64;
    private long events;
    
    BitVector() {
	events = 0;
    }
    
    public synchronized void push(int event) {
	if (event < MAX_EVENTS) events |= (1<<event);
    }
    
    public int pop() {
	long mask = 1;
	for (int counter = 0; counter < MAX_EVENTS; counter++) {
	    if (0 != (events & mask)) {
		events &= ~mask;
		return counter;
	    }
	    mask <<= 1;
	}
	return -1;		
    }
    
    public boolean hasEvent(int event) {
	if (event < MAX_EVENTS) 
	    return 0 != (events & (1<<event));
	return false;
    }
    
    public boolean hasPending(){
	return 0 != events;
    }

    static public void main(String[] args) {
	BitVector v = new BitVector();
	System.out.println(v.hasPending());
	v.push(0);
	v.push(5);
	v.push(8);
	System.out.println(v.hasPending());
	System.out.println(v.hasEvent(1));
	System.out.println(v.hasEvent(2));
	System.out.println(v.hasEvent(0));
	System.out.println(v.pop());
	System.out.println(v.pop());
	System.out.println(v.pop());
	System.out.println(v.hasPending());
    }
}
