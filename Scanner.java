import java.util.ArrayList;
import java.util.List;

public class Scanner {

    private final String source;
    private final List<Token> tokens = new ArrayList<>();
    private int start = 0;
    private int current = 0;
    private int line = 1;

    public Scanner(String source) { this.source = source; }

    List<Token> scanTokens()
    {
        while(!isAtEnd()) {
            start = current; // comeca no inicio do proximo lexeme 
            scanTokens();
        };

        tokens.add(new Token(EOF, "", null, line));
        return tokens;
    }

    private boolean isAtEnd() { return current >= source.length(); }
    
}
