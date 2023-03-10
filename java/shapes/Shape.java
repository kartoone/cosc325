package shapes;

public abstract class Shape {

    public static final String DEFAULTCOLOR = "red";
    protected String color; // the data that is common to ALL shapes

    // default constructor
    public Shape() {
        this.color = DEFAULTCOLOR;
    }

    public Shape(String color) {
        this.color = color;
    }

    abstract public void draw();

}
