class game{
public:
  struct Index{
    int row;
    int col;
    Index(int a, int b){
      row = a;
      col = b;
    }
  };
  char difficulty;
  int blankSpaces;
  sf::RenderWindow *window;
  mainMenu *menu;
  bool replay;
  puzzleGenerator* p;
  int width;
  int height;
  sf::Text** tiles;
  int numberPressed;
  sf::Text hintText;
  sf::Text solveText;
  vector<Index> correct;
  int numCorrect;
  vector<Index> wrong;
  int numWrong;
  game(char d, mainMenu *m){
    replay = false;
    width = 2000;
    height = 450;
    srand (time(NULL));
    bool gameOver = false;
    difficulty = d;
    menu = m;
    p = new puzzleGenerator();
    p->generatePuzzle(1,1);
    window = menu->getWindow();
    tiles = drawInitialBoard();
    numCorrect = 0;
    numWrong = 0;
  }
  void drawBoardBackground();
  sf::Text** drawInitialBoard();
  void drawCurrentBoard(int row, int col, sf::Color color, int val);
  sf::RectangleShape setSpot(int row, int col, sf::Color color);
  bool play(int currentRow, int CurrentCol);
  sf::Text enterValue(int row, int col, int val);
  bool valueCorrect(int row, int col);
  bool endScreen();
  void clearMemory();
};
