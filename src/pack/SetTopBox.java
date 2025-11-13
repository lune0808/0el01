package pack;

import java.awt.BorderLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JScrollBar;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

public class SetTopBox extends JFrame {

	private static final long serialVersionUID = 1L;
	
	JTextArea text;
	JScrollPane textScroll;
	JButton[] button;

	public static void main(String[] args) {
		new SetTopBox();
	}
	
	private SetTopBox() {
		text = new JTextArea(10, 4);
		textScroll = new JScrollPane(text);

		button = new JButton[3];
		button[0] = new JButton("First");
		button[1] = new JButton("Quit");
		button[2] = new JButton("Third");
		
		text.setLineWrap(true);
		button[0].addActionListener(e -> text.append("First button clicked."));
		button[1].addActionListener(e -> System.exit(0));
		button[2].addActionListener(e -> text.append("Third button clicked."));
		
		add(textScroll, BorderLayout.SOUTH);
		add(button[0], BorderLayout.WEST);
		add(button[1], BorderLayout.NORTH);
		add(button[2], BorderLayout.EAST);
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setTitle("SetTopBox");
		pack();
		setVisible(true);
	}

}
