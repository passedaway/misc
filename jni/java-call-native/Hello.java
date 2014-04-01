
public class Hello {
	public native void init();
	public native void exit();

	static {
		System.loadLibrary("hello");
	}

	public static void main(String[] args)
	{
		Hello hello = new Hello();
		hello.init();
		hello.exit();
	}

}

