public enum TokenType {

    // Single-character tokens
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE, // Chave esquerda
    RIGHT_BRACE,
    COMMA,
    DOT, 
    MINUS,
    PLUS, 
    SEMICOLON,
    SLASH,
    STAR,

    // One or two character tokens.
    BANG, // ! 
    BANG_EQUAL, // !=
    GREATER, 
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,
    
    // Literals
    IDENTIFIER, STRING, NUMBER,

    // Keywords
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,
    EOF

}
