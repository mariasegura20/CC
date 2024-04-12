// Input:  m[1], m[2], ...	(the string)
// Output: m[0]			(0 == false, 1 == true)

#include "ram.h"
#include <iostream>

void program()
{
    reset(0);   // Counter to go through the number
    reset(1);   // +1 if I process a 1, -1 if I process a 0
    reset(3);   // Auxiliary variable to inconditional jumps 

    loop:
        inc(0);
        load(2, 0);     // r[2] = m[r[0]]
        cgoto(2, process);   // If digit is 0 or 1 -> process
        cgoto(3, end);  // If is the end -> end

    process:
        dec(2); // Check if the number is 0 or 1
        cgoto(2, one);
        cgoto(3, zero);
    
    zero:
        dec(1); // r[1]--
        cgoto(3, loop);
    
    one:
        inc(1); // r[1]++
        cgoto(3, loop);
    
    end:
        dec(1);
        cgoto(1, no);   // If r[1] > 0 -> no
        inc(1);
        cgoto(1, yes);   // If r[1] == 0 -> yes
        cgoto(3, no);   // If r[1] < 0 -> no
    
    no:
        reset(0);
        reset(1);
        cgoto(3, save);
    
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
