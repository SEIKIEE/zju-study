import java.awt.desktop.OpenURIEvent;

public class Ex5_TestInnerAnonymous {
    public static void main(String[] args) {
        Outer a = new Outer();
        Outer.m(a);
        System.out.println(a.i);
    }
}

class Outer {
    private int size = 5;
    public int i;

    Outer() {
        i = 1;
    }

    public Object makeTheInner(int localVar) {
        final int finalLocalVar = 99;

        return new Object() {
            public String toString() {
                return ("InnerSize:" + size + "\n" +
                        "finalLocalVar:" + finalLocalVar);
            }
        };
    }

    public static void m(Outer a) {
        a.i = 3;
    }
}

