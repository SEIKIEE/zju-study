public class Bind{
    public static void main(String[] args) {
        Child c = new Child();
        Parent p = c;

        System.out.println(p.getPristr());
        System.out.println(c.pristr);
        c.print();
        p.print();

        c.print1();
        p.print1();

        c.print2();
        p.print2();

    }
}

class Parent{
    private String pristr = "parent private string";
    String pubstr = "public string";

    public String getPristr() {
        return pristr;
    }

    public void setPristr(String pristr) {
        this.pristr = pristr;
    }

    public Parent() {
        System.out.println("parent构造函数");
    }

    final public void print() {
        System.out.println("parent的print");
    }

    public static void print1() {
        System.out.println("parent的print1");
    }

    public void print2() {
        System.out.println("parent的print2");
    }

}

class Child extends Parent{
    String pristr = "child private string";
    String pubstr = "public string";

    public Child() {
        System.out.println("child构造函数");
    }

    public static void print1() {
        System.out.println("child的print1");
    }

    public void print2() {
        System.out.println("child的print2");
    }
}

