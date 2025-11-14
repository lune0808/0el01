package pack;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.io.IOException;

import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

/**
 * @brief the main class of the SetTopBox package
 * 
 * This class is the entry point into the Java side
 * of the project.
 */
public class SetTopBox extends JFrame {

	private static final long serialVersionUID = 1L;
	
	JTextArea output;
	JScrollPane outputScroll;
	JButton quitButton;
	JButton playButton;
	JButton deleteButton;
	JPanel outputPanel;
	JPanel buttonsPanel;
	JTextField searchBar;
	JMenuBar topMenuBar;
	JMenuBar outputMenuBar;
	Client client;

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
		outputPanel = new JPanel(new BorderLayout());
		topMenuBar = new JMenuBar();
		buttonsPanel = new JPanel(new FlowLayout());
		add(topMenuBar, BorderLayout.NORTH);
		add(outputPanel, BorderLayout.CENTER);
		add(buttonsPanel, BorderLayout.SOUTH);
		
		Action quit = new QuitAction();
		Action play = new PlayAction();
		Action delete = new DeleteAction();
		
		JMenu topMenu = new JMenu("Menu");
		topMenu.add(quit);
		topMenu.add(play);
		topMenu.add(delete);
		topMenuBar.add(topMenu);
		
		buttonsPanel.add(new JButton(quit));
		buttonsPanel.add(new JButton(play));
		buttonsPanel.add(new JButton(delete));
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setTitle("SetTopBox");
		pack();
		setVisible(true);
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
	 * Out-of-line definition for the first action
	 */
	private class PlayAction extends AbstractAction {

		private static final long serialVersionUID = 1L;

		public PlayAction() {
			super("Play");
		}
		
		@Override
		public void actionPerformed(ActionEvent e) {
		}
		
	}
	
	/**
	 * Out-of-line definition for the third action
	 */
	private class DeleteAction extends AbstractAction {

		private static final long serialVersionUID = 1L;

		public DeleteAction() {
			super("Delete");
		}
		
		@Override
		public void actionPerformed(ActionEvent e) {
		}
		
	}

}

