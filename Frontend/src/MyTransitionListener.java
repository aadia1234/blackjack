package src;

import java.awt.BorderLayout;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;

import javax.swing.JPanel;

public class MyTransitionListener extends ComponentAdapter {
    public static enum gameType {
        WAGER(), BET()
    }

    @Override
    public void componentHidden(ComponentEvent e) {
        JPanel currentPanel = ((JPanel) e.getSource());

        switch (currentPanel.getName()) {
            case "Home" -> {
                HomeGUI home = ((HomeGUI) Main.getGUI());
                Main.setGUI(new GameGUI(home.getGameChoice(), home.getMoneyInput()));
            }

            case "Game" -> Main.setGUI(new HomeGUI());
        }
        currentPanel.removeAll();
        currentPanel.getParent().revalidate();
        currentPanel.getParent().repaint();
        currentPanel.getParent().add(Main.getGUI().getPanel(), BorderLayout.CENTER);
    }
}
