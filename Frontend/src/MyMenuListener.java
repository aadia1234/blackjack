package src;

import java.awt.event.ActionEvent;

import javax.swing.AbstractAction;
import javax.swing.JMenuItem;

public class MyMenuListener extends AbstractAction {
    private static final long serialVersionUID = 1L;

    @Override
    public void actionPerformed(ActionEvent e) {
        JMenuItem menuItem = ((JMenuItem) e.getSource());
        switch (menuItem.getName().toLowerCase()) {
            default -> Main.getGUI().getPanel().setVisible(false);
        }
    }

}
