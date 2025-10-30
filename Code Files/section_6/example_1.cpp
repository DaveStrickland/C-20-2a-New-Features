#include <list>
#include <algorithm>


int main()
{
    std::list<int> l = {3,-1,10};
//    std::sort(l.begin(), l.end());
/* The sort fails because list only supports bidirectional iterator, but sort requires
   a random access iterator. Concepts is supposed to provide a better way to find this
   out rather than a horrendously long and complicated compiler error message

   This will be addressed with concepts in example_3
 */
}
