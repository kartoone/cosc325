import java.util.function.Consumer;

public class Examples {
    public void doit(Consumer<String> f, String msg) {
        f.accept(msg);
    }
    public static void main(String[] args) {
        Examples example = new Examples();
        example.doit(message->System.out.println(message), "Hello, World!");
    }
}