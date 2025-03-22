package src;

import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

import src.MyTransitionListener.gameType;

public class GameGUI extends GUI implements ActionListener {

  private BlackjackNative game;
  private JLabel moneyLabel;
  private JPanel gamePanel, buttonPanel, playerPanel, dealerPanel;
  private JButton hitButton, stayButton;
  private double moneyAmount;
  private gameType moneyType;

  public GameGUI(gameType moneyType, double moneyAmount) {
    super("Game");
    Main.setMenuVisibility(true);
    this.moneyAmount = moneyAmount;

    // Initialize native game
    game = new BlackjackNative();
    game.newGame();

    // Initialize money based on game type
    if (moneyType == gameType.WAGER) {
      // Already handled by native game initialization
    } else {
      // Override default money if bet type
      game.placeBet((int) moneyAmount);
    }

    // Initialize UI components
    moneyLabel = new JLabel();
    gamePanel = new JPanel();
    buttonPanel = new JPanel();
    playerPanel = new JPanel();
    dealerPanel = new JPanel();

    gamePanel.setLayout(new GridLayout(1, 0));
    playerPanel.setLayout(new GridLayout(1, 0));
    dealerPanel.setLayout(new GridLayout(1, 0));

    hitButton = new JButton("Hit!");
    stayButton = new JButton("Stay!");
    hitButton.addActionListener(this);
    stayButton.addActionListener(this);

    buttonPanel.setLayout(new GridLayout(0, 1));
    buttonPanel.add(hitButton);
    buttonPanel.add(stayButton);
    buttonPanel.setBorder(new EmptyBorder(100, 0, 0, 0));

    // Add initial cards from native game
    updateCardDisplay();

    gamePanel.add(playerPanel);
    gamePanel.add(dealerPanel);

    this.getPanel().add(moneyLabel);
    this.getPanel().add(gamePanel);
    this.getPanel().add(buttonPanel);

    setComponentAlignment(playerPanel);
    setComponentAlignment(dealerPanel);
    this.setComponentAlignment();

    // Update display
    updateMoneyDisplay();
  }

  @Override
  public void actionPerformed(ActionEvent e) {
    JButton button = ((JButton) e.getSource());

    if (button.getText().equalsIgnoreCase("hit!")) {
      boolean stillAlive = game.playerHit();
      updateCardDisplay();

      if (!stillAlive) {
        showMessage("Dealer Won", "Sorry, the dealer won the game, because your deck value went above 21. " +
            "\nYour deck value was: " + game.getPlayerHandValue());
        restartGame();
      }
    } else {
      game.playerStand();
      updateCardDisplay();

      showMessage("Game Over", game.getGameStateMessage() +
          "\nYour hand value: " + game.getPlayerHandValue() +
          "\nDealer's hand value: " + game.getDealerHandValue());

      restartGame();
    }
  }

  private void restartGame() {
    if (game.getPlayerMoney() <= 0) {
      showMessage("You lost all your money!",
          "Sorry, you lost all of your money! You have to restart the entire game now :(");
      this.getPanel().setVisible(false);
    } else {
      game.newGame();
      playerPanel.removeAll();
      dealerPanel.removeAll();
      game.placeBet((int) moneyAmount);
      updateCardDisplay();
      updateMoneyDisplay();
    }
  }

  private void updateCardDisplay() {
    // Clear existing cards
    playerPanel.removeAll();
    dealerPanel.removeAll();

    // Get cards from native game
    Card[] playerCards = game.getPlayerCards();
    Card[] dealerCards = game.getDealerCards();

    // Display player cards
    for (Card card : playerCards) {
      addCardToPanel(playerPanel, card);
    }

    // Display dealer cards (possibly hiding first card)
    for (int i = 0; i < dealerCards.length; i++) {
      if (i == 1 && game.shouldHideDealerFirstCard()) {
        // Show card back instead
        JLabel cardBack = new JLabel(new String(Character.toChars(Integer.parseInt("0001F0A0", 16))));
        cardBack.setFont(new Font(GUI.defaultFont.getName(), Font.PLAIN, 200));
        cardBack.setHorizontalAlignment(JLabel.CENTER);
        dealerPanel.add(cardBack);
      } else {
        addCardToPanel(dealerPanel, dealerCards[i]);
      }
    }

    // Refresh panels
    playerPanel.revalidate();
    playerPanel.repaint();
    dealerPanel.revalidate();
    dealerPanel.repaint();
  }

  private void addCardToPanel(JPanel panel, Card card) {
    JLabel cardLabel = new JLabel(card.getUnicode());
    cardLabel.setFont(new Font(GUI.defaultFont.getName(), Font.PLAIN, 200));
    cardLabel.setHorizontalAlignment(JLabel.CENTER);
    panel.add(cardLabel);
  }

  private void updateMoneyDisplay() {
    moneyLabel.setText(String.format("Total Money: $%d | Current Bet: $%d",
        game.getPlayerMoney(), game.getCurrentBet()));
  }
}