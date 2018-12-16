import re
import pybind11
import moveTable

global b

# translate coords into square names

# FEN notation example, start:
# rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
# after e4, looks like
# rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1

# takes a string of alphanumeric, expands numerics into 'e' char for moveTable proc
# for range of int value, returns string
def expand(someString):
    s = ''
    for char in someString:
        try:
            i = int(char)
            s += 'e'*i
        except:
            s += char
    return s
    
# takes board dict, from coord int, to coord int
def move_piece(f, t):
    global b
    tmp = b[f]
    b[f] = 'e'
    b[t] = tmp

# first format FEN for regularity, strip surrounding whitespace?
# incorrectly formatted strings throw errors on 'group' calls
def process_FEN(someFEN):
    someFEN = someFEN.strip()
    board_expr = re.compile(r'[A-Za-z/0-8]+')
    board = board_expr.match(someFEN).group()
    tomove_expr = re.compile('\s([wb])\s')
    tomove = tomove_expr.search(someFEN).group(1)
    can_castle_expr = re.compile(r'\s([KQkq]+|-)\s') # this will get FIRST HYPHEN
    can_castle = can_castle_expr.search(someFEN).group(1)
    en_passant_sqr_expr = re.compile('([KQkq]+|-)\s([a-h][1-8]|-)\s')
    en_passant_sqr = en_passant_sqr_expr.search(someFEN).group(2)
    halfmove_clock_expr = re.compile('\s([a-h][1-8]|-)\s([0-9]{1,2})\s')
    halfmove_clock = halfmove_clock_expr.search(someFEN).group(2)
    fullmove_number_expr = re.compile('\s[0-9]{1,2}\s([0-9]{1,3})$')
    fullmove_number = fullmove_number_expr.search(someFEN).group(1)
    
    # in order of relevance to deciding moves
    print(tomove)
    print(board)
    print(can_castle)
    print(en_passant_sqr)
    print(halfmove_clock)
    print(fullmove_number)
    
    # translate string board to dict/map of ints to string/char, pass to cppchess
    # expand numbers in board_list to 'e'
    board_list = board.split('/')
    exp_board_list = [expand(rank) for rank in board_list]
    coord_pairs = [str(i)+str(x) for x in range(8,0,-1) for i in range(1,9)]
    cpp_dict = {}
    for rank in exp_board_list:
        for char in rank:
            cpp_dict[int(coord_pairs[0])] = char
            coord_pairs = coord_pairs[1:]

    # Interface with cpluschess.cpp here
    # functions exposed from moveTable module
    # vector<pair<int,int>> findBlackMoves(board_map)
    # vector<pair<int,int>> findWhiteMoves(board_map)
    global b
    b = cpp_dict
    w_moves = moveTable.findWhiteMoves(b)
    move1_pair = w_moves[0]
    my_move = moveTable.findBestWhiteMove(b)
    print(my_move)
    move_piece(my_move[0], my_move[1])
    print(moveTable.findBestWhiteMove(b))
    
    # shortcuts
    # is checkmate avail one move?
    
    # if no checkmate, am threatened checkmate?
    
    # can i move so that no matter what response, checkmate avail next move?
    
    # is there a move so that no matter MY response, am threatened checkmate?
    
    #


# TESTS
# process_FEN('   rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1   ')
# process_FEN('rnbqkbnr/pppppppp/8/8/8/PPPPPPPP/RNBQKBNR/8 w - - 9 1')
# process_FEN('rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - a6 33 999')
# print(expand('r3q1bn6r'))
process_FEN('rnbqkbnr/pppppppp/2P5/8/8/8/PP1PPPPP/RNBQKBNR w KQkq - 0 1   ')