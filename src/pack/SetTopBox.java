package pack;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

/**
 * @brief the main class of the SetTopBox package
 * 
 * This class is the entry point into the Java side
 * of the project.
 */
public class SetTopBox extends JFrame {

	private static final long serialVersionUID = 1L;
	
	JTextArea text;
	JScrollPane textScroll;
	JMenuBar menuBar;
	Action firstAction;
	Action quitAction;
	Action thirdAction;

	/**
	 * Entry point of the program
	 * 
	 * @param args ignored
	 */
	public static void main(String[] args) {
		new SetTopBox();
	}
	
	/**
	 * Spawns a window with UI
	 */
	private SetTopBox() {
		text = new JTextArea(40, 80);
		textScroll = new JScrollPane(text);
		menuBar = new JMenuBar();
		firstAction = new FirstAction();
		quitAction = new QuitAction();
		thirdAction = new ThirdAction();
		
		JButton firstButton = new JButton(firstAction);
		JButton quitButton = new JButton(quitAction);
		JButton thirdButton = new JButton(thirdAction);
		JMenu menu = new JMenu("Menu");
		menu.add(new JMenuItem(firstAction));
		menu.add(new JMenuItem(quitAction));
		menu.add(new JMenuItem(thirdAction));
		
		text.setLineWrap(true);
		
		add(textScroll, BorderLayout.CENTER);
		add(firstButton, BorderLayout.WEST);
		add(quitButton, BorderLayout.SOUTH);
		add(thirdButton, BorderLayout.EAST);
		menuBar.add(menu);
		add(menuBar, BorderLayout.NORTH);
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setTitle("SetTopBox");
		pack();
		setVisible(true);
	}
	
	/**
	 * Out-of-line definition for the first action
	 */
	private class FirstAction extends AbstractAction {

		private static final long serialVersionUID = 1L;

		public FirstAction() {
			super("First");
		}
		
		@Override
		public void actionPerformed(ActionEvent e) {
			text.append("First button pressed.");
		}
		
	}
	
	/**
	 * Out-of-line definition for the first action
	 */
	private class QuitAction extends AbstractAction {

		private static final long serialVersionUID = 1L;

		public QuitAction() {
			super("Quit");
		}
		
		@Override
		public void actionPerformed(ActionEvent e) {
			System.exit(0);
		}
		
	}
	
	/**
	 * Out-of-line definition for the third action
	 */
	private class ThirdAction extends AbstractAction {

		private static final long serialVersionUID = 1L;

		public ThirdAction() {
			super("Third");
		}
		
		@Override
		public void actionPerformed(ActionEvent e) {
			text.append("Third button pressed.");
		}
		
	}

}

