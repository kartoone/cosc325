import shapes.*;

import java.util.ArrayList;

public class ShapeExample {
    public static void main(String[] args) {
        ArrayList<Shape> shapes = new ArrayList<>(); 
        shapes.add(new Rectangle(0, 0, 25, 5, "#ff0000"));
        shapes.add(new Oval(0, 0, 15, 5, "#ff0000"));
        shapes.add(new Circle(0, 0, 3, "#00ff00"));
        shapes.add(new Square(0, 0, 10, "#0000ff"));
        shapes.add(new Triangle(1, 1, 4, 2, 3, 3, "#00ffff"));
        for (Shape s : shapes) {
            s.draw(null); // polymorphism! we have one line of code here that can call many different draw() methods depending on the specific shape s.
        }
    }  
}
