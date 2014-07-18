// C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

// C++
#include <iostream>
#include <string>
using namespace std;

#include "sudoku.hh"

int debug = 0;
// printDebug(string) { if (debug>1) printf(string); }
// DEBUG(A) do { if (debug>1) printf(A); } while(0)

void assert( bool test )
{
  if( test == true ) return;
  printf( "assert failed\n" );
  exit(-1);
}
void negAssert( bool test )
{
  assert( !test );
}

// Value
// Value to int conversion routines
uint_32 makeIntFromVal( Value val )
{
  switch( val )
    {
    case none:
      return 0;
      break;
    case one:
      return 1;
      break;
    case two:
      return 2;
      break;
    case three:
      return 3;
      break;
    case four:
      return 4;
      break;
    case five:
      return 5;
      break;
    case six:
      return 6;
      break;
    case seven:
      return 7;
      break;
    case eight:
      return 8;
      break;
    case nine:
      return 9;
      break;
    case all:
    default:
      return 0;
      break;
    }
}
Value makeValFromInt( uint_32 uint )
{
  switch( uint )
    {
    case 0:
    return none;
      break;
    case 1:
      return one;
      break;
    case 2:
      return two;
      break;
    case 3:
      return three;
      break;
    case 4:
      return four;
      break;
    case 5:
      return five;
      break;
    case 6:
      return six;
      break;
    case 7:
      return seven;
      break;
    case 8:
      return eight;
      break;
    case 9:
      return nine;
      break;
    default:
      return none;
      break;
    }
}

// List
List::List()
{
};
List::~List()
{
};
bool List::andOne()        { return(one & m_list); };
bool List::andTwo()        { return(two & m_list); };
bool List::andThree()      { return(three & m_list); };
bool List::andFour()       { return(four & m_list); };
bool List::andFive()       { return(five & m_list); };
bool List::andSix()        { return(six & m_list); };
bool List::andSeven()      { return(seven & m_list); };
bool List::andEight()      { return(eight & m_list); };
bool List::andNine()       { return(nine & m_list); };
bool List::andAll()        { return(all == m_list); };
bool List::andNone()       { return(!(all & m_list)); };
bool List::andVal( Value val )        { return(val & m_list); };

void List::setOne()        { m_list |= one; };
void List::setTwo()        { m_list |= two; };
void List::setThree()      { m_list |= three; };
void List::setFour()       { m_list |= four; };
void List::setFive()       { m_list |= five; };
void List::setSix()        { m_list |= six; };
void List::setSeven()      { m_list |= seven; };
void List::setEight()      { m_list |= eight; };
void List::setNine()       { m_list |= nine; };
void List::setAll()        { m_list |= all; };
void List::setVal( Value val )
                 { m_list |= val; }; 
void List::equalNone()     { m_list = none; };
void List::equalVal( Value val )
                   { m_list = val; }; 
void List::equalVal( uint_32 uint )
{
  switch( uint )
    {
    case 0:
      equalVal( none );
      break;
    case 1:
      equalVal( one );
      break;
    case 2:
      equalVal( two );
      break;
    case 3:
      equalVal( three );
      break;
    case 4:
      equalVal( four );
      break;
    case 5:
      equalVal( five );
      break;
    case 6:
      equalVal( six );
      break;
    case 7:
      equalVal( seven );
      break;
    case 8:
      equalVal( eight );
      break;
    case 9:
      equalVal( nine );
      break;
    case 10:
    default:
      equalVal( none );
      break;
    }
}
void List::clearVal( Value val )
                    { if( m_list & val ) m_list = m_list ^ val; }; 
void List::clearVal( uint_32 uint )
                    { if( m_list & makeValFromInt(uint)) m_list = m_list ^ makeValFromInt(uint); }; 



// warning: only works with getDetermined
// this will mislead if list is not unique
uint_32 makeIntFromList( List list )
{
  if( list.andOne() ) return 1;
  if( list.andTwo() ) return 2;
  if( list.andThree() ) return 3;
  if( list.andFour() ) return 4;
  if( list.andFive() ) return 5;
  if( list.andSix() ) return 6;
  if( list.andSeven() ) return 7;
  if( list.andEight() ) return 8;
  if( list.andNine() ) return 9;
  return 0;
}
char makeCharFromList( List list )
{
  if( list.andOne() ) return '1';
  if( list.andTwo() ) return '2';
  if( list.andThree() ) return '3';
  if( list.andFour() ) return '4';
  if( list.andFive() ) return '5';
  if( list.andSix() ) return '6';
  if( list.andSeven() ) return '7';
  if( list.andEight() ) return '8';
  if( list.andNine() ) return '9';
  return 0;
}
// warning: only works with getDetermined
// this will mislead if list is not unique
Value makeValFromList( List list )
{
  if( list.andOne() ) return one;
  if( list.andTwo() ) return two;
  if( list.andThree() ) return three;
  if( list.andFour() ) return four;
  if( list.andFive() ) return five;
  if( list.andSix() ) return six;
  if( list.andSeven() ) return seven;
  if( list.andEight() ) return eight;
  if( list.andNine() ) return nine;
  return none;
}


// spot
Spot::Spot()
{
}
Spot::~Spot()
{
}
void Spot::init()
{
  m_determined.equalNone();
  m_possible.setAll();
  m_excluded.equalNone();
};
void Spot::setDetermined( uint_32 uint )
{
  m_determined.equalNone();  // exclusive
  if( uint == 0 ) return;
  m_possible.equalNone();  // exclusive
  m_determined.equalVal( uint );
  m_possible.equalVal( uint );
  m_excluded.setAll();
  m_excluded.clearVal( uint );
};
void Spot::setDetermined( Value val )
{
  m_determined.equalNone();  // exclusive
  if( val == none ) return;
  m_possible.equalNone();  // exclusive
  m_determined.equalVal( val );
  m_possible.equalVal( val );
  m_excluded.setAll();
  m_excluded.clearVal( val );
};
void Spot::setPossible( Value val )
{
  if( val == none ) return;
  if( ! m_determined.andVal( val ) ) {
    m_determined.equalNone();
    printf("%s possible a determined negative!\n", __FUNCTION__);
  }
  m_possible.setVal( val );
  m_excluded.clearVal( val );
}
void Spot::setExcluded( Value val )
{
  if( val == none ) return;
  if( m_determined.andVal( val ) ) {
    m_determined.equalNone();
    printf("%s exclude a determined!\n", __FUNCTION__);
  }
  if( m_possible.andVal( val ) ) {
    m_possible.clearVal( val );
    //printf("%s exclude a possible!\n", __FUNCTION__);
  }

  //printf("%x", m_excluded.show());
  //if( ! m_excluded.andVal( val ) ) {
    m_excluded.setVal( val );
    //}
    //printf("%x ", m_excluded.show());
}

// Board
Board::Board()
{
  for( int row=1; row<10; row++ )
    {
      for( int col=1; col<10; col++ )
	{
	  board[row][col].init();
	}
    }
};
Board::~Board()
{
};
// This is the CSV format as opposed to the printout format
const char* example1 =
"0,0,5, 0,0,0, 0,0,6,\
 0,0,0, 8,0,0, 0,0,0,\
 9,3,0, 0,7,0, 0,2,0,\
 \
 4,6,0, 0,0,0, 0,0,9,\
 0,0,0, 0,0,6, 0,0,5,\
 0,0,3, 0,0,0, 0,7,8,\
 \
 0,0,1, 0,0,0, 0,0,0,\
 5,0,0, 7,9,0, 0,6,0,\
 0,0,4, 0,3,5, 0,0,2,\
";
// This reads the CSV format
void Board::loadGame1( const char* ccsv )
{
  printf("%s %s\n",__FUNCTION__ , ccsv );
  for( int row=1; row<10; row++ ) 
    {
      for( int col=1; col<10; col++ )
	{
	  bool foundone=false;
	  while( !foundone )
	    {
	      // use strtok() ???
	      uint_32 num=0;
	      char c= *ccsv++;
	      //printf("%s row %d col %d %c\n",__FUNCTION__ , row, col, c );
	      switch( c ) {
	      case ' ':
	      case ',':
	      case '\n':
	      case '\f':
		break;
	      default:
		num = atoi( &c );
		if( num < 10 && num >= 0 ) {
		  foundone=true;
		  board[row][col].setDetermined(num);
		}
		break;
	      }
	      //printf("%s row %d col %d num %d char %c     ",__FUNCTION__ , row, col, num, c );
	    }
	}
    }
}
// This reads the printout format
void Board::loader( FILE *file, char(*function)(FILE *file) )
{
  for( int row=1; row<10; row++ ) 
    {
      for( int col=1; col<10; col++ )
	{
	  bool foundone=false;
	  while( !foundone )
	    {
	      uint_32 num=0;
	      char c = function(file); 
	      //printf("%s row %d col %d %c\n",__FUNCTION__ , row, col, c );
	      switch( c ) {
	      case '0':
	      case '1':
	      case '2':
	      case '3':
	      case '4':
	      case '5':
	      case '6':
	      case '7':
	      case '8':
	      case '9':
		num = atoi( &c );
		if( num < 10 && num >= 0 ) {
		  foundone=true;
		  board[row][col].setDetermined(num);
		}
		break;
	      case ' ':
	      case '|':
	      case '-':
	      case '\n':
	      case '\f':
		break;
	      default:
		cout << " bad char\n";
		return;
		break;
	      }
	    }
	}
    }
}
static char readin( FILE* file )
{
  char c;
  if (file == NULL) {
    cin >> c;
  } else {
    fread(&c, 1, 1, file);
  }
  return c;
}
// not really useful?
void Board::loadGameFromStdin( ) // from stdin
{
  loader( NULL, readin );
}
void Board::loadGameFromFile( const char* filename )
{
  FILE* file = fopen( filename, "r+" );
  if( file == NULL ) {
    printf( "%s error\n", __FUNCTION__ );
    return;
  }
  loader( file, readin );
  fclose( file );
}


// obsolete
void Board::saveGameToStdout1( )
{
  for( int row=1; row<10; row++ )
    {
      for( int col=1; col<10; col++ )
	{
	  List list = board[row][col].getDetermined();
	  if( list.andVal( all) )
	    cout << makeIntFromList( list );  // warning needs unique
	  else
	    cout << "0";

	  if( (col == 3) || (col == 6) )
	    cout << "|";
	  else
	    cout << " ";
	}
      if( (row == 3) || (row == 6) )
	{
	  cout << "\n";
	  for( int i=1; i<10; i++ ) cout << "--";
	}
      cout << "\n";
    }
  cout << "\n";
}
// used for save to file and save to stdout
// thie produces the printout format for showing a board
void Board::saver( FILE *file, int(*function)(FILE*, const char*) )
{
  for( int row=1; row<10; row++ )
    {
      for( int col=1; col<10; col++ )
	{
	  List list = board[row][col].getDetermined();
	  if( list.andVal( all) ) {
	    char str[16];
	    sprintf(str, "%c", makeCharFromList( list ));
	    function( file, str );
	  } else
	    function( file, "0" );

	  if( (col == 3) || (col == 6) )
	    function ( file, "|" );
	  else
	    function ( file, " " );
	}
      if( (row == 3) || (row == 6) )
	{
	  function ( file, "\n" );
	  for( int i=1; i<10; i++ ) function ( file, "--" );
	}
      function ( file, "\n" );
    }
  function ( file, "\n" );
}
// or put this in Board:: and pass file in class
int printout( FILE *file, const char* str )
{
  if( file != NULL ) {
    //printf( "%s",str );
    return fprintf( file, "%s",str );
  }

  return printf( "%s",str );
}
// not really useful?
void Board::saveGameToStdout( )
{
  saver( NULL, printout );
}
void Board::saveGameToFile( const char* filename )
{
  FILE* file = fopen( filename, "w+" );
  if( file == NULL ) {
    printf( "%s error\n", __FUNCTION__ );
    return;
  }
  saver( file, printout ); 
  fclose( file );
}
void Board::printSpot( Spot::State state, Value val, int row, int col )
{
  List list;
  switch(state)
    {
    case Spot::Determined:
      list = board[row][col].getDetermined();
      if( list.andVal( all) )
	printf("%d", makeIntFromList( list ));
      else
	printf(" ");
      return;
      break;
    case Spot::Possible:
      list = board[row][col].getPossible();
      if( list.andVal(val) )
	printf("%d", makeIntFromVal( val ));
      else
	printf(" ");
      break;
    case Spot::Excluded:
      list = board[row][col].getExcluded();
      if( list.andVal(val) )
	printf("%d", makeIntFromVal( val ));
      //printf("%x", list.show());
      else
	printf(" ");
      break;
    }
}
void Board::printByValue( Spot::State state, Value val )
{
  for( int row=1; row<10; row++ )
    {
      for( int col=1; col<10; col++ )
	{
	  printSpot( state, val, row, col );

	  if( (col == 3) || (col == 6) )
	    printf("|");
	  else
	    printf(" ");
	}
      if( (row == 3) || (row == 6) )
	{
	  printf("\n");
	  for( int i=1; i<10; i++ ) printf("--");
	}
      printf("\n");
    }
  printf("\n");
}
// This produces the printout format for showing a board
void Board::printDetermined( Value val )
{
  printByValue( Spot::Determined, val );
}
void Board::printPossibleByValue( Value val )
{
  printByValue( Spot::Possible, val );
}
void Board::printExcludedByValue( Value val )
{
  printByValue( Spot::Excluded, val );
}

void Board::excludeRowByValue( int rrow, int ccol, Value val )
{
  for( int col=1; col<10; col++ )
    {
      //printf("%s val %d rrow %d ccol %d col %d\n", __FUNCTION__, makeIntFromVal(val), rrow, ccol, col);
      if( col != ccol)
	board[rrow][col].setExcluded(val);
    }
}
void Board::excludeColumnByValue( int rrow, int ccol, Value val )
{
  for( int row=1; row<10; row++ )
    {
      //printf("%s val %d rrow %d ccol %d row %d\n", __FUNCTION__, makeIntFromVal(val), rrow, ccol, row);
      if( row != rrow)
	board[row][ccol].setExcluded(val);
    }
}
void Board::excludeSquareByValue( int rrow, int ccol, Value val )
{
  // upper left square
  if( rrow < 4 && ccol < 4 ) 
    {
      for( int row=1; row<4; row++ )
	  for( int col=1; col<4; col++ )
	    if( row != rrow && col != ccol )
	      board[row][col].setExcluded(val);
      return;
    }
  // upper middle square
  if( rrow < 4 && ccol < 7 ) 
    {
      for( int row=1; row<4; row++ )
	  for( int col=4; col<7; col++ )
	    if( row != rrow && col != ccol )
	      board[row][col].setExcluded(val);
      return;
    }
  // upper right square
  if( rrow < 4 && ccol < 10 ) 
    {
      for( int row=1; row<4; row++ )
	  for( int col=7; col<10; col++ )
	    if( row != rrow && col != ccol )
	      board[row][col].setExcluded(val);
      return;
    }

  // middle left square
  if( rrow < 7 && ccol < 4 ) 
    {
      for( int row=4; row<7; row++ )
	  for( int col=1; col<4; col++ )
	    if( row != rrow && col != ccol )
	      board[row][col].setExcluded(val);
      return;
    }
  // middle middle square
  if( rrow < 7 && ccol < 7 ) 
    {
      for( int row=4; row<7; row++ )
	  for( int col=4; col<7; col++ )
	    if( row != rrow && col != ccol )
	      board[row][col].setExcluded(val);
      return;
    }
  // middle right square
  if( rrow < 7 && ccol < 10 ) 
    {
      for( int row=4; row<7; row++ )
	  for( int col=7; col<10; col++ )
	    if( row != rrow && col != ccol )
	      board[row][col].setExcluded(val);
      return;
    }

  // lower left square
  if( rrow < 10 && ccol < 4 ) 
    {
      for( int row=7; row<10; row++ )
	  for( int col=1; col<4; col++ )
	    if( row != rrow && col != ccol )
	      board[row][col].setExcluded(val);
      return;
    }
  // lower middle square
  if( rrow < 10 && ccol < 7 ) 
    {
      for( int row=7; row<10; row++ )
	  for( int col=4; col<7; col++ )
	    if( row != rrow && col != ccol )
	      board[row][col].setExcluded(val);
      return;
    }
  // lower right square
  if( rrow < 10 && ccol < 10 ) 
    {
      for( int row=7; row<10; row++ )
	  for( int col=7; col<10; col++ )
	    if( row != rrow && col != ccol )
	      board[row][col].setExcluded(val);
      return;
    }

}
/* Exclude values because of existing knowns - do by row, column, square
 */
void Board::algorithm1()
{
  for( int row=1; row<10; row++ )
    {
      for( int col=1; col<10; col++ )
	{
	  List list = board[row][col].getDetermined();
	  //printf("%s val %d row %d col %d\n", __FUNCTION__, makeIntFromList(list), row, col);
	  if( list.andVal( all) )
	    {
	      excludeRowByValue( row, col, makeValFromList( list ) );
	      excludeColumnByValue( row, col, makeValFromList( list ) );
	      excludeSquareByValue( row, col, makeValFromList( list ) );
	    }
	}
    }
}
bool Board::checkSquareForTwo(int rowStart, int rowStop, int colStart, int colStop, int valint)
{
  int rcnt=0;
  int rcol=0;
  int rrow=0;
  bool isCol = false;
  bool isRow = false;
  bool failed = false;

  for( int row=rowStart; row<rowStop; row++ )
    {
      for( int col=colStart; col<colStop; col++ ) // upper left
	{
	  List list = board[row][col].getPossible();
	  if( list.andVal( makeValFromInt( valint ) ) )
	    {
	      rcnt++;
	      if( rcnt == 1 )
		{
		  rcol = col;
		  rrow = row;
		}
	      if( rcnt == 2 )
		{
		  negAssert( rcol == col && rrow == row );
		  if( rcol == col ) // found case
		    isCol = true;
		  if( rrow == row ) // found case
		    isRow = true;
		}
	      if( rcnt == 3 )
		{
		  if( rcol == col && !isCol )
		    failed = true;
		  if( rrow == row && !isRow )
		    failed = true;
		}
	      if( rcnt == 4 )
		failed = true;
	    }
	  if( failed ) break;
	}
    }
  return !failed;
}
void Board::findTwoInSquare()
{
  bool found = false;
  for( int valint=1; valint<10; valint++ )
    {
      // upper left square
      found = checkSquareForTwo(1,4,1,4,valint);
      if( found )
	printf( "two %d in upper left\n",valint);

      // upper middle square
      found = checkSquareForTwo(1,4,4,7,valint);
      if( found )
	printf( "two %d in upper middle\n",valint);

      // upper right square
      found = checkSquareForTwo(1,4,7,10,valint);
      if( found )
	printf( "two %d in upper right\n",valint);

      // middle left square
      found = checkSquareForTwo(4,7,1,4,valint);
      if( found )
	printf( "two %d in middle left\n",valint);

      // middle middle square
      found = checkSquareForTwo(4,7,4,7,valint);
      if( found )
	printf( "two %d in middle middle\n",valint);

      // middle right square
      found = checkSquareForTwo(4,7,7,10,valint);
      if( found )
	printf( "two %d in middle right\n",valint);

      // lower left square
      found = checkSquareForTwo(7,10,1,4,valint);
      if( found )
	printf( "two %d in lower left\n",valint);

      // lower middle square
      found = checkSquareForTwo(7,10,4,7,valint);
      if( found )
	printf( "two %d in lower middle\n",valint);

      // lower right square
      found = checkSquareForTwo(7,10,7,10,valint);
      if( found )
	printf( "two %d in lower right\n",valint);
    }
}
/* Check for two of the same value in a square
 */
void Board::algorithm2()
{
  findTwoInSquare();
}

void printUsage(void)
{
  cout << "L <game>       -load a game from file <game>\n";
  cout << "S <save>       -save current position to file <save>\n";
  cout << "p n            -print the possible positions for n\n";
  cout << "e n            -print the excluded positions for n\n";
  cout << "d              -print the determined values\n";
  cout << "a [1|2]        -run the exclusion algorithms\n";
  cout << "  1             exclude by row, column, square  \n";
  cout << "  2             find two in squares \n";
  cout << "s n row col    -set <row,col> to be n\n";
  cout << "  n             is 0-9 where 0 means empty\n";
}
int main(int argc, char** argv)
{
  printUsage();

  Board* game = new Board();

  // default starting game
  // this should become redundant when load & save to file work
  //game->loadGame1( example1 );

  char cmd, opt;
  bool stop = false;
  while( !stop )
    {
      cin >> cmd;
      switch( cmd ) {
      case 'a':
        cin >> opt;
	cout << " algorithm " << opt << "\n"; 
	switch( opt ) {
	case '1':
	  game->algorithm1();
	  break;
	case '2':
	  game->algorithm2();
	  break;
	}
	break;
      case 'd':
	cout << " determined " << "\n"; 
	game->printDetermined( all );
	break;
      case 'e':
	{
	  cin >> opt;
	  cout << " excluded " << opt << "\n"; 
	  switch( opt ) {
	  case '1':
	    game->printExcludedByValue( one );
	    break;
	  case '2':
	    game->printExcludedByValue( two );
	    break;
	  case '3':
	    game->printExcludedByValue( three );
	    break;
	  case '4':
	    game->printExcludedByValue( four );
	    break;
	  case '5':
	    game->printExcludedByValue( five );
	    break;
	  case '6':
	    game->printExcludedByValue( six );
	    break;
	  case '7':
	    game->printExcludedByValue( seven );
	    break;
	  case '8':
	    game->printExcludedByValue( eight );
	    break;
	  case '9':
	    game->printExcludedByValue( nine );
	    break;
	  }
	}
	break;
      case 'L':
	{
	  string gamestr;
	  cin >> gamestr;
	  cout << " file " << gamestr << "\n"; 
	  game->loadGameFromFile( (const char*) gamestr.data() );
	}
	break;
      case 'p':
	{
	  cin >> opt;
	  cout << " possible " << opt << "\n"; 
	  switch( opt ) {
	  case '1':
	    game->printPossibleByValue( one );
	    break;
	  case '2':
	    game->printPossibleByValue( two );
	    break;
	  case '3':
	    game->printPossibleByValue( three );
	    break;
	  case '4':
	    game->printPossibleByValue( four );
	    break;
	  case '5':
	    game->printPossibleByValue( five );
	    break;
	  case '6':
	    game->printPossibleByValue( six );
	    break;
	  case '7':
	    game->printPossibleByValue( seven );
	    break;
	  case '8':
	    game->printPossibleByValue( eight );
	    break;
	  case '9':
	    game->printPossibleByValue( nine );
	    break;
	  }
	}
	break;
      case 's':
	{
	  cin >> opt;
	  int val = atoi( &opt );
	  cin >> opt;
	  int row = atoi( &opt );
	  cin >> opt;
	  int col = atoi( &opt );
	  cout << " set " << val << " at <" << row << "," << col << "> \n"; 
	  game->board[row][col].setDetermined( val );
	}
	break;
      case 'S':
	/*
	// Need way to check if cin is null/EOF
	{
	  char namebuf[64];
	  scanf("%s", namebuf);

	  if( strlen( namebuf ) > 0 )
	    game->saveGameToFile( (const char *)namebuf );
	  else
	    game->saveGameToStdout( );
	}
	// this requires filename of length 1
	{
	  string savestr;
	  cin >> savestr;
	  cout << savestr << " " << savestr.size() << "\n";;
	  if( savestr.length() > 1 )
	    game->saveGameToFile( (const char *) savestr.data() );
	  else
	    game->saveGameToStdout( );
	}
	*/
	{
	  string savestr;
	  cin >> savestr;
	  cout << "save file " << savestr << "\n";;
	  game->saveGameToFile( (const char *) savestr.data() );
	}

	break;
      case 'q':
	stop = true;
	break;
      default:
	printUsage();
	//cout << " unknown " << cmd << " \n";
	break;
      }
    }
}
