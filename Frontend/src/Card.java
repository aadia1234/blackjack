package src;

public class Card {
    protected String face;
    protected char suit;
    protected String suitName;
    protected int value;

    public Card(String face, char suit, String suitName, int value) {
        this.face = face;
        this.suit = suit;
        this.suitName = suitName;
        this.value = value;
    }

    public String getUnicode() {
        // Base code points for each suit
        int spadesBase = 0x1F0A0;
        int heartsBase = 0x1F0B0;
        int diamondsBase = 0x1F0C0;
        int clubsBase = 0x1F0D0;

        // Select base code point based on suit
        int baseCodePoint;
        switch (suitName.toLowerCase()) {
            case "spades" -> baseCodePoint = spadesBase;
            case "hearts" -> baseCodePoint = heartsBase;
            case "diamonds" -> baseCodePoint = diamondsBase;
            case "clubs" -> baseCodePoint = clubsBase;
            default -> {
                return new String(Character.toChars(0x1F0A0)); // Card back
            }
        }

        // Calculate offset based on face value
        int offset;
        switch (face) {
            case "Ace" -> offset = 1;
            case "2" -> offset = 2;
            case "3" -> offset = 3;
            case "4" -> offset = 4;
            case "5" -> offset = 5;
            case "6" -> offset = 6;
            case "7" -> offset = 7;
            case "8" -> offset = 8;
            case "9" -> offset = 9;
            case "10" -> offset = 10;
            case "Jack" -> offset = 11;
            case "Queen" -> offset = 13;
            case "King" -> offset = 14;
            default -> {
                return new String(Character.toChars(0x1F0A0)); // Card back
            }
        }

        // Create the Unicode character
        return new String(Character.toChars(baseCodePoint + offset));
    }

    @Override
    public String toString() {
        return suitName + " " + face;
    }
}
