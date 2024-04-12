// Input:  m[1], m[2], ...	(the string)
// Output: m[0]			(0 == false, 1 == true)

// 10101

#include "ram.h"
#include <iostream>

void program()
{
    reset(0);   // Counter to go through the number
    reset(2);   // Auxiliary variable to inconditional jumps 

    node1:
        inc(0);
        load(1, 0);     // r[1] = m[r[0]]
        dec(1);
        cgoto(1, node2);   // If the digit is 1 -> node2
        inc(1);
        cgoto(1, node1);    // If the digit is 0 -> node1
        cgoto(2, yes);  // If is the end -> yes

    node2:
        inc(0);
        load(1, 0);
        dec(1);
        cgoto(1, node1) // If the digit is 1 -> node1
        inc(1);
        cgoto(1, node3);    // If the digit is 0 -> node3
        cgoto(2, no);   // If is the end -> no

    node3:
        inc(0);
        load(1, 0);
        dec(1);
        cgoto(1, node3) // If the digit is 1 -> node1
        inc(1);
        cgoto(1, node2);    // If the digit is 0 -> node3
        cgoto(2, no);   // If is the end -> no

    no:
        reset(0);
        reset(1);
        cgoto(2, save);
    
    yes:
        reset(0);
        reset(1);
        inc(1);
        
    save:
        store(1, 0);
}



// Driver program.

#include <iostream>
#include <iomanip>

memory r, m(1024);

int main()
{
  using namespace std;

  // Data input through the standard input.

  string s = "";
  cout << "Input string? ";
  getline(cin, s);

  // RAM initialization.

  initialize(4);		// Three registers.

  // RAM data input (memory initialization).

  for (string::size_type i = 0; i != s.size(); ++i)
    m[i + 1] = s[i] - 48;
  m[s.size() + 1] = -1;

  // Program execution.

  program();

  // RAM data output (memory reading).

  integer l = m[0];

  // Data output through the standard output. 

  cout << "Representation: ";
  for (string::size_type i = 1; i != s.size() + 2; ++i)
    cout << setw(3) << setfill('0') << m[i] << ' ';
  cout << "Same number of 0s and 1s? " << l << '.' << endl;  
}
