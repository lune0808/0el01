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
	
	JTextArea outputNames;
	JTextArea outputTypes;
	JTextArea outputDetails;
	JButton quitButton;
	JButton playButton;
	JButton deleteButton;
	JPanel outputContainerPanel;
	JPanel outputPanel;
	JPanel buttonsPanel;
	JTextField searchBar;
	JMenuBar topMenuBar;
	JMenuBar outputMenuBar;
	Client client;
	
	private static final int SEARCH_COLUMNS = 32;
	private static final int OUTPUT_ROWS = 32;
	private static final int NAME_COLUMNS = 32;
	private static final int TYPE_COLUMNS = 8;
	private static final int DETAIL_COLUMNS = 48;

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
		outputContainerPanel = new JPanel(new BorderLayout());
		topMenuBar = new JMenuBar();
		buttonsPanel = new JPanel(new FlowLayout());
		add(topMenuBar, BorderLayout.NORTH);
		add(outputContainerPanel, BorderLayout.CENTER);
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
		
		outputMenuBar = new JMenuBar();
		JMenu outputNameField = new JMenu("Name");
		JMenu outputTypeField = new JMenu("Type");
		JMenu outputTypeSelector = new JMenu("v"); // TODO: should be an arrow icon
		outputTypeSelector.add(new JMenuItem("All"));
		outputTypeSelector.add(new JMenuItem("Photo(s)"));
		outputTypeSelector.add(new JMenuItem("Video(s)"));
		outputTypeSelector.add(new JMenuItem("Movie(s)"));
		outputTypeSelector.add(new JMenuItem("Group(s)"));
		JMenu outputDetailsField = new JMenu("Details...");
		searchBar = new JTextField(SEARCH_COLUMNS); // TODO: should show 'Search...' 
		outputMenuBar.add(outputNameField);
		outputMenuBar.add(outputTypeField);
		outputMenuBar.add(outputTypeSelector);
		outputMenuBar.add(outputDetailsField);
		outputMenuBar.add(searchBar);
		outputContainerPanel.add(outputMenuBar, BorderLayout.NORTH);
		
		outputPanel = new JPanel();
		outputNames = textArea(OUTPUT_ROWS, NAME_COLUMNS);
		outputPanel.add(new JScrollPane(outputNames));
		outputTypes = textArea(OUTPUT_ROWS, TYPE_COLUMNS);
		outputPanel.add(outputTypes);
		outputDetails = textArea(OUTPUT_ROWS, DETAIL_COLUMNS);
		outputPanel.add(outputDetails);
		outputContainerPanel.add(outputPanel, BorderLayout.CENTER);
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setTitle("SetTopBox");
		pack();
		setVisible(true);
	}
	
	private JTextArea textArea(int rows, int columns) {
		JTextArea result = new JTextArea(rows, columns);
		result.setEditable(false);
		return result;
	}
	
	/**
	 * Out-of-line definition for the quit action
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
	 * Out-of-line definition for the play action
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
	 * Out-of-line definition for the delete action
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

