package pack;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.io.IOException;
import java.util.Arrays;

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
import javax.swing.JTextPane;
import javax.swing.text.SimpleAttributeSet;
import javax.swing.text.StyleConstants;

/**
 * @brief the main class of the SetTopBox package
 * 
 * This class is the entry point into the Java side
 * of the project.
 */
public class SetTopBox extends JFrame {

	private static final long serialVersionUID = 1L;

	JPanel outputNames;
	JPanel outputTypes;
	JPanel outputDetails;
	JTextArea outputNamesContent;
	JTextArea outputTypesContent;
	JTextArea outputDetailsContent;
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
	String serverResponse;
	
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
		try {
			client = new Client("localhost", 3331);
			serverResponse = client.send("all ");
		} catch (IOException e) {
			System.exit(ABORT);
		}
		
		outputContainerPanel = new JPanel(new FlowLayout());
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
		searchBar = new JTextField(SEARCH_COLUMNS); // TODO: should show 'Search...'
		outputMenuBar.add(searchBar);
		outputContainerPanel.add(outputMenuBar, BorderLayout.NORTH);

		outputPanel = new JPanel(new FlowLayout());
		SimpleAttributeSet fieldAttributes = new SimpleAttributeSet();
		StyleConstants.setItalic(fieldAttributes, true);
		outputNames = new JPanel(new BorderLayout());
		JTextPane outputNameField = new JTextPane();
		outputNameField.setCharacterAttributes(fieldAttributes, false);
		outputNameField.setText("Name");
		outputNameField.setEditable(false);
		outputNames.add(outputNameField, BorderLayout.NORTH);
		outputNamesContent = textArea(OUTPUT_ROWS, NAME_COLUMNS);
		outputNames.add(new JScrollPane(outputNamesContent), BorderLayout.CENTER);
		outputPanel.add(outputNames);
		JTextPane outputTypeField = new JTextPane();
		outputTypeField.setCharacterAttributes(fieldAttributes, false);
		outputTypeField.setText("Type");
		outputTypeField.setEditable(false);
		// TODO: show these menus
		JMenu outputTypeSelector = new JMenu("v"); // TODO: should be an arrow icon
		outputTypeSelector.add(new JMenuItem("All"));
		outputTypeSelector.add(new JMenuItem("Photo(s)"));
		outputTypeSelector.add(new JMenuItem("Video(s)"));
		outputTypeSelector.add(new JMenuItem("Movie(s)"));
		outputTypeSelector.add(new JMenuItem("Group(s)"));
		outputTypesContent = textArea(OUTPUT_ROWS, TYPE_COLUMNS);
		outputTypes = new JPanel(new BorderLayout());
		outputTypes.add(outputTypeField, BorderLayout.NORTH);
		outputTypes.add(outputTypesContent, BorderLayout.CENTER);
		outputPanel.add(outputTypes);
		JTextPane outputDetailsField = new JTextPane();
		outputDetailsField.setCharacterAttributes(fieldAttributes, false);
		outputDetailsField.setText("Details...");
		outputDetailsField.setEditable(false);
		outputDetails = new JPanel(new BorderLayout());
		outputDetails.add(outputDetailsField, BorderLayout.NORTH);
		outputDetailsContent = textArea(OUTPUT_ROWS, DETAIL_COLUMNS);
		outputDetails.add(new JScrollPane(outputDetailsContent), BorderLayout.CENTER);
		outputPanel.add(new JScrollPane(outputDetails));
		outputContainerPanel.add(outputPanel, BorderLayout.CENTER);
		
		outputNamesContent.setText(serverResponse);
		searchBar.addActionListener(new SearchAction());
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setTitle("SetTopBox");
		pack();
		setVisible(true);
	}
	
	private void parseResponseAll(String response) {
		outputNamesContent.setText(response.replace(' ', '\n'));
		outputTypesContent.setText("");
		outputDetailsContent.setText("");
	}
	
	private void parseResponsePlay(String response) {
		// TODO: visual feedback
		System.out.println(response.charAt(0) == 'Y'? "Success": "Failure");
	}
	
	private void parseResponseRemove(String response) {
		// TODO: visual feedback
		System.out.println(response.charAt(0) == 'Y'? "Success": "Failure");
	}
	
	private void parseResponsePrefixed(String response) {
		parseResponseAll(response);
	}
	
	private void parseResponseType(String response) {
		parseResponseAll(response);
	}
	
	private void parseResponseFind(String response) {
		String[] words = response.split("[ ]");
		if (words.length < 3)
			return;
		outputNamesContent.setText(words[0]);
		outputTypesContent.setText(words[words.length - 1]);
		outputDetailsContent.setText(String.join(" ", Arrays.copyOfRange(words, 1, words.length - 1)));
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
	
	/**
	 * Out-of-line definition for the search action
	 */
	private class SearchAction extends AbstractAction {

		private static final long serialVersionUID = 1L;

		public SearchAction() {
			super("Search");
		}
		
		@Override
		public void actionPerformed(ActionEvent e) {
			String request = e.getActionCommand();
			serverResponse = client.send(request);
			parseResponseFind(serverResponse);
		}
		
	}

}

