
#define uint_32 unsigned int

typedef enum // flag bits
{
  none=0,
  one=0x1,
  two=0x2,
  three=0x4,
  four=0x8,
  five=0x10,
  six=0x20,
  seven=0x40,
  eight=0x80,
  nine=0x100,
  all=0x1FF,
} Value;

class List // flag and manipulate 
{
public:
  List();
  ~List();

  // and with bit
  bool andNone();
  bool andOne();
  bool andTwo();
  bool andThree();
  bool andFour();
  bool andFive();
  bool andSix();
  bool andSeven();
  bool andEight();
  bool andNine();
  bool andAll();
  bool andVal( Value val );

  // set and clear bits
  void setOne();
  void setTwo();
  void setThree();
  void setFour();
  void setFive();
  void setSix();
  void setSeven();
  void setEight();
  void setNine();
  void setAll();
  void setVal( Value val );
  void clearVal( Value val );
  void clearVal( uint_32 uint );

  // zero flags
  void equalNone();
  void equalVal( Value val );
  void equalVal( uint_32 uint );

  uint_32 show() { return m_list; };

public:
  uint_32   m_list;
};

class Spot
{
public:
  typedef enum {
    Determined,
    Possible,
    Excluded,
  } State;

  Spot();
  ~Spot();
  void init();

  void setDetermined( uint_32 uint );
  void setDetermined( Value val );
  void setPossible( Value val );
  void setExcluded( Value val );

  List getDetermined() { return m_determined; };
  List getPossible() { return m_possible; };
  List getExcluded() { return m_excluded; };

public:
  State m_state;
  List m_determined;
  List m_possible;
  List m_excluded;
};


class Board
{
public:
  Board();
  ~Board();

  void loadGame1( const char* csv );
  void loadGame( const char* csv );
  void loadGame( FILE* file );
  void loadGame( ); // stdin
  void loader( char(*foo)(void) );

  void saveGameToStdout1( );
  void saveGameToStdout( );
  void saveGameToFilename( const char* name );
  void saver( FILE *file, int(*function)(FILE *file, const char*) );

  void printSpot( Spot::State state, Value val, int row, int col );
  void printByValue( Spot::State state, Value val );
  void printDetermined( Value val );
  void printPossibleByValue( Value val );
  void printExcludedByValue( Value val );

  void excludeRowByValue( int row, int col, Value val );
  void excludeColumnByValue( int row, int col, Value val );
  void excludeSquareByValue( int row, int col, Value val );
  void algorithm1();

  bool checkSquareForTwo( int rowStart, int rowStop, int colStart, int colStop, int valint );
  void findTwoInSquare( );
  void algorithm2();

  // row
  // column
  // square
  
public:
  // row,column
  Spot board[10][10];
};
