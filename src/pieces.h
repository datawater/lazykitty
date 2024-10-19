#pragma once

typedef enum color {
    white = 0,
    black = 1
} color_e;

typedef enum piece {    
    white_pawn,
    white_knight,
    white_bishop,
    white_rook,
    white_queen,
    white_king,

    black_pawn,
    black_knight,
    black_bishop,
    black_rook,
    black_queen,
    black_king,
    
    none_piece,
} piece_e;

typedef enum castle_type {
    white_kingside,
    white_queenside,
    
    black_kingside,
    black_queenside
} castle_type_e;