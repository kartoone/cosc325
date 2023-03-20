import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.Dimension;
import java.awt.Color;
import java.awt.event.ActionListener;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JRadioButtonMenuItem;
import javax.swing.event.MenuKeyEvent;
import java.awt.event.ActionEvent;

public class ShapeSwingProgram extends JFrame implements ActionListener {
    
    
    protected PaintPanel paintPanel = new PaintPanel();

    public ShapeSwingProgram(String title) {
        super(title);
        this.setSize(800, 600);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setLayout(new BorderLayout());        
        JPanel buttonPanel = new JPanel(new FlowLayout());
        JButton button1 = new JButton("button1");
        button1.addActionListener(this);
        buttonPanel.add(button1);
        JButton button2 = new JButton("button2");
        button2.addActionListener(this);
        buttonPanel.add(button2);
        this.add(buttonPanel, BorderLayout.PAGE_START);
        JMenuBar menuBar;
        JMenu menu, submenu;
        JMenuItem menuItem;
        JRadioButtonMenuItem rbMenuItem;

        //Create the menu bar.
        menuBar = new JMenuBar();

        //Build the first menu.
        menu = new JMenu("File");
        menu.setMnemonic(MenuKeyEvent.VK_F);
        menuBar.add(menu);

        //a group of file-related menu items 
        menuItem = new JMenuItem("Open", MenuKeyEvent.VK_O);
        menuItem.addActionListener(this);
        menu.add(menuItem);
        menuItem = new JMenuItem("Save", MenuKeyEvent.VK_S);
        menuItem.addActionListener(this);
        menu.add(menuItem);
        menuItem = new JMenuItem("Save As...", MenuKeyEvent.VK_A);
        menuItem.addActionListener(this);
        menu.add(menuItem);
        menuItem = new JMenuItem("Exit", MenuKeyEvent.VK_X);
        menuItem.addActionListener(this);
        menu.add(menuItem);

        //Build our shape menu
        menu = new JMenu("Shape");
        menuItem = new JMenuItem("Rectangle", MenuKeyEvent.VK_R);
        menuItem.addActionListener(this);
        menu.add(menuItem);
        menuItem = new JMenuItem("Square", MenuKeyEvent.VK_S);
        menuItem.addActionListener(this);
        menu.add(menuItem);
        menuItem = new JMenuItem("Oval", MenuKeyEvent.VK_O);
        menuItem.addActionListener(this);
        menu.add(menuItem);
        menuItem = new JMenuItem("Circle", MenuKeyEvent.VK_C);
        menuItem.addActionListener(this);
        menu.add(menuItem);
        menuItem = new JMenuItem("Triangle", MenuKeyEvent.VK_T);
        menuItem.addActionListener(this);
        menu.add(menuItem);

        // Create the color submenu
        menu.addSeparator();        
        submenu = new JMenu("Color");

        // create a group so you can only select one color at a time
        ButtonGroup group = new ButtonGroup();
        rbMenuItem = new JRadioButtonMenuItem("Red");
        rbMenuItem.addActionListener(this);
        rbMenuItem.setSelected(true);
        group.add(rbMenuItem);
        submenu.add(rbMenuItem);
        rbMenuItem = new JRadioButtonMenuItem("Yellow");
        rbMenuItem.addActionListener(this);
        group.add(rbMenuItem);
        submenu.add(rbMenuItem);
        rbMenuItem = new JRadioButtonMenuItem("Green");
        rbMenuItem.addActionListener(this);
        group.add(rbMenuItem);
        submenu.add(rbMenuItem);
        rbMenuItem = new JRadioButtonMenuItem("Black");
        rbMenuItem.addActionListener(this);
        group.add(rbMenuItem);
        submenu.add(rbMenuItem);
        rbMenuItem = new JRadioButtonMenuItem("White");
        rbMenuItem.addActionListener(this);
        group.add(rbMenuItem);
        submenu.add(rbMenuItem);

        // Turn submenu into an actual submenu by adding it to another menu (specifically, our second menu)
        menu.add(submenu);
        menuBar.add(menu);
        this.setJMenuBar(menuBar);

        paintPanel.setPreferredSize(new Dimension(500,500));
        paintPanel.setBackground(Color.WHITE);
        this.getContentPane().add(paintPanel, BorderLayout.CENTER);

    }

    public static void main(String[] args) {
        ShapeSwingProgram paintprogram = new ShapeSwingProgram("Shape Dropper Paint Program");
        paintprogram.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getActionCommand()=="Rectangle")
            paintPanel.currentShape = PaintPanel.ShapeType.RECTANGLE;
        else if (e.getActionCommand()=="Square")
            paintPanel.currentShape = PaintPanel.ShapeType.SQUARE;
    }
}
