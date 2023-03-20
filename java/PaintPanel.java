import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;
import javax.swing.JPanel;

import shapes.*; 

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

public class PaintPanel extends JPanel implements MouseListener, MouseMotionListener {
    
    protected enum ShapeType {
        RECTANGLE, SQUARE, TRIANGLE, OVAL, CIRCLE
    }

    protected ArrayList<Shape> shapes = new ArrayList<>();
    protected ShapeType currentShape = ShapeType.RECTANGLE;
    protected String currentColor = "#ff0000";

    public PaintPanel() {
        super();
        addMouseListener(this);
        addMouseMotionListener(this);
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);
        System.out.println("painting....");
        int w = this.getWidth();
        int h = this.getHeight();
        int eye = 30;
        int eyespacing = 30;
        int centerx = w/2;
        int centery = h/2;
        int thirdy = h/3;
        int nose = 40;
        int mouth = 120;

        // draw the face (red)
        g.setColor(Color.RED);
        g.drawOval(10,10,w-20,h-20);

        // draw the eyes (blue rectangles)
        g.setColor(Color.BLUE);
        g.drawRect(centerx-eyespacing-eye,thirdy-eye,eye,eye);
        g.drawRect(centerx+eyespacing,thirdy-eye,eye,eye);

        // draw the nose (purple triangle)
        g.setColor(Color.MAGENTA);
        g.drawLine(centerx, centery, centerx + nose/2, centery + nose/2);
        g.drawLine(centerx + nose/2, centery + nose/2, centerx - nose/2, centery + nose/2);
        g.drawLine(centerx-nose/2, centery+nose/2, centerx, centery);

        // draw the mouth (black oval ... partially hidden)        
        g.setColor(Color.BLACK);
        g.drawOval(centerx-mouth/2, h-thirdy, mouth, nose);

        // hide the top part of the mouth to make it look like a smile
        g.setColor(Color.WHITE);
        g.fillRect(centerx-mouth/2, h-thirdy-20, mouth, 40);

        for (Shape s : shapes) {
            s.draw(g);
        }
    }

    @Override
    public void mouseClicked(MouseEvent e) {
        // pay me now ... calculate the top left corner from the mouse x, y
        // hard-coded example 40 x 10 rectangle
        int mousex = e.getX();
        int mousey = e.getY();
        int topleftx = mousex - 40/2;
        int toplefty = mousey - 10/2;
        System.out.println(mousex + " " + mousey);
        Shape s;
        if (currentShape == ShapeType.RECTANGLE) {
            s = new Rectangle(topleftx, toplefty, 40, 10, "#ff0000");
        } else if (currentShape == ShapeType.SQUARE) {
            s = new Square(topleftx, toplefty, 40, "#ff0000");
        } else {
            // draw a rectangle by default
            s = new Rectangle(topleftx, toplefty, 40, 10, "#ff0000");
        }
        shapes.add(s);
        s.draw(getGraphics());
    }

    @Override
    public void mousePressed(MouseEvent e) {
        // handled in mouseClicked
        System.out.println("released");
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        // handled in mouseClicked
    }

    @Override
    public void mouseEntered(MouseEvent e) {
        // ignored
    }

    @Override
    public void mouseExited(MouseEvent e) {
        // ignored
    }

    @Override
    public void mouseDragged(MouseEvent e) {
        mouseClicked(e);
    }

    @Override
    public void mouseMoved(MouseEvent e) {
    }  

}
