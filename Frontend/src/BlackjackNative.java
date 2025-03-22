package src;

import java.io.File;

public class BlackjackNative {
    // Load the native library
    static {
        try {
            String libPath = "/Users/Aadi/Desktop/demos/Gamelogic/build/libBlackjackNative.dylib";
            System.load(new File(libPath).getAbsolutePath());
            System.out.println("Successfully loaded native library from: " + libPath);
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Error loading native library: " + e.getMessage());
            e.printStackTrace();
        }
    }

    // Game instance pointer (in C++)
    private long gamePtr;

    public BlackjackNative() {
        gamePtr = createGameInstance();
    }

    @Override
    protected void finalize() {
        destroyGameInstance(gamePtr);
    }

    // Native methods
    private native long createGameInstance();

    private native void destroyGameInstance(long gamePtr);

    public native void newGame();

    public native void placeBet(int amount);

    public native boolean playerHit();

    public native void playerStand();

    public native boolean isGameOver();

    public native Card[] getPlayerCards();

    public native Card[] getDealerCards();

    public native boolean shouldHideDealerFirstCard();

    public native int getPlayerMoney();

    public native int getCurrentBet();

    public native int getPlayerHandValue();

    public native int getDealerHandValue();

    public native boolean didPlayerWin();

    public native boolean didDealerWin();

    public native boolean isTie();

    public native String getGameStateMessage();
}