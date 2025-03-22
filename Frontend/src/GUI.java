package src;

import java.awt.Component;
import java.awt.Font;
import java.awt.GraphicsEnvironment;
import java.awt.GridLayout;
import java.io.File;
import java.io.FileInputStream;
import java.util.HashMap;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.UIManager;

public class GUI {
    JPanel panel;
    public static Font defaultFont = javax.swing.UIManager.getDefaults().getFont("Label.font");
    private HashMap<String, Font> fontsMap;

    private enum fonts {
        OXYGEN_BOLD, OXYGEN_REGULAR;

        @Override
        public String toString() {
            return name().toLowerCase() + ".ttf";
        }

        public String getPath() {
            // Try multiple possible locations
            String[] possiblePaths = {
                    "/Users/Aadi/Desktop/demos/Frontend/src/Oxygen/" + toString(),
                    "/Users/Aadi/Desktop/demos/Frontend/resources/Oxygen/" + toString(),
                    "/Users/Aadi/Desktop/demos/Blackjack_Java/resources/Oxygen/" + toString(),
                    "./src/Oxygen/" + toString(),
                    "./resources/Oxygen/" + toString()
            };

            for (String path : possiblePaths) {
                File file = new File(path);
                if (file.exists()) {
                    System.out.println("Found font at: " + path);
                    return path;
                }
            }

            System.err.println("Could not find font: " + toString() + " in any expected location.");
            return null;
        }
    }

    public GUI(String panelName) {
        panel = new JPanel();
        fontsMap = new HashMap<>();

        // First, try to load fonts from filesystem
        loadFontsFromFileSystem();

        // If fonts are still not loaded, use system defaults
        Font labelFont = fontsMap.getOrDefault(fonts.OXYGEN_BOLD.name(), defaultFont);
        Font regularFont = fontsMap.getOrDefault(fonts.OXYGEN_REGULAR.name(), defaultFont);

        setUIFont("Label.font", labelFont, 30);
        setUIFont("Button.font", regularFont, 25);
        setUIFont("TextField.font", regularFont, 25);

        panel.addComponentListener(new MyTransitionListener());
        panel.setBorder(BorderFactory.createEmptyBorder(25, 25, 25, 25));
        panel.setLayout(new GridLayout(0, 1));
        panel.setName(panelName);
    }

    private void loadFontsFromFileSystem() {
        try {
            for (fonts font : fonts.values()) {
                String path = font.getPath();
                if (path == null) {
                    System.err.println("Skipping font " + font.name() + " as path is null");
                    continue;
                }

                File fontFile = new File(path);
                Font myFont = Font.createFont(Font.TRUETYPE_FONT, new FileInputStream(fontFile));
                fontsMap.put(font.name(), myFont);
                GraphicsEnvironment.getLocalGraphicsEnvironment().registerFont(myFont);
                System.out.println("Successfully loaded font: " + font.name());
            }
        } catch (Exception e) {
            System.err.println("Error loading fonts: " + e.getMessage());
            e.printStackTrace();
        }
    }

    public void setComponentAlignment(JPanel tempPanel) {
        for (Component component : tempPanel.getComponents()) {
            if (component instanceof JLabel) {
                ((JLabel) component).setHorizontalAlignment(JLabel.CENTER);
            } else if (component instanceof JButton) {
                ((JButton) component).setHorizontalAlignment(JButton.CENTER);
            } else if (component instanceof JTextField) {
                ((JTextField) component).setHorizontalAlignment(JTextField.CENTER);
            }
        }
    }

    public void setComponentAlignment() {
        this.setComponentAlignment(this.panel);
    }

    protected void showMessage(String title, String message) {
        JOptionPane.showMessageDialog(Main.getFrame(), message, title, JOptionPane.OK_OPTION);
    }

    private static void setUIFont(String component, Font font, int fontSize) {
        try {
            if (font != null) {
                UIManager.put(component, new Font(font.getName(), Font.PLAIN, fontSize));
            } else {
                // Use system default font if custom font is null
                UIManager.put(component, new Font(defaultFont.getName(), Font.PLAIN, fontSize));
            }
        } catch (Exception e) {
            System.err.println("Error setting UI font: " + e.getMessage());
            // Fallback to a guaranteed available font
            UIManager.put(component, new Font("SansSerif", Font.PLAIN, fontSize));
        }
    }

    public JPanel getPanel() {
        return panel;
    }
}
